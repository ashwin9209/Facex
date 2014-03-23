#include "mainwindow.h"
#include "ui_mainwindow.h"

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
}

void MainWindow::on_btnCameraStop_clicked()
{
    if(tmrTimer->isActive() == true)
    {
        tmrTimer->stop();
    }
}
