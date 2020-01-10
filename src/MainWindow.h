#pragma once

#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include "./MonoTKHeader.h"
#include <QtWidgets/QMainWindow>
#include <QSharedPointer.h>

namespace MonoTK {

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
  QMenuBar* menuBar;
  QToolBar* mainToolBar;
  QWidget* centralWidget;
  QStatusBar* statusBar;
  QOpenGLWidget* openGLWidget;
public:
    MainWindow(QWidget *parent = Q_NULLPTR);
    virtual ~MainWindow();
};

}


#endif