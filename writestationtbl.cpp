#include "writestationtbl.h"
#include "ui_writestationtbl.h"

WriteStationTBL::WriteStationTBL(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WriteStationTBL)
{
    ui->setupUi(this);
}

WriteStationTBL::~WriteStationTBL()
{
    delete ui;
}
