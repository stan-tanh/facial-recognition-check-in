/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action2015_04_25;
    QWidget *centralWidget;
    QPushButton *GetSamples;
    QLabel *label111;
    QPushButton *StartTrain;
    QPushButton *StartRecognize;
    QPushButton *start;
    QPushButton *pushButton;
    QLabel *samples;
    QLabel *trainer;
    QTableWidget *tableWidget;
    QLabel *nowtime;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(932, 589);
        MainWindow->setStyleSheet(QStringLiteral("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"));
        action2015_04_25 = new QAction(MainWindow);
        action2015_04_25->setObjectName(QStringLiteral("action2015_04_25"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QStringLiteral("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"));
        GetSamples = new QPushButton(centralWidget);
        GetSamples->setObjectName(QStringLiteral("GetSamples"));
        GetSamples->setGeometry(QRect(30, 260, 111, 51));
        GetSamples->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255)"));
        label111 = new QLabel(centralWidget);
        label111->setObjectName(QStringLiteral("label111"));
        label111->setGeometry(QRect(150, 60, 480, 490));
        StartTrain = new QPushButton(centralWidget);
        StartTrain->setObjectName(QStringLiteral("StartTrain"));
        StartTrain->setGeometry(QRect(30, 380, 111, 51));
        StartTrain->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255)"));
        StartRecognize = new QPushButton(centralWidget);
        StartRecognize->setObjectName(QStringLiteral("StartRecognize"));
        StartRecognize->setGeometry(QRect(30, 150, 111, 51));
        StartRecognize->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255)"));
        start = new QPushButton(centralWidget);
        start->setObjectName(QStringLiteral("start"));
        start->setGeometry(QRect(30, 60, 111, 51));
        start->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255)"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(30, 500, 100, 51));
        pushButton->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255)"));
        samples = new QLabel(centralWidget);
        samples->setObjectName(QStringLiteral("samples"));
        samples->setGeometry(QRect(40, 310, 91, 41));
        trainer = new QLabel(centralWidget);
        trainer->setObjectName(QStringLiteral("trainer"));
        trainer->setGeometry(QRect(40, 430, 91, 41));
        tableWidget = new QTableWidget(centralWidget);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        if (tableWidget->rowCount() < 20)
            tableWidget->setRowCount(20);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(640, 60, 261, 491));
        tableWidget->setStyleSheet(QStringLiteral("background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0.0436893, y2:0.0284091, stop:0 rgba(0, 0, 0, 255), stop:0.912621 rgba(255, 255, 255, 255))"));
        tableWidget->setLineWidth(1);
        tableWidget->setAutoScrollMargin(16);
        tableWidget->setRowCount(20);
        tableWidget->setColumnCount(3);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget->horizontalHeader()->setDefaultSectionSize(64);
        tableWidget->horizontalHeader()->setMinimumSectionSize(64);
        tableWidget->verticalHeader()->setDefaultSectionSize(30);
        tableWidget->verticalHeader()->setMinimumSectionSize(24);
        nowtime = new QLabel(centralWidget);
        nowtime->setObjectName(QStringLiteral("nowtime"));
        nowtime->setGeometry(QRect(150, 10, 701, 41));
        nowtime->setTextFormat(Qt::AutoText);
        nowtime->setScaledContents(false);
        nowtime->setAlignment(Qt::AlignCenter);
        nowtime->setIndent(-3);
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        action2015_04_25->setText(QApplication::translate("MainWindow", "2015.04.25", nullptr));
        GetSamples->setText(QApplication::translate("MainWindow", "GET SAMPLES", nullptr));
        label111->setText(QString());
        StartTrain->setText(QApplication::translate("MainWindow", "START TRAIN", nullptr));
        StartRecognize->setText(QApplication::translate("MainWindow", "RECOGNIZE", nullptr));
        start->setText(QApplication::translate("MainWindow", "START", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "QUIT", nullptr));
        samples->setText(QString());
        trainer->setText(QString());
        nowtime->setText(QApplication::translate("MainWindow", "start", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
