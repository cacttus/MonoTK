/**
*
*  @file MainWindow
*  @date 01/12/2020
*  @author MetalMario
*
*/
#pragma once
#ifndef __MAINWINDOW_2065632464431033_H__
#define __MAINWINDOW_2065632464431033_H__

#include "./MonoTKHeader.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QMdiArea;
QT_END_NAMESPACE

namespace MonoTK {
/**
*  @class MainWindow
*  @brief
*
*/
class MainWindow : public QMainWindow {
  Q_OBJECT

private:
  QMenuBar* menuBar;
  QToolBar* mainToolBar;
  //QWidget* centralWidget;
  QStatusBar* statusBar;
  QOpenGLWidget* openGLWidget;

  QMdiArea* _pMDIArea=nullptr;

public:
  MainWindow(QWidget* parent = Q_NULLPTR);
  virtual ~MainWindow();
};
}//ns MonoTK

#endif
