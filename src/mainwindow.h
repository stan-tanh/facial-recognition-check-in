#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <QTimer>
#include <QThread>

#include "thread_run.h"

//#include "dialog.h"
#include "login.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTimer *timer;
    QTimer *timerlabel; //计时显示状态
    QTimer *timer_now;
    QTimer *timer_item;


private slots:

    void on_StartRecognize_clicked();

    void on_start_clicked();

    void on_GetSamples_clicked();

    void on_StartTrain_clicked();

    void ShowImg_Label();

    void ShowLabels();

    void on_pushButton_clicked();

    void updateTime();

    void updateItem();

private:
    Ui::MainWindow *ui;
    ThreadDeal *thread1;

//    Dialog *dialog;
    Login *login;
};


#endif // MAINWINDOW_H
