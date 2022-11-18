#ifndef ADMINMANAGE_H
#define ADMINMANAGE_H

#include <QDialog>

namespace Ui {
class adminmanage;
}

class adminmanage : public QDialog
{
    Q_OBJECT

public:
    explicit adminmanage(QWidget *parent = nullptr);
    ~adminmanage();

private slots:


    void on_userinformation_view_clicked();






    void on_userdocuments_view_clicked();

private:
    Ui::adminmanage *ui;
};

#endif // ADMINMANAGE_H
