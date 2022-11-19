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

    // *** initial page ***
    ui->stackedWidget->setCurrentIndex(0);

    User *user;
    std::string tmpEmail;
    std::string tmpPassword;

    ui->lastNameTextEdit->hide();
    ui->lastNameAddLabel->hide();
    
    ui->signUpButton_3->hide();

    ui->showLabel_6->hide();
    ui->showLabel_4->hide();
    ui->eyeIconLabel_6->hide();
    ui->eyeIconLabel_4->hide();
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

void MainWindow::on_signUpButton_clicked()
{
    // change to sign in page
    ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_adminButton_clicked()
{
    // change to admin login
    ui->stackedWidget->setCurrentIndex(7);
}


void MainWindow::on_reportIssueButton_clicked()
{
    // change to report issue page
    ui->stackedWidget->setCurrentIndex(6);
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
    int userID = user->loginUser(userName, password, false);

    if (userID != 0)
    {
        ui->stackedWidget->setCurrentIndex(3);
        pushUserDetails(user);
    }

}

void MainWindow::on_adminLoginButton_clicked()
{
    std::string adminEmail = ui->adminEmailTextBox->toPlainText().toStdString();
    std::string adminPassword = ui->adminPasswordTextBox->toPlainText().toStdString();

    User *admin = new User();
    int adminID = admin->loginUser(adminEmail, adminPassword, true);

    if (adminID != 0) {
        // if admin exists change to admin page
        ui->stackedWidget->setCurrentIndex(8);

        // setup admin things maybe using this or custom solution
        pushUserDetails(admin);

    }
}


void MainWindow::on_signUpButton_2_clicked()
{
    tmpEmail = ui->emailAddTextEdit_6->toPlainText().toStdString();
    tmpPassword = ui->passwordTextEdit_7->toPlainText().toStdString();
    std::string confirmPassword = ui->passwordTextEdit_6->toPlainText().toStdString();

    if (tmpPassword != confirmPassword) {
        QMessageBox::warning(nullptr, "Error", "Passwords do not match");
        return;
    } else {

        // change email label width to 131px
        ui->emailAddTextEdit_6->setFixedWidth(131);

        ui->emailAddLabel_5->setText(QString::fromStdString("<html><head/><body><p><span style=\" font-size:10pt; font-weight:400;\">First Name</span></p></body></html>"));
        ui->passwordLabel_6->setText(QString::fromStdString("<html><head/><body><p><span style=\" font-size:10pt; font-weight:400;\">Date of birth</span></p></body></html>"));
        ui->passwordLabel_4->setText(QString::fromStdString("<html><head/><body><p><span style=\" font-size:10pt; font-weight:400;\">NHI number</span></p></body></html>"));

        ui->emailAddTextEdit_6->clear();
        ui->passwordTextEdit_7->clear();
        ui->passwordTextEdit_6->clear();

        ui->lastNameTextEdit->show();
        ui->lastNameAddLabel->show();

        ui->signUpButton_2->hide();
        ui->signUpButton_3->show();
    }

}


void MainWindow::on_signUpButton_3_clicked()
{
    // handles second part of sign up page
    User *user = new User();
    // createUser
    user->createUser(ui->emailAddTextEdit_6->toPlainText().toStdString(), ui->lastNameTextEdit->toPlainText().toStdString(), tmpEmail, tmpPassword, ui->passwordTextEdit_7->toPlainText().toStdString(), ui->passwordTextEdit_6->toPlainText().toStdString(), false);

    ui->stackedWidget->setCurrentIndex(3);
    pushUserDetails(user);
    
}


