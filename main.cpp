#include "mainwindow.hh"
#include <QApplication>
#include <ctime>




int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    w.showFullScreen();


    return a.exec();
}
