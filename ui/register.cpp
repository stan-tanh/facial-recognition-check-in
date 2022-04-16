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
    std::cout << "ok" <<std::endl;//Print
    QString input_usr =  ui->rusrtext->text();//Get the entered username
    QString input_pwd1 =  ui->rpwdtext1->text();//Get the entered password
    QString input_pwd2 =  ui->rpwdtext2->text();//Get the entered OK password

    //Here are some pop-ups
    if(input_usr == NULL){
        QMessageBox::critical(0 , "critical message" , "Please input name！", QMessageBox::Ok );
    }
    else{
        if (usrs.indexOf(input_usr) != -1) {
            QMessageBox::critical(0 , "critical message" , "The name is existed！", QMessageBox::Ok );
        }
        else {//Register successfully
            if (input_pwd1 == input_pwd2){
                //Two correct passwords can be saved
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
