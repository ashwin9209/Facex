#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdlib.h>
#include <vector>
#include <QDebug>
#include <QFileDialog>
#include <QMenu>
#include <QMessageBox>
#include <opencv2/imgproc/imgproc.hpp>


#define FACE_XML  "frontalFace.xml"
#define EYE_XML   "haarcascade_mcs_eyepair_big.xml"
#define MOUTH_XML "haarcascade_mcs_mouth.xml"
#define CAMERA 0 /*for checking whether to process camera stream*/
#define VIDEO 1  /* OR video stream*/
/* The macros CAMERA & VIDEO will be stored in the videoStatus variable. */

using namespace std;

MainWindow::MainWindow(QWidget *parent) :    QMainWindow(parent),    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->checkBox_eyes->setEnabled( false ); /*should not enable detection of eyes before face detection*/
    ui->checkBox_mouth->setEnabled( false ); /*should not enable detection of mouth before face detection*/
    //ui->actionLoadVideo->setEnabled( false );


    createQtGUIActions();
    createQtGUIMenus();


    QString file;

        if( HaarFaceClassifier.empty() )
        {
            /* Trained XML classifiers should be available in the build directory */

            file = tr("%1/%2").arg(QApplication::applicationDirPath()).arg(FACE_XML);
            if(!HaarFaceClassifier.load( file.toLatin1().constData() ))
                qDebug() << tr("Cannot find %1").arg(file);
        }

        if( HaarEyeClassifier.empty() )
        {
            file = tr("%1/%2").arg(QApplication::applicationDirPath()).arg(EYE_XML);
            if(!HaarEyeClassifier.load( file.toLatin1().constData() ))
                qDebug() << tr("Cannot find %1").arg(file);
        }

        if( HaarMouthClassifier.empty() )
        {
            file = tr("%1/%2").arg(QApplication::applicationDirPath()).arg(MOUTH_XML);
            if(!HaarMouthClassifier.load( file.toLatin1().constData() ))
                qDebug() << tr("Cannot find %1").arg(file);
        }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createQtGUIActions()
{
    startCameraAction = new QAction(tr("&Start Camera"), this);
    startCameraAction->setStatusTip(tr("Starts the web-camera to enable tracking"));
    connect(startCameraAction, SIGNAL(triggered()), this, SLOT(on_actionStart_clicked()));

    stopCameraAction = new QAction(tr("&Stop Camera"), this);
    stopCameraAction->setStatusTip(tr("Stops the web-camera and disables tracking"));
    connect(stopCameraAction, SIGNAL(triggered()), this, SLOT(on_actionStop_clicked()));

    aboutFacex = new QAction(tr("&About"), this);
    connect(aboutFacex, SIGNAL(triggered()), this, SLOT(on_action_AboutFacex_clicked()));
}

void MainWindow::createQtGUIMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(startCameraAction);
    fileMenu->addAction(stopCameraAction);
    fileMenu->addAction(aboutFacex);

}

void MainWindow::on_actionStart_clicked()
{
        if( !WebCamCaptureDevice.isOpened() )
        {
            WebCamCaptureDevice.open(0);
            videoStatus = CAMERA; /* Set the appropriate stream */
            /*ui->actionLoadVideo->setEnabled( false );*/ /* Disable the File Explorer for loading videos*/
            //ui->actionStart->setEnabled( false );
            StartVideoEventId = startTimer( 50 );
        }
}

void MainWindow::on_actionLoadVideo_clicked()
{
    /*QString fileName;
    fileName = QFileDialog::getOpenFileName(this, tr("Load Video"), "D:/", tr("Video Files(*.avi, *.mp4)"));*/

    //CvCapture *videoFile = cvCaptureFromFile(fileName.toUtf8().constData());

    /*mVideo.open(fileName.toLatin1().constData());
    videoStatus = VIDEO;
    ui->actionStart->setEnabled( false );
    ui->actionStop->setEnabled( false );
    StartVideoEventId = startTimer(50);*/



    /*if(!mVideo.isOpened())
    {
        mVideo.open(fileName);
        videoStatus = VIDEO;
        ui->actionStart->setEnabled( false );
        ui->actionStop->setEnabled( false );
        StartVideoEventId = startTimer(50);
    }*/

}

void MainWindow::on_actionStop_clicked()
{

    /*ui->actionLoadVideo->setEnabled( true );
    ui->btnStopPro->setEnabled( true );*/
    killTimer( StartVideoEventId );
    WebCamCaptureDevice.release();
}

