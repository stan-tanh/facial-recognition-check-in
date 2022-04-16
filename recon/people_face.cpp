#include <opencv2/opencv.hpp>

#include <fstream>
#include <string>

#include <dirent.h>
//#include <x86_64-linux-gnu/sys/io.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>


#include "people_face.h"

#include <QThread>
#include<QTimer>
using namespace cv;
using namespace std;

/*
 *    算法  主要在这个文件， 包括     预处理:灰度化、直方图均衡化
 *                                 人脸检测
 *                                 人脸识别
 *   功能：   样本采集、   模型训练、  人脸识别
 */

string filepath = "./label/trainer.yml";//customer face recognize model
string haar_face_datapath = "/home/pi/opencv/opencv-4.5.0/data/haarcascades/haarcascade_frontalface_alt.xml";//人脸检测分类器位置
string listpath = "./label/train_list.csv";//csv文件位置（图片路径和标签组成的文本）  //train_list

string facesdir = "./face";
string names_file = "./label/face_recognizenames_file.txt";
string usr_manege = "./manage_usrs.txt";


//cv::Mat image_show;  //全局变量，用来显示
int flag_dealok = 0; //可以传递图片到label的标志
int flag_start_save = 0; //开始保存图片
int recognize_stop = 0;



extern void read_names(vector<string> &name,vector<int> &label);
extern bool save_samplename(string name);
extern void get_namescsv();

extern QString samplename;


void mask_copy(Mat imgg)
{
//    Mat mask = Mat::zeros(imgg.cols,imgg.rows,CV_8UC3);
//    mask.copyTo(imgg);

}

string q2s(const QString &s)
{
    return string((const char *)s.toLocal8Bit());
}

people_face::people_face()
{

}

//这个函数是调用　dirfiles_deal.cpp 里面生成文件夹描述文件的函数
//功能：生成描述文件　　train_list.csv　里面
void people_face::get_csvfile()
{
    get_namescsv();
}

/*
    人脸检测，保存样本。
    输入参数：样本数量
*/
int people_face::save_FaceSamples(Mat frame,int count)
{
    string face_id;
    face_id = q2s(samplename);         //输入的样本名字
    save_samplename(face_id);              //记录已录入的样本名字和标签
    //std::cout << face_id<< "input ok!" <<std::endl;;

    //cout <<"\n 看着摄像头，并等待 ..."<<endl;
    Mat gray;
    vector<Rect>faces;
    int	num = 0;
    int if_detect_ok = 0;

    //检测人脸并将人脸作为样本存入
         cv::cvtColor(frame,gray,COLOR_BGR2GRAY);
         //cv::imshow("gray",gray);                        //灰度化显示 

         cv::equalizeHist(gray,gray);
         //cv::imshow("equalizeHist",gray);               //直方图均衡化显示

         faceDetector.detectMultiScale(gray, faces,1.2,3);// detect face
         for (int i = 0; i < faces.size(); i++)
         {
             if (count % 5 == 0)  //
             {
                 num++;
                 Mat dst;
                 resize(frame(faces[i]), dst, Size(100, 100));// resize to norm size
                 cvtColor(dst, dst, COLOR_BGR2GRAY);// 灰度化
                 string path = facesdir + "/"+ face_id + "/";	//新文件夹路径
		if (count == 5)
                 	mkdir(path.c_str(),S_IRWXU);//创建人名为文件名的新文件夹
                 imwrite( path + face_id +"_"+ to_string(int(count/5)) + ".jpg",dst);	//在对应文件夹中写入对应人的图片（如：名为‘小明’的文件夹中存入小明的图片）
                 cout << "get samples!" << endl;
             }
             rectangle(frame, faces[i], Scalar(0, 0, 255), 2, 8, 0);//框出人脸
             if_detect_ok = 1;
         }
        //mask_copy(frame(faces[0]));
//        image_show = frame.clone();
//        flag_dealok = 1;

    return if_detect_ok;
}




