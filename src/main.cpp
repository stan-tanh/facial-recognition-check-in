#include "mainwindow.h"
#include <QApplication>

#include <iostream>
#include <string>
#include "thread_run.h"

extern void  thread_test();

int main(int argc, char *argv[])
{
    //std::thread test_t(thread_test);
    //test_t.join();
    //thread_test();
    QApplication a(argc, argv);
    MainWindow mw;
    mw.show();

    return a.exec();
}


