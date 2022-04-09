#ifndef PHOTO_H
#define PHOTO_H
#include <QObject>
#include <QPixmap>
class Photo : public QObject
{
    Q_OBJECT
public:
    explicit Photo(QObject *parent = 0);
    void setTempFilePath(QString path = QString());
    void clearArgs();
 
signals:
    void takeAPhotoReply(QPixmap pixmap);
public slots:
    QPixmap takeAPhoto(int time = 0, int width = 1920, int height = 1080);
private:
    void doCmd();
private:
    QString _cmd;
    QStringList _args;
    QString _path;
    int _width;
    int _height;
    int _time;
};