void MainWindow::on_action_AboutFacex_clicked()
{
    QMessageBox::about(this, tr("About Facex"),
                tr("<h2>Facex 1.0</h2>"
                   "<p>Copyright &copy; 2014 Software Inc."
                   "<p>Facex is a real-time image processing application "
                   "that processes human facial expressions through a "
                   "live webcam stream and classifies them into various "
                   "emotion categories."));

}

void MainWindow::timerEvent(QTimerEvent *event)
{

    if( event->timerId() == StartVideoEventId )
        {
            // Stop Timer to stop receiving data from camera during elaboration
            killTimer( StartVideoEventId );

            if(videoStatus == CAMERA)
                WebCamCaptureDevice >> MatOriginalImage;

            /*else if(videoStatus == VIDEO)
                mVideo >> MatOriginalImage;*/

            MatOriginalImage.copyTo( MatProcessedImage );

            if( ui->checkBox_fullFace->isChecked() )
            {
                //vector< cv::Rect > faceBoundingVector;

                float scaleFactor = 3.0f; // Change Scale Factor to change speed
                HaarFaceClassifier.detectMultiScale( MatOriginalImage, faceBoundingVector, scaleFactor );
                //HaarFaceClassifier.detectSingleScale() MatOriginalImage, rectVec );

                for( size_t i = 0; i < faceBoundingVector.size(); i++ )
                {
                    cv::rectangle( MatProcessedImage, faceBoundingVector[i], CV_RGB(0,0,0), 2 );
                    cv::Mat face = MatOriginalImage( faceBoundingVector[i] );


                    //Crop out ROI of Face detected.
                    ExtractAndDisplayFaceROI(MatOriginalImage);




                    // ---> Eye Detection
                    if( ui->checkBox_eyes->isChecked() )
                    {
                        //vector< cv::Rect > eyeBoundingVector;
                        HaarEyeClassifier.detectMultiScale( face, eyeBoundingVector );

                        for( size_t j=0; j<eyeBoundingVector.size(); j++ )
                        {
                            cv::Rect rect = eyeBoundingVector[j];
                            rect.x += faceBoundingVector[i].x;
                            rect.y += faceBoundingVector[i].y;

                            cv::rectangle( MatProcessedImage, rect, CV_RGB(0,0,0), 2 );

                            //Crop out ROI of eyes detected
                            ExtractAndDisplayEyeROI(MatProcessedImage, rect);
                        }
                    }
                    // <--- Eye Detection



                    // ---> Mouth Detection

                    // [Searched in the bottom half face]
                    if( ui->checkBox_mouth->isChecked() )
                    {
                        //vector< cv::Rect > mouthBoundingVector;
                        cv::Rect halfRect = faceBoundingVector[i];
                        halfRect.height /= 2;
                        halfRect.y += halfRect.height;

                        cv::Mat halfFace = MatOriginalImage( halfRect );

                        HaarMouthClassifier.detectMultiScale( halfFace, mouthBoundingVector, 3 );

                        for( size_t j=0; j<mouthBoundingVector.size(); j++ )
                        {
                            cv::Rect rect = mouthBoundingVector[j];
                            rect.x += halfRect.x;
                            rect.y += halfRect.y;

                            cv::rectangle( MatProcessedImage, rect, CV_RGB(0, 0, 0), 2 );


                            //Crop out ROI of mouth detected
                            ExtractAndDisplayMouthROI(MatProcessedImage, rect);
                        }
                    }
                    // <--- Mouth Detection
                }
            }

            cv::cvtColor(MatProcessedImage, MatProcessedImage, CV_BGR2RGB);
            QImage qProcessedImage ((uchar*) MatProcessedImage.data, MatProcessedImage.cols, MatProcessedImage.rows,
                                     MatProcessedImage.step, QImage::Format_RGB888);

            ui->lblVideo->setPixmap(QPixmap::fromImage(qProcessedImage));


            // Timer reactivation
            StartVideoEventId = startTimer( 0 );
        }

}



