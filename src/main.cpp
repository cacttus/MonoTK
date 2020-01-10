#include "./MainWindow.h"
#include <QApplication>
#include <QSurfaceFormat>
#include <QOpenGLContext>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QSurfaceFormat fmt;
  fmt.setDepthBufferSize(24);

  // Request OpenGL 3.3 core or OpenGL ES 3.0.
  if (QOpenGLContext::openGLModuleType() == QOpenGLContext::LibGL) {
    qDebug("Requesting 3.3 core context");
    fmt.setVersion(3, 3);
    fmt.setProfile(QSurfaceFormat::CoreProfile);
  }
  else {
    qDebug("Requesting 3.0 context");
    fmt.setVersion(3, 0);
  }
  QSurfaceFormat::setDefaultFormat(fmt);

  MonoTK::MainWindow w;
  w.show();

  return a.exec();

    //QApplication a(argc, argv);

    //MonoTK::MainWindow w;
    //w.show();


    //return a.exec();
}