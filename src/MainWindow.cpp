#include "./MainWindow.h"

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <QtWidgets/QOpenGLWidget>

namespace MonoTK {

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent) {

  //Set name, ?
  setObjectName(QString::fromUtf8("MonoTKClass"));
  resize(600, 400);

  menuBar = new QMenuBar(this);
  menuBar->setObjectName(QString::fromUtf8("menuBar"));
  setMenuBar(menuBar);
  mainToolBar = new QToolBar(this);
  mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
  addToolBar(mainToolBar);

  //https://doc.qt.io/qt-5/qtwidgets-mainwindows-menus-example.html


  //Central Widget
  centralWidget = new QWidget(this);
  centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
  setCentralWidget(centralWidget);

  //Status bar
  statusBar = new QStatusBar(this);
  statusBar->setObjectName(QString::fromUtf8("statusBar"));
  setStatusBar(statusBar);
  QString message = tr("A context menu is available by right-clicking");
  statusBar->showMessage(message);

  setWindowTitle(QApplication::translate("MonoTKClass", "MonoTK", nullptr));

  QMetaObject::connectSlotsByName(this);


//  if (useOpenGL) {
      QSurfaceFormat format = QSurfaceFormat::defaultFormat();
      format.setDepthBufferSize(0);   // No need for a depth buffer
      format.setSamples(4);           // Enable anti-aliasing

      openGLWidget = new QOpenGLWidget(this);
      openGLWidget->setFormat(format);
     // setViewport(openGLWidget);
    }
  //}
  //else {
  //  if (qobject_cast<QOpenGLWidget*>(viewport()))
  //    setViewport(nullptr);
  //}

  //QWidget* v = viewport();
  //if (mMode == StaticContents)
  //  v->setAttribute(Qt::WA_StaticContents);
  //v->setMouseTracking(true);
}
MainWindow::~MainWindow(){
}


}//ns MonoTK