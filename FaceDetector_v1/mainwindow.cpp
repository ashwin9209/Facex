#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "opencv/cvaux.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);
    _capture = cvCaptureFromCAM( 0 );
    _cascade = (CvHaarClassifierCascade*)cvLoad("haarcascade_frontalface_alt2.xml");
    _storage = cvCreateMemStorage(0);

    _colors << cvScalar(0.0,0.0,255.0) << cvScalar(0.0,128.0,255.0)
            << cvScalar(0.0,255.0,255.0) << cvScalar(0.0,255.0,0.0)
            << cvScalar(255.0,128.0,0.0) << cvScalar(255.0,255.0,0.0)
            << cvScalar(255.0,0.0,0.0) << cvScalar(255.0,0.0,255.0);

    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(on_actionCapture_triggered()));
    _timer->start(10);
}

MainWindow::~MainWindow()
{
    cvReleaseImage(&_img);
    cvReleaseCapture(&_capture);
    delete _ui;
}

void MainWindow::on_actionCapture_triggered()
{
    // Query camera for next frame
    _img = cvQueryFrame( _capture );

    if (_img)
    {
        // Detect objects
        cvClearMemStorage( _storage );

        CvSeq* objects = cvHaarDetectObjects(_img,
                                             _cascade,
                                             _storage,
                                             1.1,
                                             3,
                                             CV_HAAR_DO_CANNY_PRUNING,
                                             cvSize( 100, 100 ));

        int n = (objects ? objects->total : 0);

        CvRect* r;
        // Loop through objects and draw boxes
        for( int i = 0; i < n; i++ )
        {
            r = ( CvRect* )cvGetSeqElem( objects, i );
            cvRectangle( _img,
                         cvPoint( r->x, r->y ),
                         cvPoint( r->x + r->width, r->y + r->height ),
                         _colors[i%8]
                        );
        }

        // Convert IplImage to QImage
        QImage image = QImage((const uchar *)_img->imageData,
                                             _img->width,
                                             _img->height,
                                             QImage::Format_RGB888).rgbSwapped();
        _pixmap = new QPixmap(QPixmap::fromImage(image));
        _ui->labelCapture->setPixmap(*_pixmap);
    }
}
