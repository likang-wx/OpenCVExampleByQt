#include <QApplication>
#include <QDebug>

#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << CV_VERSION;
    Mat src=imread("../resource/img/test.jpg");//读取图片，要提前将图片放在程序路径下
    if(src.empty())
        return 0;

    cvtColor(src,src,CV_BGR2GRAY);//转为灰度图
    namedWindow("img");
    imshow("img",src);
    imwrite("../resource/img/test_gray.jpg",src);//保存结果图片
    waitKey(0);//暂停按键等待

    return 0;
}
