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

#MONO
#OUT_PWD - where qmake places the makefile
INCLUDEPATH +=  $$PWD/external/Mono/include/mono-2.0/
#Note: Just adding the .lib won't work.  And Mono apparently doesn't support static linkage.  See: https://stackoverflow.com/questions/12326401/qt-specify-dll-path-in-pro-file
#You do not need to put the dll path in the .pro file (windows). All you need to do is to put all your external dll files in a directory and add this directory to the path environment variable . (same as the accepted answer). I am adding this here just to mention important fact: RESTART QT CREATOR for this to work in order to reload the new PATH environment variable.
#LIBS +=  -L$$PWD/external/Mono/lib/libmono-static-sgen.lib
LIBS += $$PWD/external/Mono/lib/mono-2.0-sgen.lib


#Compile Assembly with mono compiler
MCS_APPNAME = test.exe
MCS_APPPATH = $$PWD/bin/$$MCS_APPNAME
MCS_COMPILE = $$PWD/external/Mono/bin/mcs
#-g = debug, -target:  exe, winexe, library, module, -unsafe is possible
MCS_COMPILE_FLAGS = -platform:anycpu -out:$$MCS_APPPATH -debug -main:MonoTK.Program -target:exe
MCS_COMPILE_FILES = $$system_quote($$PWD/src/test.cs)
MCS_COMPILE_FINAL = $$MCS_COMPILE $$MCS_COMPILE_FLAGS $$MCS_COMPILE_FILES
#https://doc.qt.io/archives/qt-4.8/qmake-function-reference.html#system-command
#Delete the app
#message("deleting " $$MCS_APPPATH)
#DEL_COMMAND = del "$$MCS_APPPATH"
#DEL_OUTPUT $$system($$DEL_COMMAND)
#message("delete output:" $$DEL_OUTPUT)
#Compile
message("compiling:" $$MCS_COMPILE_FINAL)
MCS_OUTPUT = $$system($$MCS_COMPILE_FINAL)
message("compile output:" $$MCS_OUTPUT)

#BUNDLE_COMPILE = "mkbundle --static --deps -z $$MCS_APPNAME -o "
# https://stackoverflow.com/questions/10719828/compiling-mono-as-static-library

#MonogameTK
HEADERS += $$PWD/src/MonoTKHeader.h \
    $$PWD/src/OpenGLWidget.h \
    $$PWD/src/MainWindow.h \
    src/MonoInterface.h
SOURCES += $$PWD/src/main.cpp \
    $$PWD/src/OpenGLWidget.cpp \
    $$PWD/src/MainWindow.cpp \
    src/MonoInterface.cpp
FORMS += $$PWD/src/mainwindow.ui
RESOURCES += $$PWD/src/MonoTK.qrc \
    $$PWD/qdarkstyle/style.qrc
