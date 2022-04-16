#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <opencv2/opencv.hpp>
#include "people_face.h"
#include<QDateTime>
#include <unistd.h>
#include <QPalette>
extern QString face_result;
extern cv::Mat image_show;
extern int flag_dealok;
extern int function_choose;
//UI operations in Qt, such as QMainWindow, QWidget creation, operation, can only be in the main thread.
//This limitation means that you cannot use QDialog, QMessageBox, etc in new threads. Want to pop up a dialog box warning about copying files in a new thread? Yes, but you must pass the error message to the main thread, which implements the dialog box warning.
//So the general idea is that the main thread is responsible for providing the interface, while sub-threads are responsible for a single task without UI, interacting with the main thread through a "signal-slot."

//QPalette bgpal = palette();

//bgpal.setColor (QPalette::Background, QColor (0, 0 , 0, 255));

////bgpal.setColor (QPalette::Background, Qt::transparent);

//bgpal.setColor (QPalette::Foreground, QColor (255,255,255,255)); setPalette (bgpal);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Initialize it
    timerlabel = new QTimer(this);
    timer = new QTimer(this);
    timer_now = new QTimer(this);
    timer_item = new QTimer(this);

    thread1 = new ThreadDeal;

    timer_now->start(1000);
    connect(timer_now,SIGNAL(timeout()),this,SLOT(updateTime()));

    timer_item->start(100);
    connect(timer_item,SIGNAL(timeout()),this,SLOT(updateItem()));

    connect(timer,SIGNAL(timeout()),this,SLOT(ShowImg_Label()));    //Time display
    connect(timerlabel,SIGNAL(timeout()),this,SLOT(ShowLabels()));    //Time display

    ui->samples->setText(" ");
    ui->trainer->setText(" ");

    ui->StartTrain->setEnabled(0);
    ui->GetSamples->setEnabled(0);
    ui->StartRecognize->setEnabled(0);

    //table widght
    QStringList headList;
    headList<<"name"<<"time";
    ui->tableWidget->setColumnCount(2);//Set the number of columns
    ui->tableWidget->setRowCount(100);//Set the number of columns
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//Adaptive column width
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//Tables cannot be edited
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//The entire row is selected
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//Set this parameter to only one option
    ui->tableWidget->verticalHeader()->setVisible(false);   //Hide the list header
    //ui->tableWidget->horizontalHeader()->setVisible(false); //Hide the row header
    ui->tableWidget->setHorizontalHeaderLabels(headList);//Set the header
    ui->nowtime->setFont(QFont("Timers" , 20 ,  QFont::Thin));

}

MainWindow::~MainWindow()
{
    delete ui;
}
//The added label displays the image
void MainWindow::ShowImg_Label()
{   
    if(flag_dealok){// if deal finished
        cv::resize(image_show,image_show,cv::Size(ui->label111->width(),ui->label111->height()));//resize to label size
        if(image_show.channels() == 1)
            cvtColor( image_show, image_show, COLOR_GRAY2RGB);
        else
            cvtColor( image_show, image_show, COLOR_BGR2RGB);
        QImage img = QImage(image_show.data, image_show.cols, image_show.rows,image_show.cols*3, QImage::Format_RGB888 );//cv image to qimage
        ui->label111->setPixmap(QPixmap::fromImage(img));//label show
        //ui->label->resize(ui->label->size());
        flag_dealok = 0;
    }
}


void MainWindow::updateTime()
{
    QDateTime time = QDateTime::currentDateTime();//get datatime
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->nowtime->setText(str);
}


void MainWindow::updateItem()
{
    static int count_item = 0;
    if(face_result != "None"){
        if(face_result != "unkown"){
            QDateTime time = QDateTime::currentDateTime();
            QString str = time.toString("hh:mm:ss");
            //Insert elements
            ui->tableWidget->setItem(count_item,0,new QTableWidgetItem(face_result));
            ui->tableWidget->setItem(count_item,1,new QTableWidgetItem(str));
            count_item++;
        }
        face_result = "None";
    }
}

