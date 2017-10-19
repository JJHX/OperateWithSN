#include "writestationtbl.h"
#include <QSettings>
#include "ui_writestationtbl.h"
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDebug>
#include <qfileinfo.h>
#include <QHostAddress>
WriteStationTBL::WriteStationTBL(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WriteStationTBL)
{

    ui->setupUi(this);
    init();
//    {
//        updatePath.setFilter(QDir::AllDirs);

//        //!Identify the update folder
//        foreach (QString str, updatePath.entryList())
//        {
//            if (str.contains("update"))
//            {
//                QStringList strList = str.split("_");
//                projectName = strList.at(1);
//                qDebug()<<"projectName: "<<projectName;
//            }
//        }
//    }


    ShowCurrentConfig();
}

WriteStationTBL::~WriteStationTBL()
{
    delete ui;
    system("umount /mnt");
}

bool WriteStationTBL::findConfigfile()
{

    system("mount /dev/sda1 /mnt");
    //load ip tbl
    QFile *m_IPFile = new QFile("/mnt/update/IP.tbl");
    if (!m_IPFile->open(QIODevice::ReadOnly))
    {
        ui->label_FileStatus->setText("IP.tbl file is missing");
        ui->label_FileStatus->setVisible(1);
        return false;
    }
    else
    {
        //read config file choices for setting part
        QTextStream in(m_IPFile);
        while (!in.atEnd())
        {
            //read a line each time and record in qmap
            QString line = in.readLine();
            if (line.length() > 0 && line.at(0) != '#' && line.at(0) != ' ')
            {
                QStringList fields = line.split(QRegExp("\\s"),QString::SkipEmptyParts);
                while (fields.length()<5)//wipe ass
                    fields.append("---");
                if (!mList_carId.contains(fields.at(0)))
                {
                    mList_carId.append(fields.at(0));
                    m_map.insert(fields.at(0),fields.at(1));
                    if (fields.length()>2)
                        for ( int index =2 ; index < fields.length(); ++index)
                            m_map.insertMulti(fields.at(0),fields.at(index));
                }
                else
                {
                    for ( int index =1 ; index < fields.length(); ++index)
                        m_map.insertMulti(fields.at(0),fields.at(index));
                }
//                qDebug()<<fields;
            }
        }
        QString item;
        QStringList tmpStrLst;
        std::sort(mList_carId.begin(),mList_carId.end());
        foreach(item,mList_carId)
        {
            if (tmpStrLst.isEmpty())
                tmpStrLst.append(item);
            else if (tmpStrLst.last() != item)
                tmpStrLst.append(item);
        }
        QList<QString>::iterator itr = tmpStrLst.begin();
        for (;itr!=tmpStrLst.end();++itr)
            ui->comboBox_CarID->addItem(*itr);

//        qDebug()<<m_map;
//        qDebug()<<m_map.values("1");
    }
    m_IPFile->close();
    return true;
}


void WriteStationTBL::on_comboBox_CarID_currentIndexChanged(const QString &arg1)
{
   ui->comboBox_Terminal->clear();
   ui->comboBox_Terminal->addItem(m_map.values(arg1).at(9));
   ui->comboBox_Terminal->addItem(m_map.values(arg1).at(4));
}

void WriteStationTBL::on_comboBox_Terminal_currentIndexChanged(const QString &arg1)
{
    QList<QString> str = m_map.values(ui->comboBox_CarID->currentText());
    if (arg1 == "A")
    {
        ui->label_IP_eth0->setText("Eth0: " + str.at(7));
        ui->label_IP_eth1->setText("Eth1: " + str.at(6));
        ui->label_TodID->setText("TodID: " + str.at(8));
        ui->label_Subnet->setText("Subnet: " + str.at(5));
    }
    else
    {
        ui->label_IP_eth0->setText("Eth0: " + str.at(1));
        ui->label_IP_eth1->setText("Eth1: " + str.at(2));
        ui->label_TodID->setText("TodID: " + str.at(3));
        ui->label_Subnet->setText("Subnet: " + str.at(0));
    }
}

