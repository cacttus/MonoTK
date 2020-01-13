#include <QApplication>
#include <QSurfaceFormat>
#include <QOpenGLContext>
#include <QSettings>
#include <QStyleFactory>
#include <QFile>
#include <QDebug>
#include <QDir>

#include "./MainWindow.h"

void setStyle(QApplication* a);
void setOpenGLFormat();
void setWorkingDirectory();
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  setWorkingDirectory();

  setStyle(&a);

  setOpenGLFormat();

  MonoTK::MainWindow w;
  w.show();

  return a.exec();
}
void setWorkingDirectory(){
    qDebug() << QDir::currentPath();
    if (!QDir::setCurrent(QStringLiteral("./"))){
        qDebug() << "Could not change the current working directory";
    }
    qDebug() << QDir::currentPath();
}
void setOpenGLFormat() {
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
}
void setStyle(QApplication* a) {
  //qApp is a macro to access the app
  //https://doc.qt.io/archives/qt-4.8/QApplication.html#macros
  QFile f(":qdarkstyle/style.qss");
  if (!f.exists()) {
    printf("Unable to set stylesheet, file not found\n");
  }
  else {
    f.open(QFile::ReadOnly | QFile::Text);
    QTextStream ts(&f);
    qApp->setStyleSheet(ts.readAll());
  }
  /*
//https://forum.qt.io/topic/101391/windows-10-dark-theme/4
#ifdef Q_OS_WIN
  QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", QSettings::NativeFormat);
  if (settings.value("AppsUseLightTheme") == 0) {
    a->setStyle(QStyleFactory::create("Fusion"));
    QPalette darkPalette;
    QColor darkColor = QColor(45, 45, 45);
    QColor disabledColor = QColor(127, 127, 127);
    darkPalette.setColor(QPalette::Window, darkColor);
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(18, 18, 18));
    darkPalette.setColor(QPalette::AlternateBase, darkColor);
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Disabled, QPalette::Text, disabledColor);
    darkPalette.setColor(QPalette::Button, darkColor);
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, disabledColor);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));

    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    darkPalette.setColor(QPalette::Disabled, QPalette::HighlightedText, disabledColor);

    qApp->setPalette(darkPalette);

    qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
  }
#endif
  */
}
