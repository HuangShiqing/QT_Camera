#-------------------------------------------------
#
# Project created by QtCreator 2019-03-30T10:28:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Camera
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    thread.cpp \
    camera_basler.cpp

HEADERS  += mainwindow.h \
    thread.h \
    camera_basler.h

FORMS    += mainwindow.ui


INCLUDEPATH += /opt/pylon5/include
DEPENDPATH += /opt/pylon5/include

unix:!macx: LIBS += -L$$PWD/../../../../../../opt/pylon5/lib64/ -lpylonbase -lpylonutility -lGenApi_gcc_v3_1_Basler_pylon -lGCBase_gcc_v3_1_Basler_pylon
INCLUDEPATH += $$PWD/../../../../../../opt/pylon5/lib64
DEPENDPATH += $$PWD/../../../../../../opt/pylon5/lib64
QMAKE_LFLAGS += "-Wl,--enable-new-dtags -Wl,-rpath,/opt/pylon5/lib64"

#opencv
unix:!macx: LIBS += -L$$PWD/../../../../../../usr/lib/ -lopencv_calib3d -lopencv_ml -lopencv_core -lopencv_photo -lopencv_dnn -lopencv_shape -lopencv_features2d -lopencv_stitching -lopencv_flann -lopencv_superres -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_imgproc -lopencv_videostab -lopencv_ml
INCLUDEPATH += $$PWD/../../../../../../usr/include
DEPENDPATH += $$PWD/../../../../../../usr/include


