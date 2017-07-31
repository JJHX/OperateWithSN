#ifndef WRITESTATIONTBL_H
#define WRITESTATIONTBL_H

#include <QDialog>

namespace Ui {
class WriteStationTBL;
}

class WriteStationTBL : public QDialog
{
    Q_OBJECT

public:
    explicit WriteStationTBL(QWidget *parent = 0);
    ~WriteStationTBL();

private:
    Ui::WriteStationTBL *ui;
};

#endif // WRITESTATIONTBL_H
