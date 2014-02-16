#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    virtual void timerEvent(QTimerEvent *);

private slots:

    void on_checkBox_fullFace_clicked();
    void on_actionStart_clicked();
    void on_actionStop_clicked();
    void on_actionLoadVideo_clicked();
    void on_btnProcessFrame_clicked();
    void ExtractAndDisplayROI(cv::Mat);

private:
    Ui::MainWindow *ui;

    int StartVideoEventId;

    cv::Mat mOrigImage;
    cv::Mat mElabImage;

    cv::VideoCapture mCapture;
    cv::VideoCapture mVideo;

    std::vector< cv::Rect > faceVec;

    int videoStatus;

    // ---> Face detectors
    cv::CascadeClassifier mFaceDetector;
    cv::CascadeClassifier mEyeDetector;
    cv::CascadeClassifier mMouthDetector;
    // <--- Face detectors
};

#endif // MAINWINDOW_H
