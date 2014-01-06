#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QMainWindow>

#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace Ui {
    class CMainWindow;
}

class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CMainWindow(QWidget *parent = 0);
    ~CMainWindow();

protected:
    virtual void timerEvent(QTimerEvent *);

private slots:
    void on_actionStart_triggered();

    void on_actionStop_triggered();

    void on_checkBox_fullFace_clicked();

private:
    Ui::CMainWindow *ui;

    int mCameraEventId;

    cv::Mat mOrigImage;
    cv::Mat mElabImage;

    cv::VideoCapture mCapture;

    // ---> Face detectors
    cv::CascadeClassifier mFaceDetector;
    cv::CascadeClassifier mEyeDetector;
    cv::CascadeClassifier mMouthDetector;
    // <--- Face detectors
};

#endif // CMAINWINDOW_H
