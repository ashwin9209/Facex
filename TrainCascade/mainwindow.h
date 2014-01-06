#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTimer>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<opencv2/objdetect/objdetect.hpp>
#include<opencv/cvaux.h>
#include<iostream>
#include<stdio.h>

using namespace std;
using namespace cv;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    void on_btnCaptureImage_clicked();

    void on_btnStartCamera_clicked();

    void startCamStream();

    void loadAndProcess();

    void detectAndDisplay(Mat frame);

public:
    Ui::MainWindow *ui;

    VideoCapture WebCam;
    Mat matOriginal;
    Mat matProcessed;


    QImage qimgOriginal;
    QImage qimgProcessed;

    QTimer *tmrTimer;
    QTimer *tmrTimerDetectFace;

    CvHaarClassifierCascade faceCascade;
    CvHaarClassifierCascade eyesCascade;

    //int loadAndProcessMsg;

    string face_cascade_dir = "C:\haarcascade_frontalface_alt.xml";
    string eyes_cascade_dir = "C:\haarcascade_eye_tree_eyeglasses.xml";



};

#endif // MAINWINDOW_H
