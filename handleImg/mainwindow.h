#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_openImg_clicked();

private:
    void showOriImage(Mat &matImage);
    void showGrayImage(Mat &matImage);
    void showGaussianImage(Mat &matImage);

private:
    Ui::MainWindow *ui;
    Mat m_image;
};

#endif // MAINWINDOW_H
