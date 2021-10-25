#ifndef WPAGE_SELECTCUBEMXPROJECT_P_H
#define WPAGE_SELECTCUBEMXPROJECT_P_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <Qpe/c2c/Global>

namespace Ui {
class SelectCubeMxProject_WizardPage;
}

namespace Qpe
{

class SelectCubeMxProject_WizardPage;
class SelectCubeMxProject_WizardPagePrivate
{
	QPE_DECLARE_PUBLIC(SelectCubeMxProject_WizardPage)
protected:
	SelectCubeMxProject_WizardPage* q_ptr;
public:
	SelectCubeMxProject_WizardPagePrivate();
	~SelectCubeMxProject_WizardPagePrivate();

	void initialize();

	Ui::SelectCubeMxProject_WizardPage* ui;
};

} // namespace Qpe

#endif // WPAGE_SELECTCUBEMXPROJECT_P_H
