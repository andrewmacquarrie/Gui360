#-------------------------------------------------
#
# Project created by QtCreator 2015-03-31T14:46:20
#
#-------------------------------------------------

# Look here for issues http://stackoverflow.com/questions/27944074/cvvideocapture-from-string-gives-linker-error-in-qt5-on-mac

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Gui360
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    seamcut.cpp \
    maxflow/graph.cpp \
    maxflow/maxflow.cpp

HEADERS  += mainwindow.h \
    maxflow/block.h \
    maxflow/graph.h \
    seamcut.h

FORMS    += mainwindow.ui

QMAKE_LIBFLAGS += /VERBOSE
QMAKE_AR += -v

INCLUDEPATH += /usr/local/Cellar/opencv/2.4.10.1/include

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9

unix {

OPENCV_PATH = /usr/local/Cellar/opencv/2.4.10.1/lib

LIBS     += -L$$OPENCV_PATH

LIBS     += -lopencv_calib3d \
-lopencv_contrib \
-lopencv_core \
-lopencv_features2d \
-lopencv_flann \
-lopencv_gpu \
-lopencv_highgui \
-lopencv_imgproc \
-lopencv_legacy \
-lopencv_ml \
-lopencv_nonfree \
-lopencv_objdetect \
-lopencv_ocl \
-lopencv_photo \
-lopencv_stitching \
-lopencv_superres \
-lopencv_video \
-lopencv_videostab
}
