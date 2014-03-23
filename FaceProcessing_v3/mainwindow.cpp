#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_dialog.h"

#include <opencv2/imgproc/imgproc.hpp>

#include <QDebug>
#include <QFileDialog>
#include <QMenu>
#include <QMessageBox>

#include <stdlib.h>
#include <vector>

#define EYE_XML   "haarcascade_mcs_eyepair_big.xml"
#define FACE_XML  "frontalFace.xml"
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
    videoStatus = 0;


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
    if(videoStatus == CAMERA)
    {
        killTimer( StartVideoEventId );
        WebCamCaptureDevice.release();
    }
    delete ui;
}

void MainWindow::PreProcessingCheckBoxDisable()
/* Call this function when exiting the second UI window. It un-checks the pre - processing checkbox.*/
{
    if(ui->checkBox_performPreProcessing->isChecked())
        ui->checkBox_performPreProcessing->setEnabled( false );
}

void MainWindow::createQtGUIActions()
/* Creates actions in the File Menu*/
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
/* Create menu drop-downs*/
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
        WebCamCaptureDevice.open(0); //Start webcam
        videoStatus = CAMERA; /* Set the appropriate stream */
        /*ui->actionLoadVideo->setEnabled( false );*/ /* Disable the File Explorer for loading videos*/
        //ui->actionStart->setEnabled( false );
        StartVideoEventId = startTimer( 50 );
    }
}

//void MainWindow::on_actionLoadVideo_clicked()
//{
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

//}

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




/* PRE - PROCESSING ACTIVITIES */






void MainWindow::StartPreProcessingGrayImage()
/* Pre-processing activities - Convert to GrayScale using the Indexed8 Format of QImage (8-bit binary image) */
{
    cv::cvtColor(MatOriginalImage, MatGrayImage, CV_BGR2GRAY);
    QImage qOriginalGrayImage ((uchar*) MatGrayImage.data, MatGrayImage.cols, MatGrayImage.rows,
                               MatGrayImage.step, QImage::Format_Indexed8);

    UI_Dialog_preprocess->ui->lblDialogUI_GrayScaleImage->setPixmap(QPixmap::fromImage(qOriginalGrayImage));
}



void MainWindow :: StartHistogramEqualization()
/* Histogram Equalization helps stretch out the contrast of the image */
{
    cv::equalizeHist(MatGrayImage, MatHistEqualized);
    QImage qHistogramEqualizationImage ((uchar*) MatHistEqualized.data, MatHistEqualized.cols, MatHistEqualized.rows,
                                        MatHistEqualized.step, QImage::Format_Indexed8);

    UI_Dialog_preprocess->ui->lblDialogUI_HistEquImage->setPixmap(QPixmap::fromImage(qHistogramEqualizationImage));
}



void MainWindow :: StartHSVImageConvert()
/* HSV format helps in better recognition of skin-tone, objects etc. */
{
    cv::cvtColor(MatOriginalImage, MatHSVImage, CV_BGR2HSV);
    QImage qOriginalHSVImage ((uchar*) MatHSVImage.data, MatHSVImage.cols, MatHSVImage.rows,
                              MatHSVImage.step, QImage::Format_RGB888);

    UI_Dialog_preprocess->ui->lblDialogUI_HSV->setPixmap(QPixmap::fromImage(qOriginalHSVImage));
}



void MainWindow::StartPreProcessingImage()
/* Pre-processing activities on the video stream in the new window */
{
    StartPreProcessingGrayImage();
    StartHistogramEqualization();
    StartHSVImageConvert();
}





