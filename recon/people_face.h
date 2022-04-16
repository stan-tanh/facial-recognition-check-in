#ifndef PEOPLE_FACE_H
#define PEOPLE_FACE_H
#include <opencv2/face.hpp>
#include <iostream>
using namespace  cv;
using namespace  cv::face;

class people_face
{
public:
    people_face();

    //dirent.h生成 csv文件 失败！！！
    void get_csvfile();

    //调用py库生成 csv文件
    void runPy_getcsv();

    /*
        人脸检测，保存样本。
        输入参数：样本数量
    */
    int save_FaceSamples(cv::Mat frame,int count);

    /*
        返回 0 ，不训练，直接读取成功；
        返回 1 ，进行训练，再预测。
        进行训练之前需要先删除已存在的 xml 文件，或者改名。
    */
    bool start_train();




    //人脸识别预测函数
    std::string start_predict(Mat frame,std::vector<Rect> faces);

    //初始化一些参数，加载识别分类器，加载检测分类器
    int deal_init();

    //人脸检测函数
    std::vector<Rect> start_detect(cv::Mat frame,int function_choose);

    //检测分类器
    cv::CascadeClassifier faceDetector;

    //识别分类器
    cv::Ptr<FaceRecognizer> model = LBPHFaceRecognizer::create();



};

#endif // PEOPLE_FACE_H
