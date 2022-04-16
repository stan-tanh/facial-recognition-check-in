#include <iostream>
#include <string>
#include "thread_run.h"
#include "people_face.h"
#include "mainwindow.h"
#include "opencv2/opencv.hpp"
#include <unistd.h>

using namespace cv;
int function_choose = 0;
cv::Mat image_show;  //Global variable used to display
extern int flag_dealok;
QString face_result = "None";


/*
 * This file is multithreaded to capture images
 * Set flags to different functions through interface buttons, and then execute them in Thread
 * It has three main functions, sample collection, model training and face recognition
 */

ThreadDeal::ThreadDeal()
{
    std::cout << "ThreadDeal ok" <<std::endl;
}


//After the button starts, start the thread (image processing thread)
void ThreadDeal::run()
{
    people_face p;
    cv::Mat frame,save_frame;
    std::vector<Rect> faces;
    std::string  result_face;
    
    int count = 0;
    int if_detect_ok = 0;
    
    p.deal_init();//Initialize the processing algorithm

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
        flip(frame, frame, 1);//Lr mirror flip
        save_frame = frame.clone();
        //Start testing all the time
        faces = p.start_detect(frame,function_choose);    
        image_show = frame.clone();

        switch (function_choose) { //key return flag
        case RUN_GETSANPLES:
            //std::cout << "get samples!" << std::endl;
            if_detect_ok = p.save_FaceSamples(save_frame,count);            //Here modify the parameter, the number of collection 100; Personal test 100 is about the same ***************************************************************************
            count += if_detect_ok;
            function_choose = RUN_GETSANPLES;
            if (count >= 100)//Divide this by 5, that's how many samples you can access  500->save 100 images
                function_choose = -100;//quit RUN_GETSANPLES
            image_show = save_frame.clone();                  //to  show image
            break;
        case RUN_TRAINER:
            count = 0;
            std::cout << "train!" << std::endl;
            p.get_csvfile();         //Get the description file
            p.start_train();         //Start training
            function_choose = -100;//quit RUN_TRAINER
            break;  
        case RUN_PREDICT:
            std::cout << "predict!" << std::endl;
            result_face = p.start_predict(save_frame,faces);        //To predict

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
