#include "adminmanage.h"
#include "ui_adminmanage.h"
#include <QMessageBox>




adminmanage::adminmanage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adminmanage)
{
    ui->setupUi(this);
}

adminmanage::~adminmanage()
{
    delete ui;
}



void adminmanage::on_userinformation_view_clicked()
{


   ui->stackedWidget->setCurrentIndex(4);


}



