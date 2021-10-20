#include "makefile.h"

#include <QMap>
#include <QStringList>

namespace Qpe
{

class MakefileData : public QSharedData
{
public:
	MakefileData()
	{
	}
	~MakefileData()
	{
	}

	QMap<QString, QStringList> keys;
};

// ------------------------------------------------------------------------

Makefile::Makefile()
{
}

Makefile::~Makefile()
{
}

} // namespace Qpe
