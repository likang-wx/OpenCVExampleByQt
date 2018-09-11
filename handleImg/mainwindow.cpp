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
}

void MainWindow::on_openImg_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "打开文件", qApp->applicationDirPath(), "Images (*.png *.xpm *.jpg)");
    qDebug() << fileName;

    if (fileName.isEmpty()) return;

    m_image = imread(fileName.toLocal8Bit().data());

    //opencv默认读取的图片是按照BGR顺序，QImage是按照RGB顺序
    //改变色彩通道顺序，将Mat的BGR顺序反转为QImage中的RGB顺序
    cvtColor(m_image,m_image,CV_BGR2RGB);

    QImage img = QImage(m_image.data,
                        m_image.cols,m_image.rows,QImage::Format_RGB888);

    img = img.scaled(ui->labelOriImage->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    qDebug() << img.size() << ui->labelOriImage->size();
    ui->labelOriImage->setPixmap(QPixmap::fromImage(img));
}
