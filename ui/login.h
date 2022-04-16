#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "dialog.h"
#include "register.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:

    void on_registerPB_clicked();

    void on_loginpb_clicked();

private:
    Ui::Login *ui;
    Dialog *dialog;
    Register *reg;
};

#endif // LOGIN_H
