#ifndef USERDOCUMENTS_H
#define USERDOCUMENTS_H

#include <QDialog>

namespace Ui {
class userdocuments;
}

class userdocuments : public QDialog
{
    Q_OBJECT

public:
    explicit userdocuments(QWidget *parent = nullptr);
    ~userdocuments();

private:
    Ui::userdocuments *ui;
};

#endif // USERDOCUMENTS_H
