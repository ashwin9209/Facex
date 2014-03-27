#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ImageIndex = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
    WebCam.release();
}

void MainWindow::on_btnCameraStart_clicked()
{
    WebCam.open(0);

    if(WebCam.isOpened() == false)
    {
        ui->lblError->setText("Error: Cannot access Webcam!");
        return;
    }

    tmrTimer = new QTimer(this);
    connect(tmrTimer, SIGNAL(timeout()), this, SLOT(ProcessFrameandDisplay()));
    tmrTimer->start(20);
}



void MainWindow::ProcessFrameandDisplay()
{
    WebCam.read(matOriginal);

    if(matOriginal.empty() == true)
        return;

    cv::cvtColor(matOriginal, matOriginal, CV_BGR2RGB);
    QImage qimgOriginal((uchar*)matOriginal.data, matOriginal.cols, matOriginal.rows, matOriginal.step, QImage::Format_RGB888);

    ui->lblVideoSource->setPixmap(QPixmap::fromImage(qimgOriginal));

    if(ui->checkBox_StartCapturing->isChecked())
    {
        ImageIndex++;
        QString FileName = QString :: number (ImageIndex);
        FileName = FileName + ".JPG";
        if(qimgOriginal.save(FileName, 0, -1))
            ui->lblError->setText("Saved file " + FileName);
    }

}

void MainWindow::on_btnCameraStop_clicked()
{
    if(tmrTimer->isActive() == true)
    {
        tmrTimer->stop();
    }
}
