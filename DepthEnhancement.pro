#-------------------------------------------------
#
# Project created by QtCreator 2015-03-17T15:48:19
# Author: Frederic GARCIA BECERRO
# Email: frederic.garcia.becerro@gmail.com
# Website: http://www.frederic-garcia-becerro.com
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DepthEnhancement
TEMPLATE = app

CONFIG += console

SOURCES += main.cpp\
        c_datafusion.cpp \
        mainclass.cpp \
        globals.cpp
#        mainwindow.cpp

HEADERS  += \
         app_types.h \
         c_datafusion.h \
         mainclass.h \
         globals.h
#         mainwindow.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): DEFINES += QT_NO_DEBUG_OUTPUT
win32:CONFIG(debug, debug|release): DEFINES += QT_DEBUG_MODE

#add OpenCV Libraries
INCLUDEPATH += J:\sdk\opencv-3.0.0\build\include
INCLUDEPATH += J:\sdk\opencv-3.0.0\build\include\opencv
win32:CONFIG(release, debug|release): LIBS += -LJ:\sdk\opencv-3.0.0\build\x64\vc12\lib \
        -lopencv_core300 \
        -lopencv_calib3d300 \
        -lopencv_contrib300 \
        -lopencv_features2d300 \
        -lopencv_flann300 \
        -lopencv_gpu300 \
        -lopencv_highgui300 \
        -lopencv_imgproc300 \
        -lopencv_legacy300 \
        -lopencv_ml300 \
        -lopencv_nonfree300 \
        -lopencv_objdetect300 \
        -lopencv_photo300 \
        -lopencv_stitching300 \
        -lopencv_video300 \
        -lopencv_videostab300
else: LIBS += -LJ:\sdk\opencv-3.0.0\build\x64\vc12\lib \
        -lopencv_core300d \
        -lopencv_calib3d300d \
        -lopencv_contrib300d \
        -lopencv_features2d300d \
        -lopencv_flann300d \
        -lopencv_gpu300d \
        -lopencv_highgui300d \
        -lopencv_imgproc300d \
        -lopencv_legacy300d \
        -lopencv_ml300d \
        -lopencv_nonfree300d \
        -lopencv_objdetect300d \
        -lopencv_photo300d \
        -lopencv_stitching300d \
        -lopencv_video300d \
        -lopencv_videostab300d

#add destination directory
win32:CONFIG(release, debug|release): DESTDIR = J:\git\build-DepthEnhancement-Desktop_Qt_5_4_2_MSVC2013_64bit-Release\release
else: DESTDIR = J:\git\build-DepthEnhancement-Desktop_Qt_5_4_2_MSVC2013_64bit-Release\release

