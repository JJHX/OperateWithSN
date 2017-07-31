#include "mainwindow.h"
#include <QApplication>
#include "readstationtbl.h"
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    ReadStationTBL m_RST;

    return a.exec();
}
