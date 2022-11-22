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

   ui->stackedWidget->setCurrentIndex(3);

}

void adminmanage::on_userdocuments_view_clicked()
{
       ui->stackedWidget->setCurrentIndex(2);
}








void adminmanage::on_pushButton_5_clicked()
{
   ui->stackedWidget->setCurrentIndex(7);
}


void adminmanage::on_pushButton_6_clicked()
{
  ui->stackedWidget->setCurrentIndex(7);
}