win32:CONFIG(release, debug|release): QMAKE_POST_LINK  += copy J:\\sdk\\qt5\\5.4\\msvc2013_64\\bin\\Qt5Core.dll $${DESTDIR}\\Qt5Core.dll \
                       & copy J:\\sdk\\qt5\\5.4\\msvc2013_64\\bin\\Qt5Gui.dll $${DESTDIR}\\Qt5Gui.dll \
                       & copy J:\\sdk\\qt5\\5.4\\msvc2013_64\\bin\\Qt5OpenGL.dll $${DESTDIR}\\Qt5OpenGL.dll \
                       & copy J:\\sdk\\qt5\\5.4\\msvc2013_64\\bin\\icuin53.dll $${DESTDIR}\\icuin53.dll \
                       & copy J:\\sdk\\qt5\\5.4\\msvc2013_64\\bin\\icudt53.dll $${DESTDIR}\\icudt53.dll \
                       & copy J:\\sdk\\qt5\\5.4\\msvc2013_64\\bin\\icuuc53.dll $${DESTDIR}\\icuuc53.dll \
                       & copy J:\\sdk\\qt5\\5.4\\msvc2013_64\\bin\\Qt5Widgets.dll $${DESTDIR}\\Qt5Widgets.dll \
                       & mkdir $${DESTDIR}\\platforms \
                       & copy J:\\sdk\\qt5\\5.4\\msvc2013_64\\plugins\\platforms\\qwindows.dll $${DESTDIR}\\platforms\\qwindows.dll \
                       & copy J:\\sdk\\opencv-3.0.0\\build\x64\\vc12\\bin\\opencv_core300.dll $${DESTDIR}\\opencv_core300.dll \
                       & copy J:\\sdk\\opencv-3.0.0\\build\x64\\vc12\\bin\\opencv_calib3d300.dll $${DESTDIR}\\opencv_calib3d300.dll \
                       & copy J:\\sdk\\opencv-3.0.0\\build\x64\\vc12\\bin\\opencv_contrib300.dll $${DESTDIR}\\opencv_contrib300.dll \
                       & copy J:\\sdk\\opencv-3.0.0\\build\x64\\vc12\\bin\\opencv_features2d300.dll $${DESTDIR}\\opencv_features2d300.dll \
                       & copy J:\\sdk\\opencv-3.0.0\\build\x64\\vc12\\bin\\opencv_flann300.dll $${DESTDIR}\\opencv_flann300.dll \
                       & copy J:\\sdk\\opencv-3.0.0\\build\x64\\vc12\\bin\\opencv_gpu300.dll $${DESTDIR}\\opencv_gpu300.dll \
                       & copy J:\\sdk\\opencv-3.0.0\\build\x64\\vc12\\bin\\opencv_highgui300.dll $${DESTDIR}\\opencv_highgui300.dll \
                       & copy J:\\sdk\\opencv-3.0.0\\build\x64\\vc12\\bin\\opencv_imgproc300.dll $${DESTDIR}\\opencv_imgproc300.dll \
                       & copy J:\\sdk\\opencv-3.0.0\\build\x64\\vc12\\bin\\opencv_legacy300.dll $${DESTDIR}\\opencv_legacy300.dll \
                       & copy J:\\sdk\\opencv-3.0.0\\build\x64\\vc12\\bin\\opencv_ml300.dll $${DESTDIR}\\opencv_ml300.dll \
                       & copy J:\\sdk\\opencv-3.0.0\\build\x64\\vc12\\bin\\opencv_nonfree300.dll $${DESTDIR}\\opencv_nonfree300.dll \
                       & copy J:\\sdk\\opencv-3.0.0\\build\x64\\vc12\\bin\\opencv_objdetect300.dll $${DESTDIR}\\opencv_objdetect300.dll \
                       & copy J:\\sdk\\opencv-3.0.0\\build\x64\\vc12\\bin\\opencv_photo300.dll $${DESTDIR}\\opencv_photo300.dll \
                       & copy J:\\sdk\\opencv-3.0.0\\build\x64\\vc12\\bin\\opencv_stitching300.dll $${DESTDIR}\\opencv_stitching300.dll \
                       & copy J:\\sdk\\opencv-3.0.0\\build\x64\\vc12\\bin\\opencv_video300.dll $${DESTDIR}\\opencv_video300.dll \
                       & copy J:\\sdk\\opencv-3.0.0\\build\x64\\vc12\\bin\\opencv_videostab300.dll $${DESTDIR}\\opencv_videostab300.dll \
                       & copy J:\\sdk\\opencv-3.0.0\\build\x64\\vc12\\bin\\opencv_ffmpeg300.dll $${DESTDIR}\\opencv_ffmpeg300.dll
