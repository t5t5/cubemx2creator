#include <QApplication>

#include "cubemx2creatorwizard.h"
#include "wpage_selectcubemxproject.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	Qpe::Cubemx2CreatorWizard wizard;
	wizard.addPage(new Qpe::SelectCubeMxProject_WizardPage());

	wizard.setWindowTitle("CubeMX to QtCreator converter.");
	wizard.show();

	return a.exec();
}
