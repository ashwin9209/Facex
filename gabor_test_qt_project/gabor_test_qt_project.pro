#-------------------------------------------------
#
# Project created by QtCreator 2014-03-04T15:59:22
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = gabor_test_qt_project
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp


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
