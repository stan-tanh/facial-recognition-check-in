#ifndef THREAD_RUN_H
#define THREAD_RUN_H

#include <QWidget>
#include <QThread>
//#include <opencv2/opencv.hpp>

#define RUN_GETSANPLES  1
#define RUN_TRAINER     2
#define RUN_PREDICT     3

class ThreadDeal : public QThread
{
public:
    ThreadDeal();


protected:
    void run();
};


class Threadgetface : public QThread
{
public:
    Threadgetface();


protected:
    void run();
};
#endif // THREAD_RUN_H
