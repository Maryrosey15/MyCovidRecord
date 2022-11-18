#ifndef USERINFORMATION_H
#define USERINFORMATION_H

#include <QDialog>

namespace Ui {
class userinformation;
}

class userinformation : public QDialog
{
    Q_OBJECT

public:
    explicit userinformation(QWidget *parent = nullptr);
    ~userinformation();

private:
    Ui::userinformation *ui;
};

#endif // USERINFORMATION_H
