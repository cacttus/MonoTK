#include "./MainWindow.h"

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <QtWidgets/QOpenGLWidget>

#include <QImage>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLExtraFunctions>
#include <QPropertyAnimation>
#include <QPauseAnimation>
#include <QSequentialAnimationGroup>
#include <QTimer>
#include <QDir>
#include <QPaintEvent>



namespace MonoTK {
static const char* vertexShaderSource =
"layout(location = 0) in vec4 vertex;\n"
"layout(location = 1) in vec3 normal;\n"
"\n"
"out vec3 vert;\n"
"out vec3 vertNormal;\n"
"out vec3 color;\n"
"\n"
"uniform mat4 projMatrix;\n"
"uniform mat4 viewMatrix;\n"
"uniform mat4 modelMatrix;\n"
"uniform sampler2D sampler;\n"
"\n"
"void main() {\n"
"   color = vec3(1,.2f,.2f);\n"
"   vertNormal = mat3(transpose(inverse(modelMatrix))) * normal;\n"
"   gl_Position = projMatrix * viewMatrix * modelMatrix * vertex;\n"
"}\n";

static const char* fragmentShaderSource =
"in highp vec3 vert;\n"
"in highp vec3 vertNormal;\n"
"in highp vec3 color;\n"
"\n"
"out highp vec4 fragColor;\n"
"\n"
"uniform highp vec3 lightPos;\n"
"\n"
"void main() {\n"
"   highp vec3 L = normalize(lightPos - vert);\n"
"   highp float NL = max(dot(normalize(vertNormal), L), 0.0);\n"
"   highp vec3 col = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);\n"
"   fragColor = vec4(col, 1.0);\n"
"}\n";
void OpenGLWidget::updateGL() {
  this->paintGL();
}
void OpenGLWidget::createTimer() {
  // Configure the timer
  //AAAH thank you https://stackoverflow.com/questions/15002045/how-to-force-qglwidget-to-update-screen
  //Not so much //https://stackoverflow.com/questions/17167194/how-to-make-updategl-realtime-in-qt
  connect(&timer, SIGNAL(timeout()), this, SLOT(update()));

  if (format().swapInterval() == -1) {
    // V_blank synchronization not available (tearing likely to happen)
    qDebug("Swap Buffers at v_blank not available: refresh at approx 60fps.");
    timer.setInterval(17);
  }
  else {
    // V_blank synchronization available
    timer.setInterval(0);
  }
  timer.start();
}
QByteArray versionedShaderCode(const char* src) {
  QByteArray versionedSrc;

  if (QOpenGLContext::currentContext()->isOpenGLES()) {
    versionedSrc.append(QByteArrayLiteral("#version 300 es\n"));
  }
  else {
    versionedSrc.append(QByteArrayLiteral("#version 330\n"));
  }

  versionedSrc.append(src);
  return versionedSrc;
}
void OpenGLWidget::initializeGL() {
  QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();

  if (m_texture) {
    delete m_texture;
    m_texture = 0;
  }

  //QDir::setSearchPaths("icons", QStringList(QDir::currentPath() + "/images"));

  QImage img(QDir::currentPath() + "/images/qtlogo.png");
  Q_ASSERT(!img.isNull());
  m_texture = new QOpenGLTexture(img.scaled(32, 36).mirrored());

  if (m_program) {
    delete m_program;
    m_program = 0;
  }

  m_program = new QOpenGLShaderProgram;
  // Prepend the correct version directive to the sources. The rest is the
  // same, thanks to the common GLSL syntax.
  m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, versionedShaderCode(vertexShaderSource));
  m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, versionedShaderCode(fragmentShaderSource));
  m_program->link();

  m_projMatrixLoc = m_program->uniformLocation("projMatrix");
  m_viewMatrixLoc = m_program->uniformLocation("viewMatrix");
  m_modelMatrixLoc = m_program->uniformLocation("modelMatrix");
  m_lightPosLoc = m_program->uniformLocation("lightPos");

  // Create a VAO. Not strictly required for ES 3, but it is for plain OpenGL.
  if (m_vao) {
    delete m_vao;
    m_vao = nullptr;
  }
  m_vao = new QOpenGLVertexArrayObject;
  if (m_vao->create()) {
    m_vao->bind();
  }

  if (m_verts_vbo) {
    delete m_verts_vbo;
    m_verts_vbo = nullptr;
  }

  //Main setup functions
  float w = 0.5;

  m_data.resize(4 * 6);
  add(vec3(-w, -w, -w), vec3(0, 0, 1));
  add(vec3(w, -w, -w), vec3(0, 0, 1));
  add(vec3(-w, w, -w), vec3(0, 0, 1));
  add(vec3(w, w, -w), vec3(0, 0, 1));

  createTimer();
  m_eye = vec3(0, 5, -5);
  m_target = vec3((m_eye * -1).normalized());

  m_program->bind();
  m_verts_vbo = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
  m_verts_vbo->create();
  m_verts_vbo->bind();
  m_verts_vbo->allocate(constData(), count() * sizeof(GLfloat));
  f->glEnableVertexAttribArray(0);
  f->glEnableVertexAttribArray(1);
  f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
  f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));
  m_verts_vbo->release();

  m_vao->release();
  
  indexes.resize(6);
  addIdx(2);
  addIdx(1);
  addIdx(0);
  addIdx(2);
  addIdx(3);
  addIdx(1);

  m_indexes_vbo = new QOpenGLBuffer(QOpenGLBuffer::Type::IndexBuffer);
  m_indexes_vbo->create();
  m_indexes_vbo->bind();
  m_indexes_vbo->allocate(indexes.constData(), indexes.count() * sizeof(GLuint));
  m_indexes_vbo->release();

  f->glEnable(GL_DEPTH_TEST);
  //f->glEnable(GL_CULL_FACE);
  f->glDisable(GL_CULL_FACE);
};
void OpenGLWidget::add(const QVector3D& v, const QVector3D& n) {
  GLfloat* p = m_data.data() + m_count;
  *p++ = v.x();
  *p++ = v.y();
  *p++ = v.z();
  *p++ = n.x();
  *p++ = n.y();
  *p++ = n.z();
  m_count += 6;
}
void OpenGLWidget::addIdx(GLuint ind) {
  GLuint* p = indexes.data() + _indexCount;
  *p = ind;
  _indexCount++;
}
void OpenGLWidget::resizeGL(int w, int h) {
  m_proj.setToIdentity();
  m_proj.perspective(45.0f, GLfloat(w) / h, 0.01f, 100.0f);
  m_uniformsDirty = true;
}
void OpenGLWidget::paintGL() {
  // Now use QOpenGLExtraFunctions instead of QOpenGLFunctions as we want to
// do more than what GL(ES) 2.0 offers.
  QOpenGLExtraFunctions* f = QOpenGLContext::currentContext()->extraFunctions();

//#define rd() ((float)(rand() % RAND_MAX) / (float)RAND_MAX)

  f->glClearColor(1,1, 1, 1);
  f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  m_program->bind();
  m_texture->bind();

 /// if (m_uniformsDirty) {
 //   m_uniformsDirty = false;
    QMatrix4x4 camera;
    camera.lookAt(m_eye, m_eye + m_target, QVector3D(0, 1, 0));
    m_program->setUniformValue(m_projMatrixLoc, m_proj);
    m_program->setUniformValue(m_viewMatrixLoc, camera);
    m_program->setUniformValue(m_lightPosLoc, QVector3D(20, 20, 0));
 // }

  //Rotae
  ang = fmodf(ang += 0.1f, (M_PI * 2.0f));
  mat4 model;
  model.setToIdentity();
  model.rotate( qRadiansToDegrees(ang), 0, 1, 0);
  m_program->setUniformValue(m_modelMatrixLoc, model);

  m_vao->bind();
  {
    m_indexes_vbo->bind();
    f->glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_INT, (void*)0);
  }
  m_vao->release();


  //QPaintEvent ee(QRect(QPoint(0, 0), size()));
  //Q_Q(QWidget);
  //QCoreApplication::sendSpontaneousEvent(this, &ee);

  //GLenum e = f->glGetError();
  //if (e != GL_NO_ERROR) {
  //  static bool x = true;
  //  if (x) {
  //    DebugBreak();
  //  }
  //}

}

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
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

  //Status bar
  statusBar = new QStatusBar(this);
  statusBar->setObjectName(QString::fromUtf8("statusBar"));
  setStatusBar(statusBar);
  QString message = tr("A context menu is available by right-clicking");
  statusBar->showMessage(message);

  setWindowTitle(QApplication::translate("MonoTKClass", "MonoTK", nullptr));

  QMetaObject::connectSlotsByName(this);

  QSurfaceFormat format = QSurfaceFormat::defaultFormat();
  format.setDepthBufferSize(24);   // No need for a depth buffer
  format.setSamples(4);           // Enable anti-aliasing
  format.setSwapInterval(1);

  openGLWidget = new OpenGLWidget(this);
  openGLWidget->setFormat(format);
  setCentralWidget(openGLWidget);

  //  v->setAttribute(Qt::WA_StaticContents);
//v->setMouseTracking(true);
}
MainWindow::~MainWindow() {
}


}//ns MonoTK