void WriteStationTBL::on_pushButton_Setting_Save_clicked()
{
    //!save current setting to Todconfig and update
    QSettings setting(destinationPath+"/"+projectName+"/tod.conf",QSettings::IniFormat);
    setting.beginGroup("Communication");
    setting.setValue("TodIface0Address",ui->label_IP_eth0->text().remove(0,6));
    setting.setValue("TodIface1Address",ui->label_IP_eth1->text().remove(0,6));
//    setting.setValue("TodNetmask",ui->label_currentSubnet->text().remove(0,9));
//    setting.setValue("TodPort",ui->label_currentTodPort->text().remove(0,9));
//    setting.setValue("TodId",ui->label_currentTodID->text().remove(0,7));
    ShowCurrentConfig();
}

void WriteStationTBL::ShowCurrentConfig()
{
    //!load tod.conf and display orignal settings
//    QSettings m_TodSetting("/mnt/TOD/tod.conf", QSettings::IniFormat);
    QString todPath(destinationPath);
    if (todPath.end() != "/")
        todPath.append("/"+projectName+"/tod.conf");
    if (QFile::exists(todPath))
    {
        ui->label_todFileStatus->setVisible(0);
        QSettings m_TodSetting(destinationPath+"/"+projectName+"/tod.conf", QSettings::IniFormat);
        m_TodSetting.beginGroup("Communication");
        ui->label_currentEth0->setText("Eth0: " + m_TodSetting.value("TodIface0Address").toString());
        ui->label_currentEth1->setText("Eth1: " + m_TodSetting.value("TodIface1Address").toString());
        ui->label_currentSubnet->setText("NetMask: " + m_TodSetting.value("TodNetmask").toString());
        ui->label_currentTodID->setText("TodID: " + m_TodSetting.value("TodId").toString());
        ui->label_currentTodPort->setText("TodPort: " + m_TodSetting.value("TodPort").toString());
    }
    else
    {
        ui->label_todFileStatus->setVisible(1);
        ui->label_todFileStatus->setText("tod.conf not found");
    }
}

void WriteStationTBL::on_pushButton_CarIDUp_pressed()
{
    int index = ui->comboBox_CarID->currentIndex();
    if (++index <= ui->comboBox_CarID->count()-1)
        ui->comboBox_CarID->setCurrentIndex(index);
}

void WriteStationTBL::on_pushButton_CarIDDown_clicked()
{
    int index = ui->comboBox_CarID->currentIndex();
    if (--index >= 0)
        ui->comboBox_CarID->setCurrentIndex(index);
}

void WriteStationTBL::on_pushButton_CarTermUp_clicked()
{
    int index = ui->comboBox_CarID->currentIndex();
    if (++index <= ui->comboBox_Terminal->count())
        ui->comboBox_Terminal->setCurrentIndex(index);
}

void WriteStationTBL::on_pushButton_CarTermDown_clicked()
{
    int index = ui->comboBox_Terminal->currentIndex();
    if (--index >= 0)
        ui->comboBox_Terminal->setCurrentIndex(index);
}

void WriteStationTBL::on_pushButton_Update_clicked()
{

    //!create new folder and name it as project
    //! EXP: "update_NCL1", the new folder on display would be named as "NCL1"

    if (!QFile::exists(destinationPath+projectName))
        QDir().mkdir(projectName);


    //!copy file over to destination folder//
    //                copyFile2Dest("./test/update_NCL1","./"+projectName+"/");
    if (copyFile2Dest(prjTargetPath,destinationPath+projectName+"/") )
        ui->pushButton_Update->setText("DONE");
    else
        ui->pushButton_Update->setText("ERROR");


}


/*        //!copy files to target
        updatePath.setFilter(QDir::AllEntries);
        QStringList fldContentList = updatePath.entryList();
//        qDebug()<<"The following content are in the folder:"<<fldContentList;
        foreach (QString str, fldContentList)
        {
            //skip the content start with "." ".." and the one end with "~"
            if (str.contains(".") || str.contains("..") || str.contains("~"))
                continue;
//            qDebug()<<"following output shall not include . .. or ~"<< str;

            //deal with directory
            QDir isStrDir("./test/"+str);
//            qDebug()<<"is"<<str <<"a directory?"<< isStrDir.exists();

            //copy each file to destination
            QFile destinationFile, sourceFile;
            QDir destination("./" + projectName);
            QString fileName(str);
            if (!isStrDir.exists())
            {

                sourceFile.setFileName("./test/"+str);
                destinationFile.setFileName("./"+projectName+"/"+str);
                sourceFile.copy(destinationFile.fileName());
            }

            else
            {
                QDir subFolder("./test/"+str+"/");
                subFolder.setFilter(QDir::AllEntries);
                QStringList subFldContentList = subFolder.entryList();
//                qDebug()<<"subfolder content:"<<subFldContentList;
                foreach (QString subStr, subFldContentList)
                {
                    if (str.contains(".") || str.contains("..") || str.contains("~"))
                        continue;
                    sourceFile.setFileName("./test/"+str+"/"+subStr);
                    destinationFile.setFileName("./"+projectName+"/"+subStr);
                    sourceFile.copy(destinationFile.fileName());
                }
            }
*/



