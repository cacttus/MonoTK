#pragma once

#ifndef __MONOTK_HEADER_H__
#define __MONOTK_HEADER_H__

#define USE_MATH_DEFINES

#include <qmath.h>
#include <qopengl.h>

//#include <QOpenGLWindow>
#include <QMatrix4x4>
#include <QVector3D>
#include <QMatrix>

#include <QObject>
#include <QException>

typedef QVector3D vec3;
typedef QMatrix4x4 mat4;

class QuadDrawer;

QT_BEGIN_NAMESPACE
//OpeNGL
class QOpenGLTexture;
class QOpenGLShaderProgram;
class QOpenGLBuffer;
class QOpenGLVertexArrayObject;

//Widgets
class QOpenGLWidget;
class QMdiArea;
QT_END_NAMESPACE

class MonoInterface;

class Globals {
  public:
      static int argc;
      static char ** argv;
      static MonoInterface* _pMonoInterface;
};

class Exception : public QException{
    QString _what;
public:
    Exception(QString s){
        _what = s;
    }
    void raise() const { throw *this; }
    Exception *clone() const { return new Exception(*this); }
    virtual const char*
    what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT override {
        return _what.toStdString().c_str();
    }
};


#endif // MonoTKHeader
