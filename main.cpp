#include "mainwindow.h"
#include <QApplication>
#include "readstationtbl.h"
#include <QDebug>
#include <writestationtbl.h>
#include <qfile.h>
#include <QProcess>
#include <QFileSystemWatcher>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QFileSystemWatcher watcher = new QFileSystemWatcher(this);
    watcher.addPath("/dev/sda1");
    WriteStationTBL m_wst;
    m_wst.show();

    return a.exec();
}
