#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdlib.h>
#include <vector>
#include <QDebug>
#include<opencv2/imgproc/imgproc.hpp>
#include<QFileDialog>

#define FACE_XML  "frontalFace.xml"
#define EYE_XML   "haarcascade_mcs_eyepair_big.xml"
#define MOUTH_XML "haarcascade_mcs_mouth.xml"
#define CAMERA 0 /*for checking whether to process camera stream*/
#define VIDEO 1  /* OR video stream*/
/* The macros CAMERA & VIDEO will be stored in the videoStatus variable. */

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->checkBox_eyes->setEnabled( false ); /*should not enable detection of eyes before face detection*/
    ui->checkBox_mouth->setEnabled( false ); /*should not enable detection of mouth before face detection*/
    ui->actionLoadVideo->setEnabled( false );

    QString file;

        if( mFaceDetector.empty() )
        {
            /* Trained XML classifiers should be available in the build directory*/

            file = tr("%1/%2").arg(QApplication::applicationDirPath()).arg(FACE_XML);
            if(!mFaceDetector.load( file.toLatin1().constData() ))
                qDebug() << tr("Cannot find %1").arg(file);
        }

        if( mEyeDetector.empty() )
        {
            file = tr("%1/%2").arg(QApplication::applicationDirPath()).arg(EYE_XML);
            if(!mEyeDetector.load( file.toLatin1().constData() ))
                qDebug() << tr("Cannot find %1").arg(file);
        }

        if( mMouthDetector.empty() )
        {
            file = tr("%1/%2").arg(QApplication::applicationDirPath()).arg(MOUTH_XML);
            if(!mMouthDetector.load( file.toLatin1().constData() ))
                qDebug() << tr("Cannot find %1").arg(file);
        }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionStart_clicked()
{
        if( !mCapture.isOpened() )
        {
            mCapture.open(0);
            videoStatus = CAMERA; /* Set the appropriate stream */
            /*ui->actionLoadVideo->setEnabled( false );*/ /* Disable the File Explorer for loading videos*/
            ui->actionStart->setEnabled( false );
            StartVideoEventId = startTimer( 50 );
        }
}


void MainWindow::on_btnProcessFrame_clicked()
{
    //StartProcessingEventId = startTimer(50);
    //ExtractAndDisplayFaceROI();
}

void MainWindow::on_actionLoadVideo_clicked()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, tr("Load Video"), "D:/", tr("Video Files(*.avi, *.mp4)"));

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
    mCapture.release();
}

