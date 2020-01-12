#pragma once

#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include "./MonoTKHeader.h"
#include <QSharedPointer.h>
#include <QOpenGLWidget.h>
#include <QTimer.h>

namespace MonoTK {

class OpenGLWidget : public QOpenGLWidget {
Q_OBJECT 

private:
  QOpenGLTexture* m_texture = nullptr;
  QOpenGLShaderProgram* m_program = nullptr;
  QOpenGLBuffer* m_verts_vbo = nullptr;
  QOpenGLBuffer* m_indexes_vbo = nullptr;
  QOpenGLVertexArrayObject* m_vao = nullptr;
  //Logo m_logo;
  int m_projMatrixLoc;
  int m_viewMatrixLoc;
  int m_modelMatrixLoc;
  int m_myMatrixLoc;
  float ang = 0;
  int m_lightPosLoc;
  QMatrix4x4 m_proj;
  QMatrix4x4 m_world;
  QVector3D m_eye;
  QVector3D m_target;
  bool m_uniformsDirty = true;
  float m_r = 0;
  float m_r2 = 0;

  QVector<GLfloat> m_data;
  int m_count = 0;

  int _indexCount=0;
  QVector<GLuint> indexes;

  QTimer timer;//for realtime updates.
  void addIdx(GLuint ind);

  const GLfloat* constData() const { return m_data.constData(); }
  int count() const { return m_count; }
  int vertexCount() const { return m_count / 6; }
  void  createLogo();
  void quad(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4);
  void extrude(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
  void add(const QVector3D& v, const QVector3D& n);
  virtual bool event(QEvent* e) override;

  bool paused = false;
protected:
  virtual void initializeGL() override;
  virtual void resizeGL(int w, int h) override;
  virtual void paintGL() override;
  void createTimer();
public:
  OpenGLWidget(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags()) : QOpenGLWidget(parent, f) {}

public slots:
    void updateGL();
};


}


#endif