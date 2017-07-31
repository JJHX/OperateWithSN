/********************************************************************************
** Form generated from reading UI file 'writestationtbl.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WRITESTATIONTBL_H
#define UI_WRITESTATIONTBL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QTableView>

QT_BEGIN_NAMESPACE

class Ui_WriteStationTBL
{
public:
    QDialogButtonBox *buttonBox;
    QTableView *StationTable;
    QLineEdit *LE_StationName;
    QLineEdit *LE_Color;

    void setupUi(QDialog *WriteStationTBL)
    {
        if (WriteStationTBL->objectName().isEmpty())
            WriteStationTBL->setObjectName(QString::fromUtf8("WriteStationTBL"));
        WriteStationTBL->resize(640, 480);
        buttonBox = new QDialogButtonBox(WriteStationTBL);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(10, 440, 621, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        StationTable = new QTableView(WriteStationTBL);
        StationTable->setObjectName(QString::fromUtf8("StationTable"));
        StationTable->setGeometry(QRect(50, 170, 431, 251));
        LE_StationName = new QLineEdit(WriteStationTBL);
        LE_StationName->setObjectName(QString::fromUtf8("LE_StationName"));
        LE_StationName->setGeometry(QRect(50, 50, 171, 41));
        LE_Color = new QLineEdit(WriteStationTBL);
        LE_Color->setObjectName(QString::fromUtf8("LE_Color"));
        LE_Color->setGeometry(QRect(50, 110, 171, 41));

        retranslateUi(WriteStationTBL);
        QObject::connect(buttonBox, SIGNAL(accepted()), WriteStationTBL, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), WriteStationTBL, SLOT(reject()));

        QMetaObject::connectSlotsByName(WriteStationTBL);
    } // setupUi

    void retranslateUi(QDialog *WriteStationTBL)
    {
        WriteStationTBL->setWindowTitle(QApplication::translate("WriteStationTBL", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WriteStationTBL: public Ui_WriteStationTBL {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WRITESTATIONTBL_H
