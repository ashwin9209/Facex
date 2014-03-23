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

    void createQtGUIActions();
    void createQtGUIMenus();


    void on_checkBox_fullFace_clicked();
    void on_actionStart_clicked();      //start webcam stream button action
    void on_actionStop_clicked();       //stop webcam stream button action
    void on_actionLoadVideo_clicked();  //load video from file explorer
    void on_action_AboutFacex_clicked();

    //segmenting out detected areas of the face
    void ExtractAndDisplayFaceROI(cv::Mat);
    void ExtractAndDisplayEyeROI(cv::Mat, cv::Rect);
    void ExtractAndDisplayMouthROI(cv::Mat, cv::Rect);

private:
    Ui::MainWindow *ui;

    //GUI dropdown menus and corresponding actions
    QMenu *fileMenu;
    QAction *startCameraAction;
    QAction *stopCameraAction;
    QAction *aboutFacex;

    int StartVideoEventId;

    cv::Mat MatOriginalImage;   //original image obtained from webcam
    cv::Mat MatProcessedImage;  //processed image after applying algorithms, mainly Haar trained classifiers.

    cv::VideoCapture WebCamCaptureDevice;  //Capture Device i.e. Webcam

    std::vector< cv:: Rect > faceBoundingVector;    //Storing Bounding Vectors of detected face
    std::vector< cv:: Rect > eyeBoundingVector;     //Storing Bounding Vectors of detected eyes
    std::vector< cv::Rect > mouthBoundingVector;    //Storing Bounding Vectors of detected mouth

    int videoStatus; //detecting whether the input stream is video or camera

    // ---> Haar Face detectors
    cv::CascadeClassifier HaarFaceClassifier;
    cv::CascadeClassifier HaarEyeClassifier;
    cv::CascadeClassifier HaarMouthClassifier;
    // <--- Face detectors
};

#endif // MAINWINDOW_H