/*
    返回 0 ，不训练，直接读取成功；
    返回 1 ，进行训练，再预测。
    进行训练之前需要先删除已存在的 xml 文件，或者改名。
*/
bool people_face::start_train()
{
    fstream xmlfile;
    xmlfile.open(filepath, ios::in);                 //根据自己需要进行适当的选取 ios::in|ios::out|ios::binary
    if (xmlfile)                  //存在训练好的xml
    {
        std::cout <<"xml已存在，即将覆盖" <<std::endl;
        xmlfile.close();
        //return 0;
    }

    ifstream file(listpath.c_str(), ifstream::in);
    if (!file)
    {
        printf("could not load file correctly...\n");
        return -1;
    }

    string line, path, classlabel;
    vector<Mat>images;
    vector<int>labels;
    char separator = ' ';
    Mat image_one;
    while (!file.eof())
    {
        getline(file, line);

        //cout << line << endl;
        stringstream lines(line);
        getline(lines, path, separator);//获取样本图片路径
        getline(lines, classlabel);//获取标签
        //printf("%s---\n", classlabel.c_str());

        if (!path.empty() && !classlabel.empty())
        {
            //printf("ok:::path:%s\n", path.c_str());
            image_one = imread(path, 0);
            if(!image_one.data){
                cout << "err1"<<endl;
                break;
            }
            images.push_back(image_one);//样本图片放入容器
            labels.push_back(atoi(classlabel.c_str()));//标签放入容器
        }
    }

    if (images.size() < 1 || labels.size() < 1)
    {
        printf("invalid image path...\n");
        return -1;
    }

    //训练模型  LBPHFaceRecognizer
    //Ptr<FaceRecognizer> model = createLBPHFaceRecognizer();
    Ptr<FaceRecognizer> model = LBPHFaceRecognizer::create();
    model->train(images, labels);
    model->save(filepath);

    xmlfile.close();
    return 1;
}
/*
    人脸识别预测函数，按键识别 按钮触发。
    输入：图像、检测出的人脸rect
    输出：识别结果（string name）
*/
string people_face::start_predict(Mat frame,vector<Rect> faces)
{
    static int start_load = 0;
    if (start_load == 0)
        model->read(filepath);

    start_load ++;
    if (start_load > 1000)
        start_load = 1;

    vector<string> m;
    vector<int> l;
    read_names(m,l);         //得到名字和标签对应的容器组
    cout << "samples loaded! "<<endl;
    string result_name = "None";
    Mat gray;

    for (int i = 0; i < faces.size(); i++)
        {
            Mat dst;
            resize(frame(faces[i]), dst, Size(100, 100));//规范尺寸用于后续人脸识别
            cvtColor(dst, dst, COLOR_BGR2GRAY);//灰度化
            rectangle(frame, faces[i], Scalar(0, 255, 0), 2, 8, 0);//在窗口中框出人脸
            int predictedLabel = -1;
            double confidence = 0.0;
                model->predict(dst, predictedLabel, confidence);//对窗口中人脸进行识别，给出预测标签并赋于predictedLabel
            string result_message = format("Predicted number = %d / confidence = %2f.", predictedLabel, confidence);//查看标签和置信度
            cout << result_message << endl;

            //不同人对应的不同标签
        if(confidence > 100){                         //这里修改参数，越大则越容易误识别；越小越准，但容易识别不到。 ****************************************************************************
            predictedLabel = 100;                // recognize false
        }
        if (predictedLabel < m.size()){
            result_name = m[predictedLabel];
            //putText(frame, m[predictedLabel], cv::Point(faces[i].x,faces[i].y-10), FONT_HERSHEY_PLAIN, 2.0, Scalar(0, 255, 0), 1, 10);   //faces[i].tl()
            putText(frame, to_string(confidence), Point(faces[i].x+200,faces[i].y), FONT_HERSHEY_PLAIN, 3.0, Scalar(200, 0, 200), 3, 8);
        }
        else
            result_name = "unkown";
        putText(frame, result_name, Point(faces[i].x,faces[i].y-10), FONT_HERSHEY_PLAIN, 4.0, Scalar(0, 0, 255), 2, 8);
            /*
             * 	void cv::putText(
                cv::Mat& img, // 待绘制的图像
                const string& text, // 待绘制的文字
                cv::Point origin, // 文本框的左下角
                int fontFace, // 字体 (如cv::FONT_HERSHEY_PLAIN)
                double fontScale, // 尺寸因子，值越大文字越大
                cv::Scalar color, // 线条的颜色（RGB）
                int thickness = 1, // 线条宽度
                int lineType = 8, // 线型（4邻域或8邻域，默认8邻域）
                bool bottomLeftOrigin = false // true='origin at lower left'
             */
        }
    if (result_name == "None")
        putText(frame, result_name, Point(300,200), FONT_HERSHEY_PLAIN, 6.0, Scalar(255, 0, 0), 3, 8);
    return result_name;
}

/*
    初始化检测器与识别器；start 按钮触发
*/
int people_face::deal_init()
{
    if (!faceDetector.load(haar_face_datapath))
    {
        cout << "ERROR: Could not load classifier cascade" << endl;
        return -1;
    }
    else cout << "loaded classifier cascade!" << endl;
    return 0;
}

/*
    人脸检测函数，start按钮
    输入：图片
        function_choose，这个参数=100,则代表接下来函数wu显示。
    输出： 检测的人脸rect
*/
vector<Rect> people_face::start_detect(Mat frame,int function_choose)
{
    Mat gray;
    vector<Rect>faces;
    cv::cvtColor(frame,gray,COLOR_BGR2GRAY);
    cv::equalizeHist(gray,gray);
    faceDetector.detectMultiScale(gray, faces, 1.2, 3);
    for (int i = 0; i < faces.size(); i++)
        {
            Mat dst;
            resize(frame(faces[i]), dst, Size(100, 100));//规范尺寸用于后续人脸识别
            cvtColor(dst, dst, COLOR_BGR2GRAY);//灰度化
            rectangle(frame, faces[i], Scalar(255, 0, 0), 2, 8, 0);//在窗口中框出人脸
         }
    return faces;
}
