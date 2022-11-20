#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "user.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    User *user;

private slots:
    void on_loginButton_clicked();
    void on_showProfile_clicked();
    void on_submitIssue_clicked();
    void pushUserDetails(User *user);

    void on_logout_clicked();
    void on_logout2_clicked();

    void on_loginToAccount_clicked();

    void on_loginButton2_22_clicked();

    void on_uploadButton_clicked();

    void on_submitButton_clicked();

    void on_signUpButton_clicked();

    void on_adminButton_clicked();

private:
    Ui::MainWindow *ui;
    void logout();
};
#endif // MAINWINDOW_H
