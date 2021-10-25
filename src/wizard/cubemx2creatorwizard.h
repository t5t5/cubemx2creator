#ifndef CUBEMX2CREATORWIZARD_H
#define CUBEMX2CREATORWIZARD_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <QWizard>

namespace Qpe
{

class Cubemx2CreatorWizard : public QWizard
{
	Q_OBJECT
public:
	Cubemx2CreatorWizard(QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
	~Cubemx2CreatorWizard();
};

} // namespace Qpe

#endif // CUBEMX2CREATORWIZARD_H
