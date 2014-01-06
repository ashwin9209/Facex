#-------------------------------------------------
#
# Project created by QtCreator 2013-12-01T10:39:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FacexInput
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp

HEADERS  += dialog.h

FORMS    += dialog.ui

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
 -llibopencv_video244 \
 -llibopencv_videostab244
