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


#include "ui_mainwindow.h"

namespace MonoTK {
/**
*  @class MainWindow
*  @brief
*
*/
class MainWindow : public QMainWindow {
  Q_OBJECT

private:
  Ui::MainWindow ui;

  QMenuBar* menuBar;
  QToolBar* mainToolBar;
  QStatusBar* statusBar;
  QOpenGLWidget* openGLWidget;

  QMdiArea* _pMDIArea=nullptr;

public:
  MainWindow(QWidget* parent = Q_NULLPTR);
  virtual ~MainWindow();

  private slots:
      //https://doc.qt.io/qt-5/qmetaobject.html#connectSlotsByName
      //void on_<object name>_<signal name>(<signal parameters>);
      void on_comboBox_currentIndexChanged(int index);
      void on_actionExit_triggered();
      void on_pushButton_clicked();
};
}//ns MonoTK

#endif
