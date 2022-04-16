#include "login.h"
#include "ui_login.h"

#include <iostream>
#include <string>
#include <QMessageBox>
#include <QList>
using namespace std;
extern void get_usrs(QList<QString> &usrs,QList<QString> &pwds);
QList<QString> usrs,pwds;
Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}


void Login::on_registerPB_clicked()
{
    reg = new Register;
    reg->show();
}

void Login::on_loginpb_clicked()
{
    get_usrs(usrs,pwds);
    QString this_usrname;
    int index = usrs.indexOf(ui->lusrtext->text());//ui->lusrtext->text()Get the content of the lusrtext input box; and find if the content is in the serial number of usrs, -1 is not
    if (index == -1)
    {
        QMessageBox::critical(NULL, "critical message" , "The usrname is not existed！", QMessageBox::Ok );//pop-up window
    }
    else {
        if (ui->lpwdtext->text() == pwds[index]){//Get the password input and determine if it is equal to the password corresponding to the username in the database.
            this_usrname = ui->lusrtext->text();//Username entered

            //开启登陆成功后的窗口
            dialog = new Dialog;
            dialog ->show();

            this->close();//关闭现在的窗口
            delete ui;//释放内存
        }
        else {
            QMessageBox::critical(NULL, "critical message" , "Passwd error,Input again！", QMessageBox::Ok );//弹窗密码错误
        }
    }

}
