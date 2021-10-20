#ifndef MMAKEFILE_AKEFILE_H
#define MMAKEFILE_MAKEFILE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <QSharedData>

#include <Qpe/c2c/Global>

namespace Qpe
{

class MakefileData;
class QPE_C2C_EXPORT Makefile
{
public:
	Makefile();
	~Makefile();

private:
	QSharedDataPointer<MakefileData> d;
};

} // namespace Qpe

#endif // MMAKEFILE_MAKEFILE_H
