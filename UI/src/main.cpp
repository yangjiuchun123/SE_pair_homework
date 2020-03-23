#include "UI.h"
#include <QtWidgets/QApplication>
#include <QFileDialog>
#include <qpushbutton.h>
#include <iostream>
int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	calculate* dialog = new calculate();
	dialog->show();
	return a.exec();
}