void MainWindow::timerEvent(QTimerEvent *event)
{

    if( event->timerId() == StartVideoEventId )
        {
            // Stop Timer to stop receiving data from camera during elaboration
            killTimer( StartVideoEventId );

            if(videoStatus == CAMERA)
                mCapture >> mOrigImage;

            /*else if(videoStatus == VIDEO)
                mVideo >> mOrigImage;*/

            mOrigImage.copyTo( mElabImage );

            if( ui->checkBox_fullFace->isChecked() )
            {
                //vector< cv::Rect > faceVec;

                float scaleFactor = 3.0f; // Change Scale Factor to change speed
                mFaceDetector.detectMultiScale( mOrigImage, faceVec, scaleFactor );
                //mFaceDetector.detectSingleScale() mOrigImage, rectVec );

                for( size_t i = 0; i < faceVec.size(); i++ )
                {
                    cv::rectangle( mElabImage, faceVec[i], CV_RGB(255,0,0), 2 );
                    cv::Mat face = mOrigImage( faceVec[i] );


                    //Crop out ROI of Face detected.
                    ExtractAndDisplayFaceROI(mOrigImage);


                    // ---> Eye Detection
                    if( ui->checkBox_eyes->isChecked() )
                    {
                        //vector< cv::Rect > eyeVec;
                        mEyeDetector.detectMultiScale( face, eyeVec );

                        for( size_t j=0; j<eyeVec.size(); j++ )
                        {
                            rect = eyeVec[j];
                            rect.x += faceVec[i].x;
                            rect.y += faceVec[i].y;

                            cv::rectangle( mElabImage, rect, CV_RGB(0,255,0), 2 );

                            //Crop out ROI of eyes detected
                            ExtractAndDisplayEyeROI(mElabImage, rect);
                        }
                    }
                    // <--- Eye Detection

                    // ---> Mouth Detection
                    // [Searched in the bottom half face]
                    if( ui->checkBox_mouth->isChecked() )
                    {
                        //vector< cv::Rect > mouthVec;
                        cv::Rect halfRect = faceVec[i];
                        halfRect.height /= 2;
                        halfRect.y += halfRect.height;

                        cv::Mat halfFace = mOrigImage( halfRect );

                        mMouthDetector.detectMultiScale( halfFace, mouthVec, 3 );

                        for( size_t j=0; j<mouthVec.size(); j++ )
                        {
                            cv::Rect rect = mouthVec[j];
                            rect.x += halfRect.x;
                            rect.y += halfRect.y;

                            cv::rectangle( mElabImage, rect, CV_RGB(255,255,255), 2 );


                            //Crop out ROI of mouth detected
                            ExtractAndDisplayMouthROI(mElabImage, rect);
                        }
                    }
                    // <--- Mouth Detection
                }
            }

            cv::cvtColor(mElabImage, mElabImage, CV_BGR2RGB);
            QImage qProcessedImage ((uchar*) mElabImage.data, mElabImage.cols, mElabImage.rows,
                                     mElabImage.step, QImage::Format_RGB888);

            ui->lblVideo->setPixmap(QPixmap::fromImage(qProcessedImage));


            // Timer reactivation
            StartVideoEventId = startTimer( 0 );
        }

}



void MainWindow::ExtractAndDisplayFaceROI(cv::Mat mElabImagefromTracking)
{
        //killTimer(StartProcessingEventId);

        IplImage *iplimageFrameSource = new IplImage(mElabImagefromTracking);
        //IplImage *iplimageFrameDest;

        //cvCopy(iplimageFrameSource, iplimageFrameDest, NULL);
        cv::Rect roi_face;

        for(size_t i = 0; i < faceVec.size();i++)
        {
            roi_face.x = faceVec[i].x;
            roi_face.y = faceVec[i].y;
            roi_face.width = (faceVec[i].width);
            roi_face.height = (faceVec[i].height);
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





void MainWindow::ExtractAndDisplayEyeROI(cv::Mat mElabImagefromTracking, cv::Rect prect)
{
    //killTimer(StartProcessingEventId);

    IplImage *iplimageFrameSource = new IplImage(mElabImagefromTracking);
    //IplImage *iplimageFrameDest;

    //cvCopy(iplimageFrameSource, iplimageFrameDest, NULL);
    cv::Rect roi_eye;

    for(size_t i = 0; i < eyeVec.size();i++)
    {
        /*roi_eye.x = eyeVec[i].x;
        roi_eye.y = eyeVec[i].y;
        roi_eye.width = (eyeVec[i].width);
        roi_eye.height = (eyeVec[i].height);*/

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





void MainWindow::ExtractAndDisplayMouthROI(cv::Mat mElabImagefromTracking, cv::Rect prect)
{
    //killTimer(StartProcessingEventId);

    IplImage *iplimageFrameSource = new IplImage(mElabImagefromTracking);
    //IplImage *iplimageFrameDest;

    //cvCopy(iplimageFrameSource, iplimageFrameDest, NULL);
    cv::Rect roi_mouth;

    for(size_t i = 0; i < mouthVec.size();i++)
    {
        /*roi_mouth.x = mouthVec[i].x;
        roi_mouth.y = mouthVec[i].y;
        roi_mouth.width = (mouthVec[i].width);
        roi_mouth.height = (mouthVec[i].height);*/

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

