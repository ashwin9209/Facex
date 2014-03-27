#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <cctype>
#include <iostream>
#include <iterator>
#include <stdio.h>
#include <vector>

#include <QDebug>
#include <QFileDialog>
#include <QMenu>
#include <QMessageBox>

#define FACE_XML  "frontalFace.xml"
#define SMILE_XML "SmileCascade.xml"



MainWindow::MainWindow(QWidget *parent) :    QMainWindow(parent),    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->checkBox_SmileDetect->setEnabled( false );
    ui->progressBar_Smile->setValue(0);
    ui->progressBar_Smile->setEnabled( false );

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

    if( HaarSmileClassifier.empty() )
    {
        file = tr("%1/%2").arg(QApplication::applicationDirPath()).arg(SMILE_XML);
        if(!HaarSmileClassifier.load( file.toLatin1().constData() ))
            qDebug() << tr("Cannot find %1").arg(file);
    }
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

void MainWindow :: on_actionStart_clicked()
{
    if( !WebCamCaptureDevice.isOpened() )
    {
        WebCamCaptureDevice.open(0); //Start webcam
        StartVideoEventId = startTimer( 50 );
    }
}

void MainWindow :: on_actionStop_clicked()
{
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

        WebCamCaptureDevice >> MatOriginalImage;

        MatOriginalImage.copyTo( MatProcessedImage );

        if( ui->checkbox_FaceDetect->isChecked() )
        {
            //vector< cv::Rect > faceBoundingVector;

            float scaleFactor = 3.0f; // Change Scale Factor to change speed

            /*DetectMultiScale detects multiple objects in a video frame
                  according to the features described in the Haar Classifier. */
            HaarFaceClassifier.detectMultiScale( MatOriginalImage, faceBoundingVector, scaleFactor );

            for( size_t i = 0; i < faceBoundingVector.size(); i++ )
            {
                /* For every face detected in each frame draw a rectangular bounding */
                cv::rectangle( MatProcessedImage, faceBoundingVector[i], CV_RGB(0,0,0), 2 );
                cv::Mat Matface = MatOriginalImage( faceBoundingVector[i] );



                /* Code for smile detection -------> */

                if( ui->checkBox_SmileDetect->isChecked() )
                {
                    for(  r = faceBoundingVector.begin(); r != faceBoundingVector.end(); r++)
                    {
                        HaarSmileClassifier.detectMultiScale(Matface, smileBoundingVector, 1.1, 0,
                                                             0 | CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));


                        /* The number of detected neighbors depends on image size (and also illumination, etc.). The
                       following steps use a floating minimum and maximum of neighbors. Intensity thus estimated will be
                       accurate only after a first smile has been displayed by the user. */

                        const int smile_neighbors = (int) smileBoundingVector.size();
                        static int max_neighbors = -1;
                        static int min_neighbors = -1;
                        if (min_neighbors == -1) min_neighbors = smile_neighbors;
                        max_neighbors = MAX(max_neighbors, smile_neighbors);

                        float intensityZeroOne = ((float)smile_neighbors - min_neighbors) / (max_neighbors - min_neighbors + 1);

                        if (intensityZeroOne > 0.0 && intensityZeroOne < 0.99)
                        {
                            float intensityDisplay = intensityZeroOne * 100;
                            ui->progressBar_Smile->setEnabled( true );
                            ui->progressBar_Smile->setValue( (int) intensityDisplay );
                        }



                        //int rect_height = cvRound((float)img.rows * intensityZeroOne);
                        //CvScalar col = CV_RGB((float)255 * intensityZeroOne, 0, 0);
                        //rectangle(img, cvPoint(0, img.rows), cvPoint(img.cols/10, img.rows - rect_height), col, -1);
                    }
                }

                //cv::imshow( "result", img );

            }



            /* <------Smile Detection */
        }
    }


    /* Need to convert colour channels from BGR to RGB */
    cv::cvtColor(MatProcessedImage, MatProcessedImage, CV_BGR2RGB);

    /* Need to convert Mat image into Qt image for display on a Qt label */
    QImage qProcessedImage ((uchar*) MatProcessedImage.data, MatProcessedImage.cols, MatProcessedImage.rows,
                            MatProcessedImage.step, QImage::Format_RGB888);

    /* SetPixmap is a function that maps a binary image onto a Qt label */
    ui->lblVideoSource->setPixmap(QPixmap::fromImage(qProcessedImage));


    // Timer reactivation
    StartVideoEventId = startTimer( 0 );
}

void MainWindow::on_checkbox_FaceDetect_clicked()
{
    if( ui->checkbox_FaceDetect->isChecked() )
    {
        ui->checkBox_SmileDetect->setEnabled( true );
    }
    else
    {
        ui->checkBox_SmileDetect->setEnabled( false );
    }
}



MainWindow::~MainWindow()
{
    delete ui;
}
