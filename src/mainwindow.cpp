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
//Qt中的UI操作，比如QMainWindow、QWidget之类的创建、操作，只能位于主线程！
//这个限制意味着你不能在新的线程中使用QDialog、QMessageBox等。比如在新线程中复制文件出错，想弹出对话框警告？可以，但是必须将错误信息传到主线程，由主线程实现对话框警告。
//因此一般思路是，主线程负责提供界面，子线程负责无UI的单一任务，通过“信号-槽”与主线程交互。

//QPalette bgpal = palette();

//bgpal.setColor (QPalette::Background, QColor (0, 0 , 0, 255));

////bgpal.setColor (QPalette::Background, Qt::transparent);

//bgpal.setColor (QPalette::Foreground, QColor (255,255,255,255)); setPalette (bgpal);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //初始化
    timerlabel = new QTimer(this);
    timer = new QTimer(this);
    timer_now = new QTimer(this);
    timer_item = new QTimer(this);

    thread1 = new ThreadDeal;

    timer_now->start(1000);
    connect(timer_now,SIGNAL(timeout()),this,SLOT(updateTime()));

    timer_item->start(100);
    connect(timer_item,SIGNAL(timeout()),this,SLOT(updateItem()));

    connect(timer,SIGNAL(timeout()),this,SLOT(ShowImg_Label()));    //定时显示
    connect(timerlabel,SIGNAL(timeout()),this,SLOT(ShowLabels()));    //定时显示

    ui->samples->setText(" ");
    ui->trainer->setText(" ");

    ui->StartTrain->setEnabled(0);
    ui->GetSamples->setEnabled(0);
    ui->StartRecognize->setEnabled(0);

    //table widght
    QStringList headList;
    headList<<"name"<<"time";
    ui->tableWidget->setColumnCount(2);//设置列数
    ui->tableWidget->setRowCount(100);//设置行数
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//自适应列宽
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//表格不能被编辑
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中效果
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//设置为只能单选
    ui->tableWidget->verticalHeader()->setVisible(false);   //隐藏列表头
    //ui->tableWidget->horizontalHeader()->setVisible(false); //隐藏行表头
    ui->tableWidget->setHorizontalHeaderLabels(headList);//设置表头

    ui->nowtime->setFont(QFont("Timers" , 20 ,  QFont::Thin));

}

MainWindow::~MainWindow()
{
    delete ui;
}
//加的label显示图像
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
            //插入元素
            ui->tableWidget->setItem(count_item,0,new QTableWidgetItem(face_result));
            ui->tableWidget->setItem(count_item,1,new QTableWidgetItem(str));
            count_item++;
        }
        face_result = "None";
    }
}

//想定时显示按键后的ｌａｂｅｌ，可是在按键槽函数内会导致ｕｉ卡死。
void MainWindow::ShowLabels()
{
    static int i = 0;                //采集完成标志
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
    case -100:                             //线程执行完成
        if(i&&!j){
                ui->samples->setText("complete!");//采集完成
                ui->StartTrain->setEnabled(1);
                ui->GetSamples->setEnabled(1);
                ui->StartRecognize->setEnabled(0);
                ui->start->setEnabled(1);
                ui->pushButton->setEnabled(1);

                sleep(2);
                ui->samples->setText(" ");
        }
        else if(j&&!i){                      //训练完成
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

extern int recognize_stop; // 1 停止显示
void MainWindow::on_StartRecognize_clicked()
{
    ui->StartTrain->setEnabled(0);
    ui->GetSamples->setEnabled(0);
    //ui->start->setEnabled(1);

    function_choose = RUN_PREDICT;
    recognize_stop = 0;
}

//start 开始 停止
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
////     * 模态对话框（Modal Dialog）与非模态对话框（Modeless Dialog）的概念不是Qt所独有的，在各种不同的平台下都存在。
////     * 又有叫法是称为模式对话框，无模式对话框等。
////     * 所谓模态对话框就是在其没有被关闭之前，用户不能与同一个应用程序的其他窗口进行交互，直到该对话框关闭。
////     * 对于非模态对话框，当被打开时，用户既可选择和该对话框进行交互，也可以选择同应用程序的其他窗口交互。
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
