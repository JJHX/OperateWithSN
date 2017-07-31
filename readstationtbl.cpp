/*
 *This protocol is use to test and design new station name system,
 *It will read the file from local tbl file, and map station name with it's infomation
 * <hjj17by@163.com Junjie He>
 */
#include "readstationtbl.h"
#include "qfile.h"
#include <qdebug.h>
#include <qlist.h>
#include <QTextStream>
#include <QStringList>
#include <QMap>
/*      Standard table example
 *
        # First line: station
        # S
        # STATION_NAME	COLOR	ID
        NextStation	255,255,255
        FinalStation	255,255,255
        ---	51,102,255
        ---	0,0,0
        1	SHG	51,102,255
        2	KMH	51,102,255
        3	CJR	51,102,255
        4	ZJR	51,102,255
        6	LSA	51,102,255
*/
ReadStationTBL::ReadStationTBL()
{
    qDebug()<<"Running without inputs";
    readTblFile();
    printKeyValue("1");
    printKeyValue("2");
    printKeyValue("654");
}

void ReadStationTBL::readTblFile()
{
    //!Read station table from file
    //!Create a map from those data
    QFile *m_StationFile= new QFile("/home/chegg/Desktop/OperateWithSN/stationKey.tbl");
    if (!m_StationFile->open(QIODevice::ReadOnly))
    {
        qDebug()<<"stationwidget.tbl is not loaded";
    }
    QTextStream in(m_StationFile);

    while (!in.atEnd())
    {
        QString line = in.readLine();
        if (line.length() > 0 && line.at(0) != '#')
        {
//            qDebug()<<"read line: "<<line;
            QStringList fields = line.split(QRegExp("\\s"),QString::SkipEmptyParts);
//            qDebug()<<"split into:"<<fields;
//            qDebug()<<"field[0]:"<<fields.at(0);//<<"field[1]"<<fields.at(1);
            m_stationListID.append(fields.at(0));
            m_stationListName.append(fields.at(1));
            if (fields.length()>2)
                m_stationListColor.append(fields.at(2));
            else
                m_stationListColor.append(0);
        }
    }

    for (int index = 0; index < m_stationListID.count(); index ++)
    {
        m_StationMap[m_stationListID.at(index)] = m_stationListName.at(index);
//        qDebug()<<"map:"<<m_stationListID.at(index)<<" with "<<m_stationListName.at(index);
        m_StationMap.insertMulti(m_stationListID.at(index),m_stationListColor.at(index));
    }

}

bool ReadStationTBL::checkInclude(QString str)
{
 if (m_stationListID.contains(str))
     return true;
 else
     return false;
}

QList<QString> ReadStationTBL::checkKeyValue(QString str)
{
    //!This function will return value(s) pair to the key
    //!From most recent to least reacent order
    QList<QString> result;
    if (checkInclude(str))
        result.append(m_StationMap.values(str));
    else
    {
        qDebug()<<"checkKeyValue fail";
        result<<"0,0,0"<<"---";
    }


    return result;
}

void ReadStationTBL::printKeyValue(QString str)
{
    QList<QString> tmpVal;
    tmpVal.append(checkKeyValue(str));

    if(tmpVal.size()>0)
    {
        qDebug()<<"Key->"<<str<<"Value(s)";
        for (int i=0; i< tmpVal.size(); ++i)
        {
            qDebug()<<i<<"="<<tmpVal.at(i);
        }
    }
    else
        qDebug()<<"not a proprate approach";

}

