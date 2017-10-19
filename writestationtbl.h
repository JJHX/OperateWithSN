#ifndef WRITESTATIONTBL_H
#define WRITESTATIONTBL_H

#include <QDialog>
#include <QList>
#include <QMap>
#include <QString>
#include <QDir>
#include <QSettings>

namespace Ui {
class WriteStationTBL;
}

class WriteStationTBL : public QDialog
{
    Q_OBJECT

public:
    explicit WriteStationTBL(QWidget *parent = 0);
    ~WriteStationTBL();

    bool findConfigfile();
private slots:

    void on_comboBox_CarID_currentIndexChanged(const QString &arg1);

    void on_comboBox_Terminal_currentIndexChanged(const QString &arg1);

    void on_pushButton_Setting_Save_clicked();

    void ShowCurrentConfig();

    void on_pushButton_CarIDUp_pressed();

    void on_pushButton_CarIDDown_clicked();

    void on_pushButton_CarTermUp_clicked();

    void on_pushButton_CarTermDown_clicked();

    void on_pushButton_Update_clicked();


    void on_pushButton_clean_clicked();

    void on_pushButton_flash_clicked();

private:
    Ui::WriteStationTBL *ui;
//    bool findStationKey();//!This method will find stationKey.tbl in current folder and display it path on UI
    bool init();
    bool findIPfile();
    bool removeDir(const QString &directory );
    bool copyFile2Dest(QString sourcePath, QString destPath); //copy all files from source to destination
    bool recurseAddDir(QString sourcePath, QString destPath);
    bool rawClean(QString targetPath);
//    bool setHostAddress(QString ipAddress, QString netMask);//!need revisit
//    bool setHostAddress();                                  //!need revisit
    bool changeInitialSetting();

    bool isStationFileFound;
    bool isConfigFileFound;

    QList<QString> mList_carId,mList_Terminal,mList_subnetMask;
    QMap<QString,QString> m_map;//pair id with related info

    QString projectName;
    QSettings* OWS_setting;//("/mnt/update/OWS.conf",QSettings::IniFormat);
    QString sourcePath;//(OWS_setting.value("sourcePath").toString());
    QString destinationPath;//(OWS_setting.value("destinationPath").toString());
    QString prjTargetPath;

};

#endif // WRITESTATIONTBL_H
