#include "userdocuments.h"
#include "ui_userdocuments.h"

userdocuments::userdocuments(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userdocuments)
{
    ui->setupUi(this);
}

userdocuments::~userdocuments()
{
    delete ui;
}
