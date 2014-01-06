#include "cmainwindow.h"
#include "ui_cmainwindow.h"

#include <stdlib.h>
#include <vector>
#include <QDebug>

#define FEAT_FACE_FILE  "frontalFace.xml"
#define FEAT_EYE_FILE   "haarcascade_mcs_eyepair_big.xml"
#define FEAT_MOUTH_FILE "haarcascade_mcs_mouth.xml"

using namespace std;

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMainWindow)
{
    ui->setupUi(this);

}

CMainWindow::~CMainWindow()
{
    delete ui;
}

void CMainWindow::on_actionStart_triggered()
{
    QString file;

    if( mFaceDetector.empty() )
    {
        file = tr("%1/%2").arg(QApplication::applicationDirPath()).arg(FEAT_FACE_FILE);
        if(!mFaceDetector.load( file.toLatin1().constData() ))
            qDebug() << tr("Cannot find %1").arg(file);
    }

    if( mEyeDetector.empty() )
    {
        file = tr("%1/%2").arg(QApplication::applicationDirPath()).arg(FEAT_EYE_FILE);
        if(!mEyeDetector.load( file.toLatin1().constData() ))
            qDebug() << tr("Cannot find %1").arg(file);
    }

    if( mMouthDetector.empty() )
    {
        file = tr("%1/%2").arg(QApplication::applicationDirPath()).arg(FEAT_MOUTH_FILE);
        if(!mMouthDetector.load( file.toLatin1().constData() ))
            qDebug() << tr("Cannot find %1").arg(file);
    }

    if( !mCapture.isOpened() )
    {
        mCapture.open(0);
        mCameraEventId = startTimer( 50 );
    }
}

void CMainWindow::on_actionStop_triggered()
{
    killTimer( mCameraEventId );

    mCapture.release();
}

void CMainWindow::timerEvent(QTimerEvent *event)
{
    if( event->timerId() == mCameraEventId )
    {
        // Stop Timer to stop receiving data from camera during elaboration
        killTimer( mCameraEventId );

        mCapture >> mOrigImage;

        mOrigImage.copyTo( mElabImage );

        if( ui->checkBox_fullFace->isChecked() )
        {
            vector< cv::Rect > faceVec;

            float scaleFactor = 3.0f; // Change Scale Factor to change speed
            mFaceDetector.detectMultiScale( mOrigImage, faceVec, scaleFactor );
            //mFaceDetector.detectSingleScale() mOrigImage, rectVec );

            for( size_t i = 0; i < faceVec.size(); i++ )
            {
                cv::rectangle( mElabImage, faceVec[i], CV_RGB(255,0,0), 2 );

                cv::Mat face = mOrigImage( faceVec[i] );
                //cv::imshow( "Face", face );

                // ---> Eye Detection
                if( ui->checkBox_eyes->isChecked() )
                {
                    vector< cv::Rect > eyeVec;

                    mEyeDetector.detectMultiScale( face, eyeVec );

                    for( size_t j=0; j<eyeVec.size(); j++ )
                    {
                        cv::Rect rect = eyeVec[j];
                        rect.x += faceVec[i].x;
                        rect.y += faceVec[i].y;

                        cv::rectangle( mElabImage, rect, CV_RGB(0,255,0), 2 );
                    }
                }
                // <--- Eye Detection

                // ---> Mouth Detection
                // [Searched in the bottom half face]
                if( ui->checkBox_mouth->isChecked() )
                {
                    vector< cv::Rect > mouthVec;
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
                    }
                }
                // <--- Mouth Detection
            }
        }

        ui->cameraWidget->showImage( mElabImage );

        // Timer reactivation
        mCameraEventId = startTimer( 0 );
    }
}

void CMainWindow::on_checkBox_fullFace_clicked()
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