bool WriteStationTBL::removeDir(const QString & directory)
{//!This function will empty the target directory and items under that directory
    qDebug()<<"Clean directory:"<<directory;

    bool result = false;
    QDir m_dir(directory);

    if (m_dir.exists())
    {
        foreach(QFileInfo info,m_dir.entryInfoList( QDir::NoDotAndDotDot | QDir::System | QDir::Files |  QDir::AllDirs)    )
        {
            if (info.isDir())
            {
                qDebug()<<"remove dir:absoluteFilePath "<< info.absoluteFilePath();
//                qDebug()<<"remove dir:absolutePath "<< info.absolutePath();
                result = removeDir(info.absoluteFilePath());
            }
            else
            {
                qDebug()<<"remove file:"<< info.absoluteFilePath();
                result = QFile::remove(info.absoluteFilePath());
            }
            if (!result)
                return result;
        }
        result = m_dir.rmdir(directory);
    }
    return result;
}

bool WriteStationTBL::copyFile2Dest(QString sourcePath, QString destPath)
{
    QDir sourceFolder(sourcePath);
    QDir destinationFolder(destPath);
    QFile destinationFile, sourceFile;
    QString fileName;
    bool result = false;
    if (sourceFolder.exists())
    {
        foreach (QFileInfo info, sourceFolder.entryInfoList(QDir::NoDotAndDotDot | QDir::System |
                                                            QDir::Files | QDir::AllDirs))
        {
            if (info.isDir())
            {
                //!create folder at dest?
                qDebug()<<"Folder detected:"<< info.absoluteFilePath();
                QString tempPath = info.baseName();
//                tempPath.remove(0,tempPath.length()-projectName.length());
                destinationFolder.mkdir(tempPath);
                tempPath.append("/");
                qDebug()<<"tempPath:"<< tempPath;
                result = copyFile2Dest(info.absoluteFilePath(),destPath+tempPath);
            }
            else
            {
                qDebug()<<"copy: "<<info.absoluteFilePath()<<" TO: "<<destPath+info.fileName();
                sourceFile.setFileName(info.absoluteFilePath());
                destinationFile.setFileName(destPath+info.fileName());
                sourceFile.copy(destinationFile.fileName());
            }
        }
    }
    return result;
}

bool WriteStationTBL::recurseAddDir(QString sourcePath, QString destPath)
{
    QDir sourceFolder(sourcePath);
    QDir destinationFolder(destPath);
    QFile destinationFile, sourceFile;
    QString fileName;
    bool result = false;
    if (sourceFolder.exists())
    {
        foreach (QFileInfo info, sourceFolder.entryInfoList(QDir::NoDotAndDotDot | QDir::System |
                                                            QDir::Files | QDir::AllDirs))
        {
//            QFileInfo fInfo(QString("%1%2").arg(sourcePath).arg(info));
//            QString fInfo( QString("%1%2").arg(sourcePath).arg(info));
            qDebug()<<"info.path() "<<info.path();
            qDebug()<<"info.canonicalFilePath "<<info.canonicalFilePath();
            qDebug()<<"info.completeSuffix() "<<info.completeSuffix();

//            if (info.isDir())
//            {
//                //!create folder at dest?
//                qDebug()<<"Folder detected:"<< info.absoluteFilePath();
//                QString tempPath = info.absoluteFilePath();
//                tempPath.remove(0,tempPath.length()-projectName.length());
//                tempPath.append("/");
//                qDebug()<<"tempPath:"<< tempPath;
//                result = copyFile2Dest(info.absoluteFilePath(),destPath);
//            }
//            else
//            {
//                qDebug()<<"copy: "<<info.absoluteFilePath()<<" TO: "<<destPath+info.fileName();
//                sourceFile.setFileName(info.absoluteFilePath());
//                destinationFile.setFileName(destPath+info.fileName());
//                sourceFile.copy(destinationFile.fileName());
//            }
        }
    }
    return result;
}

