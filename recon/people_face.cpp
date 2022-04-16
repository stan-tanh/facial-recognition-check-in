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

/*    Face detection
 *    Functions: sample collection, model training, face recognition
 *                                 
 *    Pre-treatment: grayscale, histogram equalization                            
 */

string filepath = "./label/trainer.yml";//customer face recognize model
string haar_face_datapath = "/home/pi/opencv/opencv-4.5.0/data/haarcascades/haarcascade_frontalface_alt.xml";//location for Face detection classifier
string listpath = "./label/train_list.csv";//Csv file location (text consisting of image path and label)  //train_list

string facesdir = "./face";
string names_file = "./label/face_recognizenames_file.txt";
string usr_manege = "./manage_usrs.txt";


//cv::Mat image_show;  //A global variable which is used for display
int flag_dealok = 0; //flag which passes pictures to lable
int flag_start_save = 0; //saving picture
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

//This function calls the folder description file which generates from   dirfiles_deal.cpp   file
//Function: Generate description file　　train_list.csv
void people_face::get_csvfile()
{
    get_namescsv();
}

/*
    Face detection, samples saving.     
    Input parameter: Sample number
*/
int people_face::save_FaceSamples(Mat frame,int count)
{
    string face_id;
    face_id = q2s(samplename);         //sample name which was input 
    save_samplename(face_id);              //Save the name and label of the sample that has been input
   
    Mat gray;
    vector<Rect>faces;
    int	num = 0;
    int if_detect_ok = 0;

    //Detect faces and save faces as samples
         cv::cvtColor(frame,gray,COLOR_BGR2GRAY);
         //cv::imshow("gray",gray);                        //Grayscale display 

         cv::equalizeHist(gray,gray);
         //cv::imshow("equalizeHist",gray);               //Histogram balanced 

         faceDetector.detectMultiScale(gray, faces,1.2,3);// detect face
         for (int i = 0; i < faces.size(); i++)
         {
             if (count % 5 == 0)  //
             {
                 num++;
                 Mat dst;
                 resize(frame(faces[i]), dst, Size(100, 100));// resize to norm size
                 cvtColor(dst, dst, COLOR_BGR2GRAY);// Grayscale
                 string path = facesdir + "/"+ face_id + "/";	//The new folder path
		if (count == 5)
                 	mkdir(path.c_str(),S_IRWXU);//Create a new folder with a name for the file name
                 imwrite( path + face_id +"_"+ to_string(int(count/5)) + ".jpg",dst);	
		 //Write pictures of the corresponding people in the corresponding folder (for example, save Bob's pictures in the folder named 'Bob')
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
    Returns 0, don't proceed training, read successfully; 
    returns 1, proceed training, and then predict.     
    Before training, the xml file that already exists needs to be deleted, or the name needs to be changed 
*/
bool people_face::start_train()
{
    fstream xmlfile;
    xmlfile.open(filepath, ios::in);                 //Make appropriate selection according to needs ios::in|ios::out|ios::binary
    if (xmlfile)                  //Determine if the trained xml exists 
    {
        std::cout <<"xml already exists，covered soon" <<std::endl;
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
        getline(lines, path, separator);//Get the sample image path
        getline(lines, classlabel);//Get the label
        //printf("%s---\n", classlabel.c_str());

        if (!path.empty() && !classlabel.empty())
        {
            //printf("ok:::path:%s\n", path.c_str());
            image_one = imread(path, 0);
            if(!image_one.data){
                cout << "err1"<<endl;
                break;
            }
            images.push_back(image_one);//place sample image in the container
            labels.push_back(atoi(classlabel.c_str()));//place lable in the container
        }
    }

    if (images.size() < 1 || labels.size() < 1)
    {
        printf("invalid image path...\n");
        return -1;
    }

    //train the lable   LBPHFaceRecognizer
    //Ptr<FaceRecognizer> model = createLBPHFaceRecognizer();
    Ptr<FaceRecognizer> model = LBPHFaceRecognizer::create();
    model->train(images, labels);
    model->save(filepath);

    xmlfile.close();
    return 1;
}
/*
    Face recognition prediction function, key recognition button trigger
    Input: Image, face been detected ( rect )
    Output: detect results ( String name )
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
    read_names(m,l);         //Get the container group corresponding to the name and label
    cout << "samples loaded! "<<endl;
    string result_name = "None";
    Mat gray;

    for (int i = 0; i < faces.size(); i++)
        {
            Mat dst;
            resize(frame(faces[i]), dst, Size(100, 100));//Specification size for subsequent face recognition
            cvtColor(dst, dst, COLOR_BGR2GRAY);//Grayscale
            rectangle(frame, faces[i], Scalar(0, 255, 0), 2, 8, 0);//Frame the face in the window
            int predictedLabel = -1;
            double confidence = 0.0;
                model->predict(dst, predictedLabel, confidence);//Recognize The face in the window, give prediction label and assign to  predictedLabel 
            string result_message = format("Predicted number = %d / confidence = %2f.", predictedLabel, confidence);//Review the labels and confidence levels
            cout << result_message << endl;

            //Different labels for different people
        if(confidence > 100){                         //Modify the parameters  ****************************************************************************
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
                cv::Mat& img, // The image to be drawn
                const string& text, // The text to be drawn
                cv::Point origin, // The lower-left corner of the text box
                int fontFace, // font 
                double fontScale, // Size factor
                cv::Scalar color, // The color of the line（RGB）
                int thickness = 1, // Line width
                int lineType = 8, // Linetype 
                bool bottomLeftOrigin = false // true='origin at lower left'
             */
        }
    if (result_name == "None")
        putText(frame, result_name, Point(300,200), FONT_HERSHEY_PLAIN, 6.0, Scalar(255, 0, 0), 3, 8);
    return result_name;
}

/*
    Initializes the detector and recognizer; trigger start button
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
    Face detection function-matches start button
    input:picture
    Output: Detected face - rect
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
            resize(frame(faces[i]), dst, Size(100, 100));//Specification size for subsequent face recognition
            cvtColor(dst, dst, COLOR_BGR2GRAY);//grayscale
            rectangle(frame, faces[i], Scalar(255, 0, 0), 2, 8, 0);//Frame the face in the window
         }
    return faces;
}
