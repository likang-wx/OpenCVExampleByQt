#include <QApplication>
#include <QDebug>

#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << CV_VERSION;
    Mat src=imread("../resource/img/test.jpg");//��ȡͼƬ��Ҫ��ǰ��ͼƬ���ڳ���·����
    if(src.empty())
        return 0;

    cvtColor(src,src,CV_BGR2GRAY);//תΪ�Ҷ�ͼ
    namedWindow("img");
    imshow("img",src);
    imwrite("../resource/img/test_gray.jpg",src);//������ͼƬ
    waitKey(0);//��ͣ�����ȴ�

    return 0;
}
