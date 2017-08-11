#include "writestationtbl.h"
#include <QSettings>
#include "ui_writestationtbl.h"
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDebug>
WriteStationTBL::WriteStationTBL(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WriteStationTBL)
{

    ui->setupUi(this);
//    isStationFileFound=findStationKey();
    isConfigFileFound=findConfigfile();
    ShowCurrentConfig();
}

WriteStationTBL::~WriteStationTBL()
{
    delete ui;
}

bool WriteStationTBL::findConfigfile()
{

    //load ip tbl
    QFile *m_IPFile = new QFile("./IP.tbl");
    if (!m_IPFile->open(QIODevice::ReadOnly))
    {
//        ui->textBrowser_IPFilePath->setText("Not found");
//        ui->textBrowser_IPFilePath->setStyleSheet("color:red");
        return false;
    }
    else
    {
//        ui->textBrowser_IPFilePath->setText(QDir::currentPath()+"/IP.tbl");
//        ui->textBrowser_IPFilePath->setStyleSheet("color:green");
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
                qDebug()<<fields;
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

        qDebug()<<m_map;
        qDebug()<<m_map.values("1");
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

void WriteStationTBL::on_pushButton_clicked()
{
    //!save current setting to Todconfig and update
    QSettings setting("tod.conf",QSettings::IniFormat);
    setting.beginGroup("Communication");
    setting.setValue("TodIface0Address",ui->label_IP_eth0->text().remove(0,6));
    setting.setValue("TodIface1Address",ui->label_IP_eth1->text().remove(0,6));
    setting.setValue("TodNetmask",ui->label_currentSubnet->text().remove(0,9));
    setting.setValue("TodPort",ui->label_currentTodPort->text().remove(0,9));
    setting.setValue("TodId",ui->label_currentTodID->text().remove(0,7));
    ShowCurrentConfig();
}

void WriteStationTBL::ShowCurrentConfig()
{
    //!load tod.conf and display orignal settings
//    QSettings m_TodSetting("/mnt/TOD/tod.conf", QSettings::IniFormat);
    QSettings m_TodSetting("tod.conf", QSettings::IniFormat);
    m_TodSetting.beginGroup("Communication");
    ui->label_currentEth0->setText("Eth0: " + m_TodSetting.value("TodIface0Address").toString());
    ui->label_currentEth1->setText("Eth1: " + m_TodSetting.value("TodIface1Address").toString());
    ui->label_currentSubnet->setText("NetMask: " + m_TodSetting.value("TodNetmask").toString());
    ui->label_currentTodID->setText("TodID: " + m_TodSetting.value("TodId").toString());
    ui->label_currentTodPort->setText("TodPort: " + m_TodSetting.value("TodPort").toString());
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
//    if (    (QFile::exists("./TOD/updateSft/demoTod") &
//             (QDir::exists("./TOD/updateSft/image"))  &
//             (QDir::exists("./TOD/updateSft/src"))    &
//             (QDir::exists("./TOD/updateSft/lang")))    )
        if (    QFile::exists("./TOD/updateSft/demoTod") )
    {
            system("cp -r ./TOD/updateSft/image /mnt");
            system("cp -r ./TOD/updateSft/src /mnt");
            system("cp -r ./TOD/updateSft/lang /mnt");
            system("cp ./TOD/updateSft/demoTod /mnt");
    }
    else
    {
        ui->pushButton_Update->setText("Lack of files");
    }

}
