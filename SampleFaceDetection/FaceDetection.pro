QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FaceDetection
TEMPLATE = app

# Note: to be changed according to your OpenCV configuration
INCLUDEPATH += C:\\opencv\\build\\include

SOURCES += main.cpp\
        cmainwindow.cpp \
    cqtopencvviewergl.cpp

HEADERS  += cmainwindow.h \
    cqtopencvviewergl.h

FORMS    += cmainwindow.ui


win32 {
message("Using win32 configuration")

OPENCV_PATH = C:/opencv


#LIBS_PATH = "$$OPENCV_PATH/build/x86/mingw/lib" #project compiled using MINGW
#LIBS_PATH = "$$OPENCV_PATH/build/x86/vc10/lib" #project compiled using Visual C++ 2010 32bit compiler

    CONFIG(debug, debug|release) {
    #LIBS     += -L$$LIBS_PATH \
     #           -lopencv_core244d \
      #          -lopencv_highgui244d \
       #         -lopencv_objdetect244d

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

    }

    CONFIG(release, debug|release) {
    LIBS     += -L$$LIBS_PATH \
                -lopencv_core244 \
                -lopencv_highgui244 \
                -lopencv_objdetect244
    }

}

unix {
message("Using unix configuration")

OPENCV_PATH = /usr/local/opencv2/

LIBS     += -L$$LIBS_PATH \
            -lopencv_core \
            -lopencv_highgui \
            -lopencv_objdetect
}

INCLUDEPATH += $$OPENCV_PATH/modules/core/include/ \ #core module
    $$OPENCV_PATH/modules/highgui/include/ \ #highgui module
    $$OPENCV_PATH/modules/objdetect/include/ #obj_detect module

message("OpenCV path: $$OPENCV_PATH")
message("Includes path: $$INCLUDEPATH")
message("Libraries: $$LIBS")
