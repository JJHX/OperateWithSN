#ifndef READSTATIONTBL_H
#define READSTATIONTBL_H

#include <QObject>
#include <QList>
#include <QMap>
class ReadStationTBL
{
public:
    ReadStationTBL();
    QMap<QString,QString> m_StationMap;

protected:
    void readTblFile();
    bool checkInclude(QString str);
    void printKeyValue(QString str);
    QList<QString> checkKeyValue(QString str);
    QList<QString> m_stationListID;
    QList<QString> m_stationListName;
    QList<QString> m_stationListColor;


};

#endif // READSTATIONTBL_H
