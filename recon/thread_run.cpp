#include <iostream>
#include <string>
#include "thread_run.h"
#include "people_face.h"
#include "mainwindow.h"
#include "opencv2/opencv.hpp"
#include <unistd.h>

using namespace cv;
int function_choose = 0;
cv::Mat image_show;  //全局变量，用来显示
extern int flag_dealok;
QString face_result = "None";


/*
 * 这个文件是多线程，采集图像
 * 通过  界面按钮将flag  置不同的 功能，然后在 thread中 执行
 * 主要有三个功能，样本采集、 模型训练、人脸识别
 */

ThreadDeal::ThreadDeal()
{
    std::cout << "ThreadDeal ok" <<std::endl;
}


//按键开始后，开始该线程（图像处理线程）
void ThreadDeal::run()
{
    people_face p;
    cv::Mat frame,save_frame;
    std::vector<Rect> faces;
    std::string  result_face;
    
    int count = 0;
    int if_detect_ok = 0;
    
    p.deal_init();//初始化处理算法

    VideoCapture capture(0);
    capture.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    capture.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    if(capture.isOpened())
    {
        std::cout << "Capture is opened" << std::endl;
     }
    else
    {
        std::cout << "Capture is error" << std::endl;
     }
    while (true) {

        capture >> frame; //get image for capture
        flip(frame, frame, 1);//lr镜像翻转
        save_frame = frame.clone();
        //一直开始检测
        faces = p.start_detect(frame,function_choose);    
        image_show = frame.clone();

        switch (function_choose) { //key return flag
        case RUN_GETSANPLES:
            //std::cout << "get samples!" << std::endl;
            if_detect_ok = p.save_FaceSamples(save_frame,count);                    //这里修改参数，采集的个数１００;个人测试１００差不多 ***************************************************************************
            count += if_detect_ok;
            function_choose = RUN_GETSANPLES;
            if (count >= 100)//这里除以5，就是存取样本数  500->save 100 images
                function_choose = -100;//quit RUN_GETSANPLES
            image_show = save_frame.clone();                  //to  show image
            break;
        case RUN_TRAINER:
            count = 0;
            std::cout << "train!" << std::endl;
            p.get_csvfile();         //得到描述文件
            p.start_train();         //开始训练
            function_choose = -100;//quit RUN_TRAINER
            break;  
        case RUN_PREDICT:
            std::cout << "predict!" << std::endl;
            result_face = p.start_predict(save_frame,faces);        //开始预测

            face_result = QString::fromStdString(result_face);  // string to qstring
            image_show = save_frame.clone();                  //to  show image
            flag_dealok = 1;
            //function_choose = 100;////quit RUN_PREDICT
            break;
        }
        //show
        flag_dealok = 1;
        if (function_choose == RUN_PREDICT){
            msleep(1000); 
            function_choose = 100;////quit RUN_PREDICT
            }//delay to show label;
        
        msleep(5);
    }
}
