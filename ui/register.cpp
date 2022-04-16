#include "register.h"
#include "ui_register.h"
#include <iostream>
#include <QMessageBox>
#include <QList>
#include <string>
using namespace std;
extern void get_usrs(QList<QString> &usrs,QList<QString> &pwds);
extern void write_usrs(QString line);

extern QList<QString> usrs,pwds;

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
}

Register::~Register()
{
    delete ui;
}

void Register::on_rok_clicked()
{
    std::cout << "ok" <<std::endl;//打印
    QString input_usr =  ui->rusrtext->text();//获取输入的用户名
    QString input_pwd1 =  ui->rpwdtext1->text();//获取输入的密码
    QString input_pwd2 =  ui->rpwdtext2->text();//获取输入的确定密码

    //下面是一些弹窗
    if(input_usr == NULL){
        QMessageBox::critical(0 , "critical message" , "Please input name！", QMessageBox::Ok );
    }
    else{
        if (usrs.indexOf(input_usr) != -1) {
            QMessageBox::critical(0 , "critical message" , "The name is existed！", QMessageBox::Ok );
        }
        else {//注册成功
            if (input_pwd1 == input_pwd2){
                //两次密码正确可以进行保存
                QString qline = input_usr;
                qline = qline.append(' ');
                qline = qline.append(input_pwd1);
                write_usrs(qline);

                QMessageBox::information(0 , "information message" , "Success！", QMessageBox::Ok );
                this->reject();
            }
            else {
                    QMessageBox::critical(0 , "critical message" , "passwd is error！", QMessageBox::Ok );
            }
        }
    }
}

void Register::on_rcancer_clicked()
{

}
