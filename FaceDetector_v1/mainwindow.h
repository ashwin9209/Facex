#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <opencv/cv.h>
#include <opencv/highgui.h>

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
    void on_actionCapture_triggered();

private:
    Ui::MainWindow* _ui;
    CvCapture*      _capture;
    IplImage*       _img;
    CvHaarClassifierCascade* _cascade;
    CvMemStorage*   _storage;
    QList<CvScalar>  _colors;
    QPixmap*         _pixmap;
    QTimer*          _timer;
};

#endif