void MainWindow::ExtractAndDisplayFaceROI(cv::Mat MatProcessedImagefromTracking)
{
        //killTimer(StartProcessingEventId);

        IplImage *iplimageFrameSource = new IplImage(MatProcessedImagefromTracking);
        //IplImage *iplimageFrameDest;

        //cvCopy(iplimageFrameSource, iplimageFrameDest, NULL);
        cv::Rect roi_face;

        for(size_t i = 0; i < faceBoundingVector.size();i++)
        {
            roi_face.x = faceBoundingVector[i].x;
            roi_face.y = faceBoundingVector[i].y;
            roi_face.width = (faceBoundingVector[i].width);
            roi_face.height = (faceBoundingVector[i].height);
        }

        cvSetImageROI(iplimageFrameSource, roi_face);

        cv::Mat mProcImage(iplimageFrameSource);
        cv::cvtColor(mProcImage, mProcImage, CV_BGR2RGB);
        QImage qSegmentedImage ((uchar*) mProcImage.data, mProcImage.cols, mProcImage.rows,
                                     mProcImage.step, QImage::Format_RGB888);

        ui->lblProcessFaceFrame->setPixmap(QPixmap::fromImage(qSegmentedImage));

        // Timer reactivation
        //StartProcessingEventId = startTimer( 0 );
    }





void MainWindow::ExtractAndDisplayEyeROI(cv::Mat MatProcessedImagefromTracking, cv::Rect prect)
{
    //killTimer(StartProcessingEventId);

    IplImage *iplimageFrameSource = new IplImage(MatProcessedImagefromTracking);
    //IplImage *iplimageFrameDest;

    //cvCopy(iplimageFrameSource, iplimageFrameDest, NULL);
    cv::Rect roi_eye;

    for(size_t i = 0; i < eyeBoundingVector.size();i++)
    {
        /*roi_eye.x = eyeBoundingVector[i].x;
        roi_eye.y = eyeBoundingVector[i].y;
        roi_eye.width = (eyeBoundingVector[i].width);
        roi_eye.height = (eyeBoundingVector[i].height);*/

        roi_eye.x = prect.x;
        roi_eye.y = prect.y;
        roi_eye.width = prect.width;
        roi_eye.height = prect.height;
    }

    cvSetImageROI(iplimageFrameSource, roi_eye);

    cv::Mat mProcImage(iplimageFrameSource);
    cv::cvtColor(mProcImage, mProcImage, CV_BGR2RGB);
    QImage qSegmentedImage ((uchar*) mProcImage.data, mProcImage.cols, mProcImage.rows,
                                 mProcImage.step, QImage::Format_RGB888);

    ui->lblProcessEyeFrame->setPixmap(QPixmap::fromImage(qSegmentedImage));

    // Timer reactivation
    //StartProcessingEventId = startTimer( 0 );
}





void MainWindow::ExtractAndDisplayMouthROI(cv::Mat MatProcessedImagefromTracking, cv::Rect prect)
{
    //killTimer(StartProcessingEventId);

    IplImage *iplimageFrameSource = new IplImage(MatProcessedImagefromTracking);
    //IplImage *iplimageFrameDest;

    //cvCopy(iplimageFrameSource, iplimageFrameDest, NULL);
    cv::Rect roi_mouth;

    for(size_t i = 0; i < mouthBoundingVector.size();i++)
    {
        /*roi_mouth.x = mouthBoundingVector[i].x;
        roi_mouth.y = mouthBoundingVector[i].y;
        roi_mouth.width = (mouthBoundingVector[i].width);
        roi_mouth.height = (mouthBoundingVector[i].height);*/

        roi_mouth.x = prect.x;
        roi_mouth.y = prect.y;
        roi_mouth.width = prect.width;
        roi_mouth.height = prect.height;
    }

    cvSetImageROI(iplimageFrameSource, roi_mouth);

    cv::Mat mProcImage(iplimageFrameSource);
    cv::cvtColor(mProcImage, mProcImage, CV_BGR2RGB);
    QImage qSegmentedImage ((uchar*) mProcImage.data, mProcImage.cols, mProcImage.rows,
                                 mProcImage.step, QImage::Format_RGB888);

    ui->lblProcessMouthFrame->setPixmap(QPixmap::fromImage(qSegmentedImage));

    // Timer reactivation
    //StartProcessingEventId = startTimer( 0 );
}

void MainWindow::on_checkBox_fullFace_clicked()
{
    if( ui->checkBox_fullFace->isChecked() )
        {
            ui->checkBox_eyes->setEnabled( true );
            ui->checkBox_mouth->setEnabled( true );
        }
        else
        {
            ui->checkBox_eyes->setEnabled( false );
            ui->checkBox_mouth->setEnabled( false );
        }
}
