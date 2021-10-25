#ifndef WPAGE_SELECTCUBEMXPROJECT_H
#define WPAGE_SELECTCUBEMXPROJECT_H

#include <QScopedPointer>
#include <QWizardPage>

#include <Qpe/c2c/Global>

namespace Qpe
{

class SelectCubeMxProject_WizardPagePrivate;
class SelectCubeMxProject_WizardPage : public QWizardPage
{
	Q_OBJECT
	QPE_DECLARE_PRIVATE(SelectCubeMxProject_WizardPage)
protected:
	QScopedPointer<SelectCubeMxProject_WizardPagePrivate> d_ptr;
public:
	SelectCubeMxProject_WizardPage(QWidget* parent = nullptr);
	~SelectCubeMxProject_WizardPage();
};

} // namespace Qpe

#endif // WPAGE_SELECTCUBEMXPROJECT_H
