#include "makefile.h"

#include <QFile>
#include <QMap>
#include <QRegularExpression>
#include <QStack>
#include <QStringList>
#include <QTextStream>

namespace Qpe
{

static const QLatin1String PATTERN__KEY_VALUE
		("(?<key>^[A-Z][A-Z0-9_]*)\\s*(?<operator>\\+=|=)\\s*(?<value>.*)");
static const QLatin1String PATTERN__SPLIT_KEY_VALUE
		("\\s+");
static const QLatin1String PATTERN__IFDEF
		("ifdef\\s+(?<key>.*)");
static const QLatin1String PATTERN__IFEQ
		("ifeq\\s*\\(\\$\\((?<key>.*)\\),\\s*(?<value>.*)\\)");
static const QLatin1String PATTERN__ELSE
		("else");
static const QLatin1String PATTERN__ENDIF
		("endif");

static const QLatin1String CAPTURE__KEY			("key");
static const QLatin1String CAPTURE__OPERATOR	("operator");
static const QLatin1String CAPTURE__VALUE		("value");


enum Operator
{
	Assign,
	Append,
};

enum Block
{
	Block_Main,
	Block_IfTrue,
	Block_IfFalse,
};

// ------------------------------------------------------------------------

template <Block... TBlock>
struct IsCurrentBlock;

template <Block TBlock1>
struct IsCurrentBlock<TBlock1>
{
	static bool test(Block current) { return current == TBlock1; }
};

template <Block TBlock1, Block... TBlockN>
struct IsCurrentBlock<TBlock1, TBlockN...>
{
	static bool test(Block current)
	{
		return
			IsCurrentBlock<TBlock1>::test(current) ||
			IsCurrentBlock<TBlockN...>::test(current);
	}
};

// ------------------------------------------------------------------------

class MakefileData : public QSharedData
{
public:
	MakefileData()
		: QSharedData()
		, regexKeyValue(PATTERN__KEY_VALUE)
		, regexIfdef(PATTERN__IFDEF)
		, regexIfeq(PATTERN__IFEQ)
		, regexElse(PATTERN__ELSE)
		, regexEndif(PATTERN__ENDIF)
		, splitKeyValue(PATTERN__SPLIT_KEY_VALUE)
	{
		block.push(Block_Main);
	}

	MakefileData(const MakefileData& other)
		: QSharedData(other)
		, keys(other.keys)
		, buffer(other.buffer)
		, block(other.block)
		, regexKeyValue(other.regexKeyValue)
		, regexIfdef(other.regexIfdef)
		, regexIfeq(other.regexIfeq)
		, regexElse(other.regexElse)
		, regexEndif(other.regexEndif)
		, splitKeyValue(other.splitKeyValue)
	{
	}

	~MakefileData()
	{
	}

	bool parseLine(const QString& line);
	bool isKeyValue(const QString& in, QString& key, Operator& op, QStringList& values);
	bool isIfBlock(const QString& in);
	template <Block... TBlocks>
	bool isCurrentBlock() const;

	bool isIfdefBlock(const QString& in);
	bool isIfeqBlock(const QString& in);
	bool isElseBlock(const QString& in);
	bool isEndifBlock(const QString& in);

	QMap<QString, QStringList> keys;

	QString buffer;
	QStack<Block> block;

