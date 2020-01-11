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

typedef QVector3D vec3;
typedef QMatrix4x4 mat4;

class QuadDrawer;

QT_BEGIN_NAMESPACE

class QOpenGLTexture;
class QOpenGLShaderProgram;
class QOpenGLBuffer;
class QOpenGLVertexArrayObject;

QT_END_NAMESPACE


#endif // MonoTKHeader
