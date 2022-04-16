<h1 align="center">Facial Recognition Check in System</h1>

# Introductions:
Face recognition is a kind of biometric recognition technology that is based on the identity of people's facial feature information. At present, a lot of research have been carried out on face recognition systems, but mainly based on PC architecture recognition technology, for some special occasions, portability and flexibility are not enough. To this end, this project introduces a real-time processing face recognition system based on embedded technology.

The project aims to develop a time attendance system based on face recognition. The camera is used to automatically detect the face information of the attendance, and the openCV is used to process the collected face images and video streams, enter the user's face information, and the follow-up user will compare the collected real-time images with the pre-established face database when the camera passes again, and record the attendance information. This project uses the Raspberry Pi 4B as the hardware platform.

**Author**：Yandan Lai(2714855L), Yunpeng Tang(2663224Y), Ge Cheng(2644025C), Jingyu Wu(2492041W

**Components：**<br>
* PC with Ubuntu
* Raspberry Pi 4B<br>
![Image text](https://github.com/stan-tanh/facial-recognition-check-in/raw/main/images/4B.png)  
* B020201 USB Camera<br>
![Image text](https://github.com/stan-tanh/facial-recognition-check-in/raw/main/images/Camera.png)

**Methodologies:**

* SVM
* QT C++
* OpenCV C++

**Install the QT development environment:**

Run the following commands to install:
```
sudo apt-get install qt5-default qtcreator
```
**Install the Opencv development environment:**

```
sudo apt-get install libgdk-pixbuf2.0-dev libpango1.0-dev libpixman-1-dev libcairo2-dev
sudo apt-get install libgtk2.0-dev  
sudo apt install libtbb-dev libjpeg-dev libtiff-dev libwebp-dev libpng-dev
sudo apt-get install ffmpeg
sudo apt-get install libavutil-dev libswresample-dev libavdevice-dev libavfilter-dev libavresample-dev
sudo apt-get install libavcodec-dev libavformat-dev libswscale-dev libv4l-dev libxvidcore-dev libx264-dev   
sudo apt-get install libatlas-base-dev gfortran 
sudo apt-get install libjasper-dev libjasper1

# uncompressed files
sudo tar zxvf opencv-4.5.0-raspbios-buster-armhf.tar.gz -C /opt

# setting environment
cd /home/pi
sudo vi .bashrc

source /opt/opencv-4.5.0/bin/setup_vars_opencv4.sh
export PATH=$PATH:/opt/opencv-4.5.0/bin/
export PKG_CONFIG_LIBDIR=/opt/opencv-4.5.0/lib/pkgconfig/

```
# How to use

```
cd facial-recognition-check-in
qmake -o Makefile face_recognize.pro
make
./face_recog
```

# License
Apache License 2.0. See [`LICENSE`](https://github.com/stan-tanh/facial-recognition-check-in/raw/main/LICENSE) for more information.

# Contacts
This project is established by students from University of Glasgow:
- [Yunpeng Tang, 2663224T](https://github.com/stan-tanh)
- [Yandan Lai, 2714855L](https://github.com/HedgehogHut0)
- [Ge Cheng, 2644025C](https://github.com/ChengGe010)
- [Jingyu Wu, 2492041W](https://github.com/Whatsssssup)

# Social Media:
<br><a href="https://youtu.be/hAqNX1u65mk" target="blank"><img align="left" src="https://upload.wikimedia.org/wikipedia/commons/0/09/YouTube_full-color_icon_%282017%29.svg" height="40" width="40"/>
</a>
<a href="https://www.instagram.com/FacialRecog/">
<img align="left" alt="Mitul's LinkedIN" width= "40px" src="https://upload.wikimedia.org/wikipedia/commons/e/e7/Instagram_logo_2016.svg" />
</a>

