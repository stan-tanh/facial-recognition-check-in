#-------------------------------------------------
#
# Project created by QtCreator 2019-04-03T15:54:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = face_recognize
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    people_face.cpp \
    thread_run.cpp \
    dirfiles_deal.cpp \
    dialog.cpp \
    login.cpp \
    register.cpp

HEADERS += \
        mainwindow.h \
    people_face.h \
    thread_run.h \
    dialog.h \
    login.h \
    register.h

FORMS += \
        mainwindow.ui \
    dialog.ui \
    login.ui \
    register.ui

#pkg-config --cflags opencv    // 查看头文件目录
#pkg-config --libs opencv      // 查找库文件
#opencv
INCLUDEPATH += /usr/local/include/opencv4 \
                /usr/local/include/opencv4/opencv2
LIBS += -L/usr/lib -lopencv_ccalib -lopencv_face   -lopencv_video -lopencv_plot  -lopencv_objdetect -lopencv_ml -lopencv_xphoto -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_photo -lopencv_imgproc -lopencv_core

#INCLUDEPATH += /home/jiang/opencv/opencv-3.4.4/include/opencv \
#                 /home/jiang/opencv/opencv-3.4.4/include/opencv2



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
