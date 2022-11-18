#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>


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

void MainWindow::on_loginButton_clicked()
{

}


void MainWindow::on_saveButton_clicked()
{
    QMessageBox::about(this, "Message", "Changes saved");
}


void MainWindow::on_uploadButton_clicked()
{
    QMessageBox::about(this, "Message", "Unique QR code uploaded");
}


void MainWindow::on_generateButton_clicked()
{
    QMessageBox::about(this, "Message", "QR code generated");
}

