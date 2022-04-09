# Facial Recognition Check in System

**Introductions:**

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
