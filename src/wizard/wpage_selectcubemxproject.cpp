#include "wpage_selectcubemxproject.h"
#include "wpage_selectcubemxproject_p.h"
#include "ui_wpage_selectcubemxproject.h"

namespace Qpe
{

SelectCubeMxProject_WizardPagePrivate::SelectCubeMxProject_WizardPagePrivate()
	: ui(new Ui::SelectCubeMxProject_WizardPage)
{
}

SelectCubeMxProject_WizardPagePrivate::~SelectCubeMxProject_WizardPagePrivate()
{
	delete ui;
}

void SelectCubeMxProject_WizardPagePrivate::initialize()
{
	QA_Q();
	ui->setupUi(q);

	q->registerField("pathCubeMxProject", ui->pathLineEdit);
}

// ------------------------------------------------------------------------

SelectCubeMxProject_WizardPage::SelectCubeMxProject_WizardPage(
		QWidget* parent /* = nullptr */)
	: QWizardPage(parent)
	, d_ptr(new SelectCubeMxProject_WizardPagePrivate())
{
	QA_D();
	d->q_ptr = this;
	d->initialize();
}

SelectCubeMxProject_WizardPage::~SelectCubeMxProject_WizardPage()
{
}

} // namespace Qpe