/* TIMER EVENTS */




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

        if(ui->checkBox_performPreProcessing->isChecked())
        {
            StartPreProcessingImage();
        }

        if( ui->checkBox_fullFace->isChecked() )
        {
            //vector< cv::Rect > faceBoundingVector;

            float scaleFactor = 1.1f; // Change Scale Factor to change speed

            /*DetectMultiScale detects multiple objects in a video frame
                  according to the features described in the Haar Classifier. */
            HaarFaceClassifier.detectMultiScale( MatOriginalImage, faceBoundingVector, scaleFactor );

            for( size_t i = 0; i < faceBoundingVector.size(); i++ )
            {
                /* For every face detected in each frame draw a rectangular bounding */
                cv::rectangle( MatProcessedImage, faceBoundingVector[i], CV_RGB(0,0,0), 2 );
                cv::Mat face = MatOriginalImage( faceBoundingVector[i] );


                //Crop out ROI of Face detected.
                ExtractAndDisplayFaceROI(MatOriginalImage);




                // ---> Eye Detection
                if( ui->checkBox_eyes->isChecked() )
                {
                    //vector< cv::Rect > eyeBoundingVector;
                    HaarEyeClassifier.detectMultiScale( face, eyeBoundingVector, scaleFactor );

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

                    HaarMouthClassifier.detectMultiScale( halfFace, mouthBoundingVector, scaleFactor );

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


        /* Need to convert colour channels from BGR to RGB */
        cv::cvtColor(MatProcessedImage, MatProcessedImage, CV_BGR2RGB);

        //cv::resize(MatProcessedImage, MatResizedImage, cv::Size(), 0, 0, CV_INTER_AREA);

        //QImage qProcessedImage ((uchar*) MatResizedImage.data, MatResizedImage.cols, MatResizedImage.rows,
          //                              MatResizedImage.step, QImage::Format_RGB888);

        /* Need to convert Mat image into Qt image for display on a Qt label */
        QImage qProcessedImage ((uchar*) MatProcessedImage.data, MatProcessedImage.cols, MatProcessedImage.rows,
                                MatProcessedImage.step, QImage::Format_RGB888);

        /* SetPixmap is a function that maps a binary image onto a Qt label */
        ui->lblVideo->setPixmap(QPixmap::fromImage(qProcessedImage));


        // Timer reactivation
        StartVideoEventId = startTimer( 0 );
    }

}



void MainWindow::ExtractAndDisplayFaceROI(cv::Mat MatProcessedImagefromTracking)
{
    //killTimer(StartProcessingEventId);

    /* Capture current frame for ROI extraction */
    IplImage *iplimageFrameSource = new IplImage(MatProcessedImagefromTracking);

    //cvCopy(iplimageFrameSource, iplimageFrameDest, NULL);
    cv::Rect roi_face;

    for(size_t i = 0; i < faceBoundingVector.size();i++)
        /* For every face bounding vector capture the end points onto
       a new rectangular vector for locally decribing the face
       region and also reduce load on memory */
    {
        roi_face.x = faceBoundingVector[i].x;
        roi_face.y = faceBoundingVector[i].y;
        roi_face.width = (faceBoundingVector[i].width);
        roi_face.height = (faceBoundingVector[i].height);
    }

    /* cvSetImageROI is an opencv function that crops out region of interest from
       the source using a bounding vector to define the new corner points */

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

        /* Uses the rectangular bounding vector passed as a parameter to this function
            to simplify processing of ROI*/
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

/*void MainWindow::on_btnPreProcessing_clicked()
{
    UI_Dialog_preprocess = new Dialog(this);
    UI_Dialog_preprocess->show();
    onShowdialog(StartVideoEventId);
}*/

/*void MainWindow::onShowdialog(QTimerEvent *event)
{
    if( event->timerId() == StartVideoEventId )
        {
            // Stop Timer to stop receiving data from camera during elaboration
            killTimer( StartVideoEventId );

            QImage qOriginalImage ((uchar*) MatOriginalImage.data, MatOriginalImage.cols, MatOriginalImage.rows,
                             MatOriginalImage.step, QImage::Format_RGB888);

            UI_Dialog_preprocess->ui->lblDialogUIprocessedimage1->setPixmap(QPixmap::fromImage(qOriginalImage));

            // Timer reactivation
            StartVideoEventId = startTimer( 0 );
        }
}*/


void MainWindow::on_checkBox_performPreProcessing_clicked()
{
    if(ui->checkBox_performPreProcessing->isChecked())
    {
        UI_Dialog_preprocess = new Dialog(this);
        UI_Dialog_preprocess->show();
    }
}

void MainWindow::on_btnSnapshot_clicked()
{
    cv::imwrite("qtImage.jpg", MatOriginalImage);
}
