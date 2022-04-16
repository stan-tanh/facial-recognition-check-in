/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QLineEdit *lusrtext;
    QPushButton *loginpb;
    QLabel *lpwdlabel;
    QPushButton *registerPB;
    QLabel *loginlabel;
    QLabel *lusrlabel;
    QLineEdit *lpwdtext;

    void setupUi(QDialog *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QStringLiteral("Login"));
        Login->resize(332, 256);
        Login->setStyleSheet(QStringLiteral("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"));
        lusrtext = new QLineEdit(Login);
        lusrtext->setObjectName(QStringLiteral("lusrtext"));
        lusrtext->setGeometry(QRect(140, 90, 131, 28));
        lusrtext->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255)"));
        loginpb = new QPushButton(Login);
        loginpb->setObjectName(QStringLiteral("loginpb"));
        loginpb->setGeometry(QRect(160, 170, 100, 28));
        loginpb->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255)"));
        lpwdlabel = new QLabel(Login);
        lpwdlabel->setObjectName(QStringLiteral("lpwdlabel"));
        lpwdlabel->setGeometry(QRect(50, 130, 76, 20));
        lpwdlabel->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255)"));
        registerPB = new QPushButton(Login);
        registerPB->setObjectName(QStringLiteral("registerPB"));
        registerPB->setGeometry(QRect(50, 170, 81, 28));
        registerPB->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255)"));
        loginlabel = new QLabel(Login);
        loginlabel->setObjectName(QStringLiteral("loginlabel"));
        loginlabel->setGeometry(QRect(105, 40, 121, 20));
        loginlabel->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255)"));
        lusrlabel = new QLabel(Login);
        lusrlabel->setObjectName(QStringLiteral("lusrlabel"));
        lusrlabel->setGeometry(QRect(50, 90, 76, 20));
        lusrlabel->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255)"));
        lpwdtext = new QLineEdit(Login);
        lpwdtext->setObjectName(QStringLiteral("lpwdtext"));
        lpwdtext->setGeometry(QRect(140, 130, 131, 28));
        lpwdtext->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255)"));
        lpwdtext->setEchoMode(QLineEdit::Password);

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QDialog *Login)
    {
        Login->setWindowTitle(QApplication::translate("Login", "Dialog", nullptr));
        loginpb->setText(QApplication::translate("Login", "login", nullptr));
        lpwdlabel->setText(QApplication::translate("Login", "passwd", nullptr));
        registerPB->setText(QApplication::translate("Login", "register", nullptr));
        loginlabel->setText(QApplication::translate("Login", " Administrator login", nullptr));
        lusrlabel->setText(QApplication::translate("Login", "name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
