#include "../headers/mainwindow.h"
#include <QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	//MainWindow* mainwindow;
   
    //this call to show is this weird because I use the Singleton pattern
    //access to this instance of MainWindow is needed latter to display
    //all the Navigation widgets(to make them this mainwindow central widget)
    MainWindow::instance()->show();

	return a.exec();
}
