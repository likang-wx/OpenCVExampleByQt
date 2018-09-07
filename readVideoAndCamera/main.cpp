
#include <QApplication>
#include <QDebug>

#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void testVideo()
{
    VideoCapture cap;
    cap.open("../resource/video/test.avi"); //打开视频,以上两句等价于VideoCapture cap("../resource/video/test.avi");

    qDebug() << CV_VERSION;
    //cap.open("http://www.laganiere.name/bike.avi");//也可以直接从网页中获取图片，前提是网页有视频，以及网速够快
    if(!cap.isOpened())//如果视频不能正常打开则返回
        return;

    int width = cap.get(CV_CAP_PROP_FRAME_WIDTH);  //帧宽度
    int height = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //帧高度
    int frameRate = cap.get(CV_CAP_PROP_FPS);  //帧率 x frames/s
    int totalFrames = cap.get(CV_CAP_PROP_FRAME_COUNT); //总帧数

    qDebug()<<"视频宽度="<<width;
    qDebug()<<"视频高度="<<height;
    qDebug()<<"视频总帧数="<<totalFrames;
    qDebug()<<"帧率="<<frameRate;

    Mat frame;
    while(1)
    {
        cap>>frame;//等价于cap.read(frame);
        if(frame.empty())//如果某帧为空则退出循环
            break;
//        Canny(frame, frame, 30, 100);
//        cvtColor(frame,frame,CV_BGR2GRAY); //转为灰度图
        cvtColor(frame, frame, CV_BGR2HSV);//BGR空间转为HSV颜色空间，注意，两者不能同时对同一张图片（在此为frame）进行处理，否则报错
        imshow("video", frame);
        if(27 == waitKey(20)) //27是key_esc
            break;

    }
    cap.release();//释放资源
}

void testCamera()
{
    VideoCapture cap;
    cap.open(0); //打开摄像头

    if(!cap.isOpened())
        return;

    Mat frame;
    while(1)
    {
        cap>>frame;//等价于cap.read(frame);
//        Canny(frame, frame, 30, 100);//canny边缘检测，去掉这一行就是纯粹的读取摄像头了
        cvtColor(frame, frame, CV_BGR2HSV);//BGR空间转为HSV颜色空间，注意，两者不能同时对同一张图片（在此为frame）进行处理，否则报错
        if(frame.empty())
            break;
        imshow("video", frame);
        if(waitKey(20)>0)//按下任意键退出摄像头　　因电脑环境而异，有的电脑可能会出现一闪而过的情况
            break;
    }
    cap.release();
    destroyAllWindows();//关闭所有窗口
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    testVideo();

//    testCamera();

    return 0;
}
