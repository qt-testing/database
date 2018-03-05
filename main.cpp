#include "database.h"
#include "maindialog.h"
#include <QApplication>

int main(int argc, char **argv)
{
	QApplication a(argc, argv);

	MainDialog dlg;
	dlg.show();

	return a.exec();
}
