#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTimer>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:

    Ui::Dialog *ui;


    cv::VideoCapture WebCam;
    cv::Mat matOriginal;
    cv::Mat matProcessed;
    cv::VideoCapture fps_count;

    char fpsc[3];

    QImage qimgOriginal;
    QImage qimgProcessed;

    std::vector<cv::Vec3f> vecCircles;
    std::vector<cv::Vec3f>:: iterator ItrCircles;

    QTimer *tmrTimer;



public slots:

    void processFrameAndUpdateGUI();


private slots:
    void on_btnPauseResume_clicked();

};

#endif // DIALOG_H
