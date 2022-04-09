# Facial Recognition Check in System

**Introductions:**<br>
Face recognition is a kind of biometric recognition technology that is based on the identity of people's facial feature information. At present, a lot of research have been carried out on face recognition systems, but mainly based on PC architecture recognition technology, for some special occasions, portability and flexibility are not enough. To this end, this project introduces a real-time processing face recognition system based on embedded technology.  

The project aims to develop a time attendance system based on face recognition. The camera is used to automatically detect the face information of the attendance, and the openCV is used to process the collected face images and video streams, enter the user's face information, and the follow-up user will compare the collected real-time images with the pre-established face database when the camera passes again, and record the attendance information. This project uses the Raspberry Pi 4B as the hardware platform.

**Authors**<br>
Yandan Lai(2714855L), Yunpeng Tang(2663224Y), Ge Cheng(2644025C), Jingyu Wu(2492041W)

**Components：**<br>
* PC with Ubuntu
* Raspberry Pi 4B<br>
![Image text](https://github.com/stan-tanh/facial-recognition-check-in/raw/main/images/4B.png)  
* B020201 USB Camera<br>
![Image text](https://github.com/stan-tanh/facial-recognition-check-in/raw/main/images/Camera.png)

**Methodologies:**

* SDK
* QT C++
* OpenCV C++

**Install the QT development environment:**

On the CLI, run the following commands to install:
```
sudo apt-get update
sudo apt-get install qt5-default
sudo apt-get install qtcreator
sudo apt-get install qtmultimedia5-dev
sudo apt-get install libqt5serialport5-dev
```
**Install the Opencv development environment:**

```
sudo apt-get install build-essential
sudo apt-get install cmake libgtk2.0-dev pkg-config libswscale-dev
sudo apt-get install libjpeg-dev libpng-dev libtiff-dev 
mkdir build
cd build
cmake ..
sudo make
sudo make install
mkdir test
cd test
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
 
int main(int argc, const char * argv[]) {
    Mat image;
    VideoCapture capture(0);
    while(1){
    	capture>>image;
	    imshow("test",image);
	    waitKey(20);
    }
}
cmake_minimum_required(VERSION 2.6)
project(test_opencv)
find_package(OpenCV REQUIRED)
add_executable(test_opencv test_opencv.cpp)
target_link_libraries(test_opencv ${OpenCV_LIBS})
cmake .
 
make 
 
./test_opencv
```

# License
Apache License 2.0. See [`LICENSE`](https://github.com/stan-tanh/facial-recognition-check-in/raw/main/LICENSE) for more information.

# Contacts
This project is established by students from University of Glasgow:
- [Yunpeng Tang, 2663224T](https://github.com/stan-tanh)
- [Yandan Lai, 2714855L](https://github.com/HedgehogHut0)
- [Ge Cheng, 2644025C](https://github.com/ChengGe010)
- [Jingyu Wu, 2492041W](https://github.com/Whatsssssup)
