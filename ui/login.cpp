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
    int index = usrs.indexOf(ui->lusrtext->text());//ui->lusrtext->text()获取lusrtext输入框的内容；并找该内容是否在usrs的序号，-1则不在
    if (index == -1){
        QMessageBox::critical(NULL, "critical message" , "The usrname is not existed！", QMessageBox::Ok );//弹窗
    }
    else {
        if (ui->lpwdtext->text() == pwds[index]){//获取密码输入，并判断是否等于数据库中的用户名对应的密码。
            this_usrname = ui->lusrtext->text();//输入的用户名

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
