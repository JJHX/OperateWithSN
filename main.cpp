#include "mainwindow.h"
#include <QApplication>
#include "readstationtbl.h"
#include <QDebug>
#include <writestationtbl.h>
#include <qfile.h>
#include <QProcess>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    QProcess m_process;
//    m_process.start("uname -r");
//    QByteArray readOutputLine(m_process.readAllStandardOutput());
//    qDebug()<<readOutputLine;
    WriteStationTBL m_wst;
    m_wst.show();
//    m_process.waitForFinished(300);
//    QString m_tmpStr = m_process.readLine(）;
//    if (m_tmpStr.at(0) == '4')
//    {
//        WriteStationTBL m_wst;
//        m_wst.show();
//    }
//    else if (m_tmpStr.at(0) == '2')
//    {
//        //!Determine if the usb stick pluged in
//        system("mount /dev/sda1 /mnt");
//        if (QFile::exists("/mnt/TOD/tod-comm-config.tbl"))
//        {

//            WriteStationTBL m_wst;
//            m_wst.show();
//        }
//        else
//        {
//            //!Setup ip address as TOD.conf in Display.
//            system("ifconfig eth0 192.168.230.101 netmask 255.255.255.0");
//            system("ifconfig eth1 10.0.1.1 netmask 255.255.255.0");
//        }
//    }

    return a.exec();
}
