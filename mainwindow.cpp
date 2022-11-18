#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}






void MainWindow::on_LoginButton_login_clicked()
{
 QString email = ui->lineEdit_email->text();
 QString password = ui->lineEdit_password->text();

 if (email == "developer148@gmail.com" && password == "test"){
     QMessageBox ::information(this, "Login", "Username and password is correct");
     hide();
     adminManage = new adminmanage(this);
     adminManage->show();
 } else{
     QMessageBox::warning(this, "Login", "Username and Password is not correct");

}
}






void MainWindow::on_checkBox_stateChanged(int arg1)
{
   if (arg1 == 2){
       QMessageBox::information(this, "Title",ui->lineEdit_password->text());
   }
   else{
       qDebug() << "Unchecked";
   }
}