bool WriteStationTBL::rawClean(QString targetPath)
{
    QString command("rm -r ");
    command.append(targetPath);
    QByteArray ba = command.toLatin1();
    const char * c_str2 = ba.data();
    system(c_str2);
    return 1;
}

bool WriteStationTBL::changeInitialSetting()
{
    //! this function will modify the 99xinit-mft file on MFT display
    //! according to the new project name
    //! correct path shall place into file
    QString Xinit_path("/etc/X11/Xinit.d/99xinit-mft");
    QFile m_data(Xinit_path);
    m_data.open(QIODevice::Text | QIODevice::ReadWrite);
    QString dataText = m_data.readAll();


}

//bool WriteStationTBL::setHostAddress(QString ipAddress, QString netMask)
//{
//    bool result;
//    result = QHostAddress::setAddress(ipAddress);
//    return result;
//}

//bool WriteStationTBL::setHostAddress()
//{
//    bool result;
//    OWS_setting->beginGroup("Default");
//    if (OWS_setting->value("testMode") == 1)
//    {
//        QString m_ipAddr=OWS_setting->value("testIpAddress");
//        QString m_netMask=OWS_setting->value("testNetMask");
//        QHostAddress::setAddress(m_ipAddr);
//    }
//    return result;

//}


void WriteStationTBL::on_pushButton_clean_clicked()
{

    removeDir(destinationPath+projectName);
    QDir target(destinationPath);
    foreach (QFileInfo info, target.entryInfoList(QDir::NoDotAndDotDot | QDir::AllDirs) )
    {
        if (info.isDir())
            if(info.baseName()!= "OperateWithSN")
                removeDir(info.absoluteFilePath());
    }

}

bool WriteStationTBL::init()
{
    ui->label_FileStatus->setVisible(0);
    isConfigFileFound=findConfigfile();
    if (QFile::exists("/mnt/OWS.conf"))
    {
        OWS_setting = new QSettings("/mnt/OWS.conf",QSettings::IniFormat);
        OWS_setting->beginGroup("Settings");
        sourcePath=OWS_setting->value("sourcePath").toString();
        destinationPath=OWS_setting->value("destinationPath").toString();
        qDebug()<<"sourcePath:"<<sourcePath;
        qDebug()<<"destinationPath:"<<destinationPath;
//        OWS_setting->beginGroup("Default");
//        if (OWS_setting->value("testMode") == 1)
//        {
//            QString m_ipAddr=OWS_setting->value("testIpAddress");
//            QString m_netMask=OWS_setting->value("testNetMask");
//            QHostAdd

//        }

    }
    else
    {
        ui->label_FileStatus->setText("OWS.conf is missing from USB stick");
        ui->label_FileStatus->isVisible();
        ui->pushButton_Setting_Save->setDisabled(1);
        ui->pushButton_clean->setDisabled(1);
        ui->pushButton_Update->setDisabled(1);
        ui->pushButton_clean->setDisabled(1);
        ui->pushButton_CarIDDown->setDisabled(1);
        ui->pushButton_CarIDUp->setDisabled(1);
        ui->pushButton_CarTermDown->setDisabled(1);
        ui->pushButton_CarTermUp->setDisabled(1);
    }

    //configure update_#PROJECT_NAME folder
    QDir m_dir(sourcePath);
    foreach (QFileInfo info, m_dir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllDirs))
    {
        if (info.isDir())
            if (info.baseName().contains("_"))
            {
                qDebug()<<"info.baseName: "<<info.baseName();
                projectName = info.baseName().remove(0,7);
                qDebug()<<"projectName: "<<projectName;
                prjTargetPath=sourcePath+info.baseName();
                qDebug()<<"prjTargetPath"<<prjTargetPath;

            }
    }

    return 1;
}

void WriteStationTBL::on_pushButton_flash_clicked()
{
    ShowCurrentConfig();
}
