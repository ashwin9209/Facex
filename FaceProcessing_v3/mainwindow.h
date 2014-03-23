#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dialog.h"

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

public slots:
    void PreProcessingCheckBoxDisable();

private slots:

    /* Qt GUI Setup Functions */
    void createQtGUIActions();
    void createQtGUIMenus();

    /* Button-click functions */
    void on_checkBox_fullFace_clicked();                // Start Detecting Face
    void on_actionStart_clicked();                      // Start Webcam Stream Button Action
    void on_actionStop_clicked();                       // Stop Webcam Stream Button Action
    void on_action_AboutFacex_clicked();                // About the Project - Facex
    void on_checkBox_performPreProcessing_clicked();    //Start Pre-Processing Button Action

    /* Segmenting out detected areas of the face */
    void ExtractAndDisplayFaceROI(cv::Mat);
    void ExtractAndDisplayEyeROI(cv::Mat, cv::Rect);
    void ExtractAndDisplayMouthROI(cv::Mat, cv::Rect);

    /* Pre - Processing Functions */
    void StartPreProcessingImage();
    void StartPreProcessingGrayImage();
    void StartHistogramEqualization();
    void StartHSVImageConvert();




    /* Dead functions. May be revived later. */

    //void onShowdialog(QTimerEvent *event);
    //void on_btnPreProcessing_clicked();
    //void on_checkBox_performPreProcessing_stateChanged(int arg1);

    void on_btnSnapshot_clicked();

private:

    /* UI Objects */
    Ui::MainWindow *ui;
    Dialog *UI_Dialog_preprocess;

    //GUI Dropdown Menus & Corresponding Actions
    QMenu *fileMenu;
    QAction *startCameraAction;
    QAction *stopCameraAction;
    QAction *aboutFacex;

    int StartVideoEventId; // Timer to Control Loop Flow

    cv::Mat MatOriginalImage;   //Original Image Obtained from Webcam
    cv::Mat MatProcessedImage;  //Processed Image After Applying Algorithms, mainly Haar Trained Classifiers.
    cv::Mat MatGrayImage;
    cv::Mat MatResizedImage;
    cv::Mat MatHistEqualized;
    cv::Mat MatHSVImage;

    cv::VideoCapture WebCamCaptureDevice;  //Capture Device i.e. Webcam

    std::vector< cv:: Rect > faceBoundingVector;    //Storing Bounding Vectors of Detected Face
    std::vector< cv:: Rect > eyeBoundingVector;     //Storing Bounding Vectors of Detected Eyes
    std::vector< cv::Rect > mouthBoundingVector;    //Storing Bounding Vectors of Detected Mouth

    int videoStatus; // Stores status of Camera [Started/Unstarted]

    // ---> Haar Face detectors
    cv::CascadeClassifier HaarFaceClassifier;
    cv::CascadeClassifier HaarEyeClassifier;
    cv::CascadeClassifier HaarMouthClassifier;
    // <--- Face detectors
};

#endif // MAINWINDOW_H
