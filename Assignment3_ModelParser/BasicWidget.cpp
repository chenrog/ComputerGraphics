#include "BasicWidget.h"

#include <fstream>
#include <iostream>

//////////////////////////////////////////////////////////////////////
// Publics
BasicWidget::BasicWidget(QWidget* parent)
    : QOpenGLWidget(parent),
      vbo_(QOpenGLBuffer::VertexBuffer),
      ibo_(QOpenGLBuffer::IndexBuffer) {
  setFocusPolicy(Qt::StrongFocus);
}

BasicWidget::~BasicWidget() {
  vbo_.release();
  vbo_.destroy();
  ibo_.release();
  ibo_.destroy();
  vao_.release();
  vao_.destroy();
}

//////////////////////////////////////////////////////////////////////
// Privates
QString BasicWidget::vertexShaderString() const {
  QString str =
      "#version 330\n"
      "layout(location = 0) in vec3 position;\n"
      "out vec4 vertColor;\n"
      "void main()\n"
      "{\n"
      "  gl_Position = vec4(position, 1.0);\n"
      "  vertColor = vec4(1.0f, 0.4f, 0.4f, 1.0f);\n"
      "}\n";
  return str;
}

QString BasicWidget::fragmentShaderString() const {
  QString str =
      "#version 330\n"
      "in vec4 vertColor;\n"
      "out vec4 color;\n"
      "void main()\n"
      "{\n"
      "  color = vertColor;\n"
      "}\n";
  return str;
}

void BasicWidget::createShader() {
  QOpenGLShader vert(QOpenGLShader::Vertex);
  vert.compileSourceCode(vertexShaderString());
  QOpenGLShader frag(QOpenGLShader::Fragment);
  frag.compileSourceCode(fragmentShaderString());

  bool ok = shaderProgram_.addShader(&vert);
  if (!ok) {
    qDebug() << shaderProgram_.log();
  }
  ok = shaderProgram_.addShader(&frag);
  if (!ok) {
    qDebug() << shaderProgram_.log();
  }
  ok = shaderProgram_.link();
  if (!ok) {
    qDebug() << shaderProgram_.log();
  }
}

///////////////////////////////////////////////////////////////////////
// Protected
void BasicWidget::keyReleaseEvent(QKeyEvent* keyEvent) {
  // Handle key events here.
  int key = keyEvent->key();

  if (key == Qt::Key_1) {
    qDebug() << "Render Bunny";
    load(BUNNY);
    update();
  } else if (key == Qt::Key_2) {
    qDebug() << "Render Monkey";
    load(MONKEY);
    update();
  } else if (key == Qt::Key_3) {
    qDebug() << "Render Cube";
    load("cube.obj");
    update();
  } else if (key == Qt::Key_W) {
    qDebug() << "Wireframe On/Off";
    setWireframe();
    update();
  } else if (key == Qt::Key_Q) {
    qDebug() << "Quit";
    std::exit(0);
  } else {
    qDebug() << "You Pressed an unsupported Key!";
  }
}

void BasicWidget::initializeGL() {
  makeCurrent();
  initializeOpenGLFunctions();

  QOpenGLContext* curContext = this->context();
  qDebug() << "[BasicWidget]::initializeGL() -- Context Information:";
  qDebug() << "  Context Valid: "
           << std::string(curContext->isValid() ? "true" : "false").c_str();
  qDebug() << "  GL Version Used: " << curContext->format().majorVersion()
           << "." << curContext->format().minorVersion();
  qDebug() << "  Vendor: "
           << reinterpret_cast<const char*>(glGetString(GL_VENDOR));
  qDebug() << "  Renderer: "
           << reinterpret_cast<const char*>(glGetString(GL_RENDERER));
  qDebug() << "  Version: "
           << reinterpret_cast<const char*>(glGetString(GL_VERSION));
  qDebug() << "  GLSL Version: "
           << reinterpret_cast<const char*>(
                  glGetString(GL_SHADING_LANGUAGE_VERSION));

  createShader();

  shaderProgram_.bind();
  // create the buffers
  vbo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
  vbo_.create();
  ibo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
  ibo_.create();
  vao_.create();

  // initial load for bunny as default
  load(BUNNY);

  // create the vao and bind everything into it
  vao_.bind();
  vbo_.bind();
  shaderProgram_.enableAttributeArray(0);
  shaderProgram_.setAttributeBuffer(0, GL_FLOAT, 0, 3);
  ibo_.bind();
  vao_.release();

  shaderProgram_.release();

  glViewport(0, 0, width(), height());
}

void BasicWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void BasicWidget::paintGL() {
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

  glClearColor(0.f, 0.f, 0.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  shaderProgram_.bind();
  vao_.bind();

  ObjParser* objParser = ObjParser::Instance();
  int index_count = objParser->getIndices().size();
  glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, 0);

  vao_.release();
  shaderProgram_.release();
}

void BasicWidget::setWireframe() {
  makeCurrent();
  wireframe = !wireframe;
  if (wireframe) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  } else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
}

void BasicWidget::load(std::string fileName) {
  ObjParser* objParser = ObjParser::Instance();
  objParser->parse(fileName);

  shaderProgram_.bind();
  vbo_.bind();
  vbo_.allocate(objParser->getVertices().constData(),
                objParser->getVertices().size() * sizeof(GL_FLOAT));
  ibo_.bind();
  ibo_.allocate(objParser->getIndices().constData(),
                objParser->getIndices().size() * sizeof(GL_INT));
  shaderProgram_.release();
}