//Want to show the label after the key, but in the keyway function will cause the UI stuck.
void MainWindow::ShowLabels()
{
    static int i = 0;                //Collection completion mark
    static int j= 0;
    //std::cout << "flag="<<function_choose<<std::endl;
    switch (function_choose) {
    case RUN_GETSANPLES:
        if(!timer->isActive())
            timer->start(30);

        j = 0;
        i++;
        if(i%2)
            ui->samples->setText("collecting...");
        else {
            ui->samples->setText(" ");
        }
        break;
    case RUN_TRAINER:
        i = 0;
        j++;
        if(j%2)
            ui->samples->setText("training ...");
        else {
            ui->samples->setText(" ");
        }
        break;
    case -100:                             //Thread completion
        if(i&&!j){
                ui->samples->setText("complete!");//Collect complete
                ui->StartTrain->setEnabled(1);
                ui->GetSamples->setEnabled(1);
                ui->StartRecognize->setEnabled(0);
                ui->start->setEnabled(1);
                ui->pushButton->setEnabled(1);

                sleep(2);
                ui->samples->setText(" ");
        }
        else if(j&&!i){                      //Complete the training
            ui->trainer->setText("Train Finished!");
            ui->StartTrain->setEnabled(0);
            ui->GetSamples->setEnabled(0);
            ui->StartRecognize->setEnabled(0);
            ui->start->setEnabled(1);
            ui->pushButton->setEnabled(1);
            sleep(2);
            ui->trainer->setText(" ");
        }
        ui->trainer->setText(" ");
        ui->samples->setText(" ");
        timerlabel->stop();
        break;
    }

}

extern int recognize_stop; // 1 To stop showing
void MainWindow::on_StartRecognize_clicked()
{
    ui->StartTrain->setEnabled(0);
    ui->GetSamples->setEnabled(0);
    //ui->start->setEnabled(1);

    function_choose = RUN_PREDICT;
    recognize_stop = 0;
}

//start To stop
void MainWindow::on_start_clicked()
{
    static int first_start = 0;
    if (first_start == 0)
    {
        ui->StartTrain->setEnabled(1);
        ui->GetSamples->setEnabled(1);
        ui->StartRecognize->setEnabled(1);


        if(!thread1->isRunning())
           thread1->start();

        if(!timer->isActive())
            timer->start(50);

        ui->start->setEnabled(1);
        ui->start->setText("STOP");
    }
    else
    {
        QString start_name;
        start_name = ui->start->text();

        if (start_name == "START"){
            ui->StartTrain->setEnabled(0);
            ui->GetSamples->setEnabled(0);
            ui->StartRecognize->setEnabled(1);


            if(!thread1->isRunning())
               thread1->start();

            if(!timer->isActive())
                timer->start(50);

            ui->start->setEnabled(1);
            ui->start->setText("STOP");
        }

        else if (start_name == "STOP"){
                ui->StartTrain->setEnabled(1);
                ui->GetSamples->setEnabled(1);
                ui->StartRecognize->setEnabled(0);


                ui->start->setEnabled(1);
                ui->start->setText("START");
        }
    }
    first_start ++;
    if (first_start > 100)
        first_start = 100;

    function_choose = 0;
}

void MainWindow::on_GetSamples_clicked()
{
//    dialog = new Dialog(this);
//    //dialog->setModal(false);
////    /*
////     * The concepts of Modal Dialog and Modeless Dialog are not unique to Qt and exist on a variety of platforms.
////     * It is also called mode dialog box, no mode dialog box, etc.
////     * A modal dialog box is one in which the user cannot interact with other Windows in the same application until the dialog box is closed.
////     * For modeless dialogs, when opened, the user can choose to interact either with the dialogs or with other Windows in the application.
////    */
//    dialog->show();

    login = new Login();
    login->show();

//    ui->StartTrain->setEnabled(0);
//    ui->GetSamples->setEnabled(0);
//    ui->StartRecognize->setEnabled(0);
//    ui->start->setEnabled(0);
//    ui->pushButton->setEnabled(0);

    if(!timerlabel->isActive())
        timerlabel->start(500);
    if(!timer->isActive())
        timer->start(50);


}

void MainWindow::on_StartTrain_clicked()
{
    ui->StartTrain->setEnabled(0);
    ui->GetSamples->setEnabled(0);
    ui->StartRecognize->setEnabled(0);
    ui->start->setEnabled(1);
    if(!timerlabel->isActive())
        timerlabel->start(500);
    function_choose = RUN_TRAINER;

}

void MainWindow::on_pushButton_clicked()
{
    image_show = cv::Mat::zeros(image_show.rows,image_show.cols,image_show.type());
    flag_dealok = 1;
    ShowImg_Label();
    timer->stop();
    recognize_stop = 1;
    thread1->quit();
    timerlabel->stop();
    timer_now->stop();
    timer_item->stop();
    this->close();
}
