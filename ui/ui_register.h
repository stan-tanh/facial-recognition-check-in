/********************************************************************************
** Form generated from reading UI file 'register.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTER_H
#define UI_REGISTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Register
{
public:
    QPushButton *rcancer;
    QLineEdit *rpwdtext2;
    QLineEdit *rpwdtext1;
    QLabel *rpwd1lb;
    QLabel *rusrname;
    QLineEdit *rusrtext;
    QLabel *rpwd2lb;
    QPushButton *rok;
    QLabel *register_2;

    void setupUi(QDialog *Register)
    {
        if (Register->objectName().isEmpty())
            Register->setObjectName(QStringLiteral("Register"));
        Register->resize(361, 280);
        Register->setStyleSheet(QStringLiteral("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"));
        rcancer = new QPushButton(Register);
        rcancer->setObjectName(QStringLiteral("rcancer"));
        rcancer->setGeometry(QRect(100, 200, 61, 28));
        rcancer->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255)"));
        rpwdtext2 = new QLineEdit(Register);
        rpwdtext2->setObjectName(QStringLiteral("rpwdtext2"));
        rpwdtext2->setGeometry(QRect(152, 160, 141, 28));
        rpwdtext2->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255)"));
        rpwdtext2->setEchoMode(QLineEdit::Password);
        rpwdtext1 = new QLineEdit(Register);
        rpwdtext1->setObjectName(QStringLiteral("rpwdtext1"));
        rpwdtext1->setGeometry(QRect(152, 120, 141, 28));
        rpwdtext1->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255)"));
        rpwdtext1->setEchoMode(QLineEdit::Password);
        rpwd1lb = new QLabel(Register);
        rpwd1lb->setObjectName(QStringLiteral("rpwd1lb"));
        rpwd1lb->setGeometry(QRect(45, 120, 91, 20));
        rpwd1lb->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255)"));
        rusrname = new QLabel(Register);
        rusrname->setObjectName(QStringLiteral("rusrname"));
        rusrname->setGeometry(QRect(45, 80, 91, 20));
        rusrname->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255)"));
        rusrtext = new QLineEdit(Register);
        rusrtext->setObjectName(QStringLiteral("rusrtext"));
        rusrtext->setGeometry(QRect(152, 80, 141, 28));
        rusrtext->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255)"));
        rpwd2lb = new QLabel(Register);
        rpwd2lb->setObjectName(QStringLiteral("rpwd2lb"));
        rpwd2lb->setGeometry(QRect(45, 160, 91, 20));
        rpwd2lb->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255)"));
        rok = new QPushButton(Register);
        rok->setObjectName(QStringLiteral("rok"));
        rok->setGeometry(QRect(200, 200, 61, 28));
        rok->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255)"));
        register_2 = new QLabel(Register);
        register_2->setObjectName(QStringLiteral("register_2"));
        register_2->setGeometry(QRect(120, 40, 121, 20));
        register_2->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255)"));

        retranslateUi(Register);

        QMetaObject::connectSlotsByName(Register);
    } // setupUi

    void retranslateUi(QDialog *Register)
    {
        Register->setWindowTitle(QApplication::translate("Register", "Dialog", nullptr));
        rcancer->setText(QApplication::translate("Register", "ok", nullptr));
        rpwd1lb->setText(QApplication::translate("Register", "password", nullptr));
        rusrname->setText(QApplication::translate("Register", "new usrname", nullptr));
        rpwd2lb->setText(QApplication::translate("Register", "password again", nullptr));
        rok->setText(QApplication::translate("Register", "cancle", nullptr));
        register_2->setText(QApplication::translate("Register", " New Administrator ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Register: public Ui_Register {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTER_H
