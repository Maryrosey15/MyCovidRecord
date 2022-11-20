#include "mainwindow.h"
#include "database.h"
#include "user.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);
    User *user;
//    connect(clickViewProfile)
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_showProfile_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);


}


void MainWindow::on_submitIssue_clicked()
{
    QString issueText = ui->issueTextBox->toPlainText();
    std::cout << issueText.toStdString();

    // store issue somewhere
}

void MainWindow::pushUserDetails(User *user) {
    // Name: Mary Rose Garcia
    // Date of Birth: October 2, 1988
    // NHI: ACB1234

    database *db = new database();
    db->databaseConnect();
    ui->userPersonalInfo->setText("Name: " + QString::fromStdString(user->firstName) + " " + QString::fromStdString(user->lastName) + "<br>" + "Date of Birth: " + QString::fromStdString(user->dateOfBirth) + "<br>" + "NHI: " + QString::fromStdString(user->NHI));
    ui->name->setText("<html><head/><body><p><span style=\" font-size:10pt; font-weight:700; color:#002e6e;\">"+ QString::fromStdString(user->firstName) + " " + QString::fromStdString(user->lastName)+"</span></p></body></html>");
    ui->name_2->setText("<html><head/><body><p><span style=\" font-size:10pt; font-weight:700; color:#002e6e;\">"+ QString::fromStdString(user->firstName) + " " + QString::fromStdString(user->lastName)+"</span></p></body></html>");
    
    std::string vaccineRecordText;
    for (auto it = user->vaccineRecord.begin(); it != user->vaccineRecord.end(); ++it) {
        vaccineRecordText += it->first + ": " + it->second + "<br>";
    }
    ui->vaccineRecord->setText("<html><head/><body><p><span style=\" font-size:10pt; color:#002e6e;\">" + QString::fromStdString(vaccineRecordText) + "</span></p></body></html>");
    ui->vaccineRecord_2->setText("<html><head/><body><p><span style=\" font-size:10pt; color:#002e6e;\">" + QString::fromStdString(vaccineRecordText) + "</span></p></body></html>");
    
    std::string testResultsText;
    for (auto it = user->testResults.begin(); it != user->testResults.end(); ++it) {
        testResultsText += it->first + ": " + it->second + "<br>";
    }
    ui->testRecord->setText("<html><head/><body><p><span style=\" font-size:10pt; color:#002e6e;\">" + QString::fromStdString(testResultsText) + "</span></p></body></html>");
    // user->vaccineRecord - std::map<std::string, std::string>
    // <html><head/><body><p><span style=" font-size:10pt; color:#002e6e;">Booster 1:   18/03/2022</span></p></body></html>
}

void MainWindow::on_logout_clicked()
{
    logout();
}


void MainWindow::on_logout2_clicked()
{
    logout();
}

void MainWindow::logout() {
    // delete user object
    user->logoutUser();

    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_loginToAccount_clicked()
{

    std::string userName = ui->emailAddTextEdit->toPlainText().toStdString();
    std::string password = ui->passwordTextEdit->toPlainText().toStdString();

    // create new user object
    User *user = new User();
    // check if user exists in database
    int userID = user->loginUser(userName, password);

    if (userID != -1)
    {
        ui->stackedWidget->setCurrentIndex(3);
        pushUserDetails(user);
    }


    // createUser
//    user->createUser("John", "Smith", "johnsmith@gmail.com", "password", "01/01/2000", "ABCD1234", false);


}


void MainWindow::on_loginButton2_22_clicked()
{
    QMessageBox::about(this,"Message", "Changes saved");
}


void MainWindow::on_uploadButton_clicked()
{
    QMessageBox::about(this,"Message", "Uploaded succesfully!");
}


void MainWindow::on_submitButton_clicked()
{
    QMessageBox::about(this,"Message", "Report submitted!");
}

