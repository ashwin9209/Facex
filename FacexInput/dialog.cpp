#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog)
{
    ui->setupUi(this);

    WebCam.open(0);

    if(WebCam.isOpened() == false)
    {
        ui->txtXY->appendPlainText("Error: Cannot access Webcam!");
        return;
    }

    tmrTimer = new QTimer(this);

    connect(tmrTimer, SIGNAL(timeout()), this, SLOT(processFrameAndUpdateGUI()));
    tmrTimer->start(20);

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::processFrameAndUpdateGUI()
{
    WebCam.read(matOriginal);

    if(matOriginal.empty() == true)
           return;

    //RED OBJECTS
    //cv::inRange(matOriginal, cv::Scalar(140, 0, 0), cv::Scalar(256, 100, 100), matProcessed);

    //Yellow objects
    //cv::inRange(matOriginal, cv::Scalar(204, 204, 0), cv::Scalar(256, 256, 34), matProcessed);

    //Orange objects
    //cv::inRange(matOriginal, cv::Scalar(232, 116, 0), cv::Scalar(256, 150, 45), matProcessed);

    //White Objects
    //cv::inRange(matOriginal, cv::Scalar(163, 163, 163), cv::Scalar(255, 255, 255), matProcessed);

    /*cv::GaussianBlur(matProcessed, matProcessed, cv::Size(9, 9), 1.5);
    cv::HoughCircles(matProcessed, vecCircles, CV_HOUGH_GRADIENT, 2, matProcessed.rows / 4, 100, 50, 10, 400);

    for(ItrCircles = vecCircles.begin(); ItrCircles!= vecCircles.end(); ItrCircles++)
    {
        ui->txtXY->appendPlainText(QString("Position X: ") + QString::number((*ItrCircles)[0]).rightJustified(4, ' ') +
                                    QString(", Position Y: ") + QString::number((*ItrCircles)[1]).rightJustified(4, ' ') +
                                    QString(", Radius: ") + QString::number((*ItrCircles)[2], 'f', 3).rightJustified(7, ' '));
        //ui->txtXY->appendPlainText(QString("FPS ") + fpsc);

        //green central point of tracked object
        cv::circle(matOriginal, cv::Point((int)(*ItrCircles)[0], (int)(*ItrCircles)[1]), 3, cv::Scalar(0, 255, 0), CV_FILLED);
        //border ring
        cv::circle(matOriginal, cv::Point((int)(*ItrCircles)[0], (int)(*ItrCircles)[1]), (int)(*ItrCircles)[2], cv::Scalar(0, 0, 255), 3);
    }

    cv::cvtColor(matOriginal, matOriginal, CV_BGR2RGB);*/
    QImage qimgOriginal((uchar*)matOriginal.data, matOriginal.cols, matOriginal.rows, matOriginal.step, QImage::Format_RGB888);
    //QImage qimgProcessed((uchar*)matProcessed.data, matProcessed.cols, matProcessed.rows, matProcessed.step, QImage::Format_Indexed8);

    ui->lblInput->setPixmap(QPixmap::fromImage(qimgOriginal));
    //ui->lblProcessed->setPixmap(QPixmap::fromImage(qimgProcessed));
}

void Dialog::on_btnPauseResume_clicked()
{
    if(tmrTimer->isActive() == true)
    {
        tmrTimer->stop();
        ui->btnPauseResume->setText("Resume");
    }
    else
    {
        tmrTimer->start(20);
        ui->btnPauseResume->setText("Pause");
    }
}
