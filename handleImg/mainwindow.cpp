#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    /*
     * 关于 Mat ，首先要知道的是你不必再手动地
     * （1）为其开辟空间
     * （2）在不需要时立即将空间释放。
     * 但手动地做还是可以的：
     * 大多数OpenCV函数仍会手动地为输出数据开辟空间。
     * 当传递一个已经存在的 Mat 对象时，
     * 开辟好的矩阵空间会被重用。
     * 也就是说，我们每次都使用大小正好的内存来完成任务。
    */
//    if(!m_image.empty())
//    {
//        qDebug() << "m_image is not empty";
//        m_image.release();
//    }
}

void MainWindow::on_openImg_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "打开文件", qApp->applicationDirPath()+"/../resource/img/", "Images (*.png *.xpm *.jpg)");
    qDebug() << fileName;

    if (fileName.isEmpty()) return;

    m_image = imread(fileName.toLocal8Bit().data());

    showOriImage(m_image);
    showGrayImage(m_image);
    showGaussianImage(m_image);
    showBlurImage(m_image);
    showCannyFalseImage(m_image);
    showCannyTrueImage(m_image);
}

void MainWindow::showOriImage(Mat &matImage)
{
    //opencv默认读取的图片是按照BGR顺序，QImage是按照RGB顺序
    //改变色彩通道顺序，将Mat的BGR顺序反转为QImage中的RGB顺序
    Mat matImageTemp;
    cvtColor(matImage,matImageTemp,CV_BGR2RGB);

    QImage img = QImage(matImageTemp.data,
                        matImageTemp.cols,matImageTemp.rows,QImage::Format_RGB888);

    img = img.scaled(ui->labelOriImage->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    qDebug() << img.size() << ui->labelOriImage->size();
    ui->labelOriImage->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::showGrayImage(Mat &matImage)
{
    Mat matImageTemp;
    cvtColor(matImage,matImageTemp,CV_BGR2GRAY);

    //转换为灰度图后要用 Format_Grayscale8 格式转QImage.
    QImage img = QImage(matImageTemp.data,
                        matImageTemp.cols,matImageTemp.rows,QImage::Format_Grayscale8);

    img = img.scaled(ui->labelGrayImage->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    qDebug() << img.size() << ui->labelGrayImage->size();
    ui->labelGrayImage->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::showGaussianImage(Mat &matImage)
{
    Mat matImageTemp;

    int sigma = 3;
    int ksize = (sigma*5)|1;

    cvtColor(matImage,matImageTemp,CV_BGR2RGB);
    GaussianBlur(matImageTemp, matImageTemp, Size(ksize, ksize), sigma, sigma);

    //转换为灰度图后要用 Format_Grayscale8 格式转QImage.
    QImage img = QImage(matImageTemp.data,
                        matImageTemp.cols,matImageTemp.rows,QImage::Format_RGB888);

    img = img.scaled(ui->labelGaussianImage->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    qDebug() << img.size() << ui->labelGaussianImage->size();
    ui->labelGaussianImage->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::showBlurImage(Mat &matImage)
{
    Mat matImageTemp;

    int sigma = 3;
    int ksize = (sigma*5)|1;

    cvtColor(matImage,matImageTemp,CV_BGR2RGB);
    blur(matImageTemp, matImageTemp, Size(ksize, ksize));

    //转换为灰度图后要用 Format_Grayscale8 格式转QImage.
    QImage img = QImage(matImageTemp.data,
                        matImageTemp.cols,matImageTemp.rows,QImage::Format_RGB888);

    img = img.scaled(ui->labelBlurImage->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    qDebug() << img.size() << ui->labelBlurImage->size();
    ui->labelBlurImage->setPixmap(QPixmap::fromImage(img));

}

void MainWindow::showCannyFalseImage(Mat &matImage)
{
    Mat matImageTemp;

    /*
     * 边缘检测 必须先要转为灰度图
     * The Canny edge detector writes its output to a single-channel (grayscale) image
    */
    cvtColor(matImage,matImageTemp,CV_BGR2GRAY);
    Canny( matImageTemp, matImageTemp, 10, 100, 3, false );
    //转换为灰度图后要用 Format_Grayscale8 格式转QImage.
    QImage img = QImage(matImageTemp.data,
                        matImageTemp.cols,matImageTemp.rows,QImage::Format_Grayscale8);

    img = img.scaled(ui->labelCannyFImage->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    qDebug() << img.size() << ui->labelCannyFImage->size();
    ui->labelCannyFImage->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::showCannyTrueImage(Mat &matImage)
{
    Mat matImageTemp;
    cvtColor(matImage,matImageTemp,CV_BGR2GRAY);
    Canny( matImageTemp, matImageTemp, 10, 100, 3, true );
    //转换为灰度图后要用 Format_Grayscale8 格式转QImage.
    QImage img = QImage(matImageTemp.data,
                        matImageTemp.cols,matImageTemp.rows,QImage::Format_Grayscale8);

    img = img.scaled(ui->labelCannyTImage->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    qDebug() << img.size() << ui->labelCannyTImage->size();
    ui->labelCannyTImage->setPixmap(QPixmap::fromImage(img));
}
