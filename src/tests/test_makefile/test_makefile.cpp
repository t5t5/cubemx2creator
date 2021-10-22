#include <QtTest/QTest>
#include <QDebug>
#include <QVariant>

#include <Qpe/c2c/Makefile>

using namespace Qpe;

enum Block
{
	Block_Main,
	Block_IfTrue,
	Block_IfFalse,
};

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

template <Block... TBlocks>
bool isCurrentBlock()
{
	Block current = Block_Main;
	return IsCurrentBlock<TBlocks...>::test(current);
}

class TestMakefile : public QObject
{
	Q_OBJECT
private slots:
	void test();
	void test_isCurrentBlock();
};

void TestMakefile::test()
{
	Makefile mf;
	bool state = mf.loadFrom("C:/sources/_embedded/stm32g030engine_mk/Makefile");
	QVERIFY(state);
	qDebug() << mf.keys();
}

void TestMakefile::test_isCurrentBlock()
{
	QVERIFY(!isCurrentBlock<Block_IfTrue>());
	QVERIFY(isCurrentBlock<Block_Main>());
	QVERIFY((isCurrentBlock<Block_Main, Block_IfTrue>()));
	QVERIFY(!(isCurrentBlock<Block_IfFalse, Block_IfTrue>()));
}

QTEST_MAIN(TestMakefile)

#include "test_makefile.moc"
