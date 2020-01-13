#include "./MainWindow.h"
#include "./OpenGLWidget.h"
#include <QtCore/QVariant>
#include <QOpenGLWidget>
#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QStandardPaths>
#include <QMessageBox>


namespace MonoTK {

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  ui.setupUi(this);


  //QStandardPaths::LocateFile()
  //QStandardPaths::
//Set name, ?
//setObjectName(QString::fromUtf8("MonoTKClass"));
//resize(600, 400);

    //  menuBar = new QMenuBar(this);
    //  menuBar->setObjectName(QString::fromUtf8("menuBar"));
    //  setMenuBar(menuBar);
    //  mainToolBar = new QToolBar(this);
    //  mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
    //  addToolBar(mainToolBar);
    
    //  //https://doc.qt.io/qt-5/qtwidgets-mainwindows-menus-example.html
      
    //  //Status bar
    //  statusBar = new QStatusBar(this);
    //  statusBar->setObjectName(QString::fromUtf8("statusBar"));
    //  setStatusBar(statusBar);
    //  QString message = tr("A context menu is available by right-clicking");
    //  statusBar->showMessage(message);
    
    //  setWindowTitle(QApplication::translate("MonoTKClass", "MonoTK", nullptr));
    
    //  QMetaObject::connectSlotsByName(this);
    
    //  // Try to create 4 sub-windows
    //  // checkto see if the opengl context is shared among sub windows.
    //  QMdiSubWindow* subWindow;
    
    //  QSurfaceFormat format = QSurfaceFormat::defaultFormat();
    //  format.setDepthBufferSize(24);   // No need for a depth buffer
    //  format.setSamples(4);           // Enable anti-aliasing
    //  format.setSwapInterval(1);
    
    //  _pMDIArea = new QMdiArea(this);
    //  setCentralWidget(_pMDIArea);
    
    //  openGLWidget = new OpenGLWidget(this);
    //  openGLWidget->setFormat(format);
    // // setCentralWidget(openGLWidget);
    //  subWindow = new QMdiSubWindow;
    //  subWindow->setWidget(openGLWidget);
    //  subWindow->setAttribute(Qt::WA_DeleteOnClose);
    //  subWindow->setFixedSize(this->width() * 0.25, 200);
    //  _pMDIArea->addSubWindow(subWindow);
    
    //  openGLWidget = new OpenGLWidget(this);
    //  openGLWidget->setFormat(format);
    ////  setCentralWidget(openGLWidget);
    //  subWindow = new QMdiSubWindow;
    //  subWindow->setWidget(openGLWidget);
    //  subWindow->setAttribute(Qt::WA_DeleteOnClose);
    //  subWindow->setFixedSize(this->width() * 0.25, 200);
    //  _pMDIArea->addSubWindow(subWindow);
    
    //  openGLWidget = new OpenGLWidget(this);
    //  openGLWidget->setFormat(format);
    ////  setCentralWidget(openGLWidget);
    //  subWindow = new QMdiSubWindow;
    //  subWindow->setWidget(openGLWidget);
    //  subWindow->setAttribute(Qt::WA_DeleteOnClose);
    //  subWindow->setFixedSize(this->width() * 0.25, 200);
    //  _pMDIArea->addSubWindow(subWindow);
    
    //  openGLWidget = new OpenGLWidget(this);
    //  openGLWidget->setFormat(format);
    //  //setCentralWidget(openGLWidget);
    //  subWindow = new QMdiSubWindow;
    //  subWindow->setWidget(openGLWidget);
    //  subWindow->setAttribute(Qt::WA_DeleteOnClose);
    //  subWindow->setFixedSize(this->width() * 0.25, 200);
    //  _pMDIArea->addSubWindow(subWindow);

    //  v->setAttribute(Qt::WA_StaticContents);
    //v->setMouseTracking(true);

  //connect(newAct, &QAction::triggered, this, &MainWindow::newFile);
}
MainWindow::~MainWindow() {
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
  QMessageBox msgBox;
  QString docs = QStandardPaths::locate(QStandardPaths::DocumentsLocation, QString(), QStandardPaths::LocateDirectory);
  msgBox.setText("Docs = " + docs);
  msgBox.exec();
}

void MainWindow::on_actionExit_triggered()
{
  QCoreApplication::quit();
}



}//ns MonoTK


