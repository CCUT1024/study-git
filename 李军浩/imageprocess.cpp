#include "imageprocess.h"
#include <QDebug>
#include "globals.h"
ImageProcess::ImageProcess(QObject* parent)
    : QObject(parent)
    , _filename("")
    , _buffer(this) 
    , _isPaused(false)
    , _isCanRun(true)
{
    qDebug() << "初始化ImageProcess " << "Thread ID: " << QThread::currentThreadId();
}

ImageProcess::~ImageProcess()
{
    qDebug() << "ImageProcess destroy";
}

void ImageProcess::processImage(QString filename)                                                       // 图像处理操作
{
    _isCanRun = true;
    _isPaused = false;

    qDebug() << "开始图像处理 " << _isCanRun;

                                                                                                        
    cv::VideoCapture cap(filename.toStdString());                                                       // 打开视频文件
    if (!cap.isOpened())
    {
        qDebug() << "Error opening video file";
        return;
    }
    
    cv::Mat frame;                                                                                      // 读取视频帧并处理

    while (cap.read(frame))                                                                             
    {
        qDebug() << "正处理第" << imageCount++ << "帧图片" << "Thread ID: " << QThread::currentThreadId() << "_iscanrun: " << _isCanRun;

        if (_isPaused)
        {
            mutex.lock();
            pauseCondition.wait(&mutex);  // 阻塞线程直到收到继续信号，只要暂停一次，就必须从外部收到解锁信号才能执行（外部唤醒），期间信号也收不到，重新读取文件也不行
            mutex.unlock();
        }

        if (!_isCanRun)
        {
            break;
        }
        cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
        QImage image((unsigned char*)(frame.data), frame.cols, frame.rows, QImage::Format_RGB888);

        QImage imageCopy = image.copy();

        emit startSendVideo(imageCopy);                                                                 // 开始发送视频

        //emit imageProcessed(imageCopy);                                                               // UI界面显示视频
        
        QThread::usleep(30000);                                                                         // 休眠以控制帧率
    }
}


