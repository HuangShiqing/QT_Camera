#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPixmap>
#include <QPaintEvent>
#include <qpainter.h>
#include <QTimer>
#include <QString>

#include "opencv2/opencv.hpp"
using namespace cv;

#include <iostream>

#include "thread.h"

extern u_int8_t *pImageBuffer;
extern Mat edge;
extern int first_frame_flag ;
extern int frame_count;
extern int time_process;
int show_frame_count=0;
int show_time_process=0;
using namespace std;

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

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);

    if(first_frame_flag == 1)
    {
         painter.drawPixmap(QRect(10,10,650,490),QPixmap("/home/nvidia/DeepLearning/QT/Camera/Camera/panda.jpeg"));
    }
    else if(first_frame_flag == 0)
    {
        QImage qimg;
        qimg = QImage((const unsigned char*)(pImageBuffer),640,480,QImage::Format_RGB888);
        QPixmap jpg1 = QPixmap::fromImage(qimg);
//        painter.drawPixmap(QRect(10,10,650,490),jpg);
        painter.drawPixmap(QRect(330,10,330,250),jpg1);


         if(edge.type()==CV_8UC1)
         {
             QImage image(edge.cols, edge.rows, QImage::Format_Indexed8);
             // Set the color table (used to translate colour indexes to qRgb values)
             image.setColorCount(256);
             for(int i = 0; i < 256; i++)
             {
                 image.setColor(i, qRgb(i, i, i));
             }
             // Copy input Mat
             uchar *pSrc = edge.data;
             for(int row = 0; row < edge.rows; row ++)
             {
                 uchar *pDest = image.scanLine(row);
                 memcpy(pDest, pSrc, edge.cols);
                 pSrc += edge.step;
             }
             QPixmap jpg = QPixmap::fromImage(image);
//             painter.drawPixmap(QRect(10,10,650,490),jpg);
             painter.drawPixmap(QRect(10,10,330,250),jpg);
         }


        QFont font("宋体",15,QFont::Black,true);
        painter.setFont(font);
        painter.setPen(Qt::red);
        painter.drawText(QRect(550,50,100,100),"fps:  ");
        painter.drawText(QRect(600,50,100,100),QString::number(show_frame_count));
        painter.drawText(QRect(550,75,100,100),"time:  ");
        painter.drawText(QRect(620,75,100,100),QString::number(show_time_process));
    }

}

void MainWindow::slot_timer()
{
//    cout<<frame_count<<endl;
    show_frame_count = frame_count;
    frame_count = 0;

    show_time_process = time_process;
}
void MainWindow::on_pushButton_clicked()
{
    ThreadCamera *threadcamera = new ThreadCamera(this);
    threadcamera->start();

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(slot_timer()),Qt::QueuedConnection);//signalsupdate
    timer->start(1000);
}
