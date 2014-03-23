#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
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

    /* Qt GUI Setup Functions */
    void createQtGUIActions();
    void createQtGUIMenus();

    /* Button-click functions */
                                                        // Start Detecting Face
    void on_actionStart_clicked();                      // Start Webcam Stream Button Action
    void on_actionStop_clicked();                       // Stop Webcam Stream Button Action
    void on_action_AboutFacex_clicked();


    void on_checkbox_FaceDetect_clicked();

private:
    Ui::MainWindow *ui;

    //GUI Dropdown Menus & Corresponding Actions
    QMenu *fileMenu;
    QAction *startCameraAction;
    QAction *stopCameraAction;
    QAction *aboutFacex;

    int StartVideoEventId; // Timer to Control Loop Flow

    cv::Mat MatOriginalImage;   //Original Image Obtained from Webcam
    cv::Mat MatProcessedImage;  //Processed Image After Applying Algorithms, mainly Haar Trained Classifiers.

    cv::VideoCapture WebCamCaptureDevice;  //Capture Device i.e. Webcam

    std::vector< cv:: Rect > faceBoundingVector;    //Storing Bounding Vectors of Detected Face
    std::vector< cv:: Rect > smileBoundingVector;
    std::vector< cv:: Rect >::iterator r;

    // ---> Haar Face detectors
    cv::CascadeClassifier HaarFaceClassifier;
    cv::CascadeClassifier HaarSmileClassifier;
    // <--- Face detectors

};

#endif // MAINWINDOW_H
