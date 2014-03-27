#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnCameraStart_clicked();

    void on_btnCameraStop_clicked();

    void ProcessFrameandDisplay();

private:
    Ui::MainWindow *ui;

    cv::VideoCapture WebCam;
    cv::Mat matOriginal;

    QImage qimgOriginal;

    QTimer *tmrTimer;

    int ImageIndex;
};

#endif // MAINWINDOW_H