#else: QMAKE_POST_LINK  += copy C:\\Qt\\Qt5.3.2\\5.3\\msvc2010_opengl\\bin\\Qt5Cored.dll $${DESTDIR}\\Qt5Cored.dll \
#                       & copy C:\\Qt\\Qt5.3.2\\5.3\\msvc2010_opengl\\bin\\Qt5Guid.dll $${DESTDIR}\\Qt5Guid.dll \
#                       & copy C:\\Qt\\Qt5.3.2\\5.3\\msvc2010_opengl\\bin\\Qt5OpenGLd.dll $${DESTDIR}\\Qt5OpenGLd.dll \
#                       & copy C:\\Qt\\Qt5.3.2\\5.3\\msvc2010_opengl\\bin\\icuin53.dll $${DESTDIR}\\icuin53.dll \
#                       & copy C:\\Qt\\Qt5.3.2\\5.3\\msvc2010_opengl\\bin\\icudt53.dll $${DESTDIR}\\icudt53.dll \
#                       & copy C:\\Qt\\Qt5.3.2\\5.3\\msvc2010_opengl\\bin\\icuuc53.dll $${DESTDIR}\\icuuc53.dll \
#                       & copy C:\\Qt\\Qt5.3.2\\5.3\\msvc2010_opengl\\bin\\Qt5Widgetsd.dll $${DESTDIR}\\Qt5Widgetsd.dll \
#                       & mkdir $${DESTDIR}\\platforms \
#                       & copy C:\\Qt\\Qt5.3.2\\5.3\\msvc2010_opengl\\plugins\\platforms\\qwindowsd.dll $${DESTDIR}\\platforms\\qwindowsd.dll \
#                       & copy J:\\sdk\\opencv-3.0.0\\build\\x64\\vc12\\bin\\opencv_core300d.dll $${DESTDIR}\\opencv_core300d.dll \
#                       & copy J:\\sdk\\opencv-3.0.0\\build\\x64\\vc12\\bin\\opencv_calib3d300d.dll $${DESTDIR}\\opencv_calib3d300d.dll \
#                       & copy J:\\sdk\\opencv-3.0.0\\build\\x64\\vc12\\bin\\opencv_contrib300d.dll $${DESTDIR}\\opencv_contrib300d.dll \
#                       & copy J:\\sdk\\opencv-3.0.0\\build\\x64\\vc12\\bin\\opencv_features2d300d.dll $${DESTDIR}\\opencv_features2d300d.dll \
#                       & copy J:\\sdk\\opencv-3.0.0\\build\\x64\\vc12\\bin\\opencv_flann300d.dll $${DESTDIR}\\opencv_flann300d.dll \
#                       & copy J:\\sdk\\opencv-3.0.0\\build\\x64\\vc12\\bin\\opencv_gpu300d.dll $${DESTDIR}\\opencv_gpu300d.dll \
#                       & copy J:\\sdk\\opencv-3.0.0\\build\\x64\\vc12\\bin\\opencv_highgui300d.dll $${DESTDIR}\\opencv_highgui300d.dll \
#                       & copy J:\\sdk\\opencv-3.0.0\\build\\x64\\vc12\\bin\\opencv_imgproc300d.dll $${DESTDIR}\\opencv_imgproc300d.dll \
#                       & copy J:\\sdk\\opencv-3.0.0\\build\\x64\\vc12\\bin\\opencv_legacy300d.dll $${DESTDIR}\\opencv_legacy300d.dll \
#                       & copy J:\\sdk\\opencv-3.0.0\\build\\x64\\vc12\\bin\\opencv_ml300d.dll $${DESTDIR}\\opencv_ml300d.dll \
#                       & copy J:\\sdk\\opencv-3.0.0\\build\\x64\\vc12\\bin\\opencv_nonfree300d.dll $${DESTDIR}\\opencv_nonfree300d.dll \
#                       & copy J:\\sdk\\opencv-3.0.0\\build\\x64\\vc12\\bin\\opencv_objdetect300d.dll $${DESTDIR}\\opencv_objdetect300d.dll \
#                       & copy J:\\sdk\\opencv-3.0.0\\build\\x64\\vc12\\bin\\opencv_photo300d.dll $${DESTDIR}\\opencv_photo300d.dll \
#                       & copy J:\\sdk\\opencv-3.0.0\\build\\x64\\vc12\\bin\\opencv_stitching300d.dll $${DESTDIR}\\opencv_stitching300d.dll \
#                       & copy J:\\sdk\\opencv-3.0.0\\build\\x64\\vc12\\bin\\opencv_video300d.dll $${DESTDIR}\\opencv_video300d.dll \
#                       & copy J:\\sdk\\opencv-3.0.0\\build\\x64\\vc12\\bin\\opencv_videostab300d.dll $${DESTDIR}\\opencv_videostab300d.dll \
#                       & copy J:\\sdk\\opencv-3.0.0\\build\\x64\\vc12\\bin\\opencv_ffmpeg300.dll $${DESTDIR}\\opencv_ffmpeg300.dll
