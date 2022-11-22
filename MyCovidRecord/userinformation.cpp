#include "userinformation.h"
#include "ui_userinformation.h"

userinformation::userinformation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userinformation)
{
    ui->setupUi(this);
}

userinformation::~userinformation()
{
    delete ui;
}
