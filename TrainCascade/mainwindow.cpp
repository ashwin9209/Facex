#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :    QMainWindow(parent),    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_btnCaptureImage_clicked()
{
    /*loadAndProcessMsg = loadAndProcess();
    if(loadAndProcessMsg == -1)
        ui->txtBoxError->appendPlainText("Fatal error. See issue above.");*/

    tmrTimerDetectFace = new QTimer(this);
    connect(tmrTimerDetectFace, SIGNAL(timeout()), this, SLOT(loadAndProcess()));
    tmrTimerDetectFace->start(20);

}

void MainWindow::startCamStream()
{
    WebCam.read(matOriginal);

     if(matOriginal.empty() == true)
        return;

     QImage qimgOriginal((uchar*)matOriginal.data, matOriginal.cols, matOriginal.rows, matOriginal.step, QImage::Format_RGB888);

     ui->lblInput->setPixmap(QPixmap::fromImage(qimgOriginal));
}

void MainWindow::on_btnStartCamera_clicked()
{
    WebCam.open(0);

        if(WebCam.isOpened() == false)
        {
            ui->lblInput->setText("Error: Cannot access webcam!");
            return;
        }

        tmrTimer = new QTimer(this);
        connect(tmrTimer, SIGNAL(timeout()), this, SLOT(startCamStream()));
        tmrTimer->start(20);
}

void MainWindow::loadAndProcess()
{
    if(!(faceCascade.load(face_cascade_dir)))
    {
        ui->txtBoxError->appendPlainText("Cannot open Face Cascade XML file!");
        return;
    }

    if(!(eyesCascade.load(eyes_cascade_dir)))
    {
        ui->txtBoxError->appendPlainText("Cannot open Eye Cascade XML file!");
        return;
    }

    Mat frame = qimgOriginal;
    if(!frame.empty())
        detectAndDisplay(frame);
    else
    {
        ui->txtBoxError->appendPlainText("Frame could not be captured!");
        return;
    }

    return;
}

void MainWindow::detectAndDisplay(Mat frame)
{
    vector<Rect> faces;
    Mat frame_gray;

    cvtColor(frame, frame_gray, CV_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    //Detect faces

    faceCascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30));

    for(size_t i = 0; i < faces.size(); i++)
    {
        Point center ( faces[i].x + faces[i].width * 0.5, faces[i].y + faces[i].height * 0.5 );
        ellipse(frame, center, Size(faces[i].width * 0.5, faces[i].height * 0.5), 0, 0, Scalar(255, 0, 255), 4, 8, 0);


        Mat faceROI = frame_gray( faces[i]);
        vector<Rect> eyes;

        //In each face, detect eyes

        eyesCascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

        for( size_t j = 0; j < eyes.size(); j++)
        {
            Point center ( faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5);
            int radius = cvRound((eyes[j].width + eyes[j].height) * 0.25);
            circle( frame, center, radius, Scalar (255, 0, 0), 4, 8, 0);
        }

    }

    QImage qimgProcessed((uchar*)frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    ui->lblProcessed->setPixmap(QPixmap::fromImage(qimgProcessed));
}
