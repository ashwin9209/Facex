#-------------------------------------------------
#
# Project created by QtCreator 2014-03-21T14:40:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmileDetect_v1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH += C:\\opencv\\build\\include

LIBS += -LC:\\opencvmybuild\\lib \
 -llibopencv_calib3d244 \
 -llibopencv_contrib244 \
 -llibopencv_core244 \
 -llibopencv_features2d244 \
 -llibopencv_flann244 \
 -llibopencv_gpu244 \
 -llibopencv_highgui244 \
 -llibopencv_imgproc244 \
 -llibopencv_legacy244 \
 -llibopencv_ml244 \
 -llibopencv_nonfree244 \
 -llibopencv_objdetect244 \
 -llibopencv_photo244 \
 -llibopencv_stitching244 \