	QRegularExpression regexKeyValue;
	QRegularExpression regexIfdef;
	QRegularExpression regexIfeq;
	QRegularExpression regexElse;
	QRegularExpression regexEndif;
	QRegularExpression splitKeyValue;
};

bool MakefileData::parseLine(const QString& l)
{
	QString line = l.trimmed();
	if (line.isEmpty()) {
		// пустая строка, пропускаем
		return true;
	}
	if (line.startsWith('#')) {
		// строка комментария, пропускаем
		return true;
	}
	buffer += line;
	if (line.endsWith('\\')) {
		// если последний символ \ - значит надо читать и следующую строку
		buffer.chop(1);
		return true;
	}

	QString key;
	Operator op;
	QStringList values;
	if (isKeyValue(buffer, key, op, values)) {
		if (isCurrentBlock<Block_Main, Block_IfTrue>()) {
			if (op == Assign) {
				keys[key] = values;
			} else
			if (op == Append) {
				keys[key] += values;
			}
		}
		buffer.clear();
		return true;
	}

	if (isIfBlock(buffer)) {
		buffer.clear();
		return true;
	}

	buffer.clear();
	return false;
}

bool MakefileData::isKeyValue(
	const QString& in, QString& key, Operator& op, QStringList& values)
{
	auto match = regexKeyValue.match(in);
	if (!match.hasMatch()) { return false; }

	key = match.captured(CAPTURE__KEY);
	QString ops = match.captured(CAPTURE__OPERATOR);
	if (ops == "+=") {
		op = Append;
	} else
	if (ops == "=") {
		op = Assign;
	} else {
		return false;
	}
	values = match.captured(CAPTURE__VALUE).split(splitKeyValue, Qt::SkipEmptyParts);

	return true;
}

bool MakefileData::isIfBlock(const QString& in)
{
	return
		isIfdefBlock(in) ||
		isIfeqBlock(in) ||
		isElseBlock(in) ||
		isEndifBlock(in);
}

bool MakefileData::isIfdefBlock(const QString& in)
{
	auto match = regexIfdef.match(in);
	if (!match.hasMatch()) { return false; }
	QString key = match.captured(CAPTURE__KEY);
	block.push(keys.contains(key) ? Block_IfTrue : Block_IfFalse);
	return true;
}

bool MakefileData::isIfeqBlock(const QString& in)
{
	auto match = regexIfeq.match(in);
	if (!match.hasMatch()) { return false; }
	QString key = match.captured(CAPTURE__KEY);
	QString value = match.captured(CAPTURE__VALUE);
	QStringList values = keys.value(key);
	block.push(values.contains(value) ? Block_IfTrue : Block_IfFalse);
	return true;
}

bool MakefileData::isElseBlock(const QString& in)
{
	auto match = regexElse.match(in);
	if (!match.hasMatch()) { return false; }
	if (block.isEmpty()) { return false; }
	if (!isCurrentBlock<Block_IfTrue, Block_IfFalse>()) { return false; }
	Block& current = block.top();
	current = (current == Block_IfTrue) ? Block_IfTrue : Block_IfTrue;
	return true;
}

bool MakefileData::isEndifBlock(const QString& in)
{
	auto match = regexEndif.match(in);
	if (!match.hasMatch()) { return false; }
	if (block.isEmpty()) { return false; }
	if (!isCurrentBlock<Block_IfTrue, Block_IfFalse>()) { return false; }
	block.pop();
	return true;
}

template<Block... TBlocks>
bool MakefileData::isCurrentBlock() const
{
	Block current = block.isEmpty() ? Block_Main : block.top();
	return IsCurrentBlock<TBlocks...>::test(current);
}

// ------------------------------------------------------------------------

Makefile::Makefile()
	: d(new MakefileData())
{
}

Makefile::Makefile(const Makefile& other)
	: d(other.d)
{
}

Makefile::~Makefile()
{
}

Makefile& Makefile::operator=(const Makefile& other)
{
	if (this != &other) {
		d = other.d;
	}
	return *this;
}

bool Makefile::loadFrom(const QString& filename)
{
	QFile file(filename);
	if (!file.open(QFile::ReadOnly | QFile::Text)) { return false; }
	QTextStream stream(&file);

	QString line;
	while (stream.readLineInto(&line)) {
//		if (!d->parseLine(line)) { return false; }
		d->parseLine(line);
	}

	return true;
}

QMap<QString, QStringList> Makefile::keys() const
{
	return d->keys;
}


} // namespace Qpe
