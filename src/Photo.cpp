#include "photo.h"
#include <QDebug>
#include <QProcess>
#include <QPixmap>
#include <QApplication>
Photo::Photo(QObject *parent)
    : QObject(parent)
{
    _cmd = "raspistill -n ";
}
 
void Photo::setTempFilePath(QString path)
{
    _path = path;
}
 
void Photo::clearArgs()
{
    _args.clear();
}
 
QPixmap Photo::takeAPhoto(int time, int width, int height)
{
    …
    doCmd();
    …
    emit takeAPhotoReply(pixmap);
    return pixmap;
}
 
void Photo::doCmd()
{
    …
    QProcess p;
    p.execute(cmd);
    …
}
