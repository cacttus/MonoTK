#
# Main QT Build file
# MonoTK, 2020
# MetalMario971
#

QT += core gui
QT += opengl
QT += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#https://doc.qt.io/qt-5/qmake-variable-reference.html
TEMPLATE = app
TARGET = MonoTK
DESTDIR = $$PWD/bin
CONFIG += debug
LIBS += -L"$$PWD"
DEPENDPATH += $$PWD/src
MOC_DIR += $$PWD/tmp/moc
OBJECTS_DIR += $$PWD/tmp/objects
UI_DIR += $$PWD/tmp/ui
RCC_DIR += $$PWD/tmp/rcc

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

HEADERS += $$PWD/src/MonoTKHeader.h \
    $$PWD/src/OpenGLWidget.h \
    $$PWD/src/MainWindow.h
SOURCES += $$PWD/src/main.cpp \
    $$PWD/src/OpenGLWidget.cpp \
    $$PWD/src/MainWindow.cpp
FORMS += $$PWD/src/mainwindow.ui
RESOURCES += $$PWD/src/MonoTK.qrc \
    $$PWD/qdarkstyle/style.qrc
