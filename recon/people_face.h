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

    //dirent.h Failed to generate CSV file!!
    void get_csvfile();

    //Call the PY library to generate a CSV file
    void runPy_getcsv();

    /*
        Face detection, sample preservation.
        Input parameter: number of samples
    */
    int save_FaceSamples(cv::Mat frame,int count);

    /*
        Return 0, no training, directly read success;
        Return 1, train, and predict.
        Delete the existing XML file or rename it before performing the training.
    */
    bool start_train();




    //Face recognition prediction function
    std::string start_predict(Mat frame,std::vector<Rect> faces);

    //Initialize some parameters, load identification classifier, load detection classifier
    int deal_init();

    //Face detection function
    std::vector<Rect> start_detect(cv::Mat frame,int function_choose);

    //Detection classifier
    cv::CascadeClassifier faceDetector;

    //Recognition classifier
    cv::Ptr<FaceRecognizer> model = LBPHFaceRecognizer::create();



};

#endif // PEOPLE_FACE_H
