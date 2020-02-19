#pragma once

#include <QtGui>
#include <QtOpenGL>
#include <QtWidgets>
#include "ObjParser.h"

/**
 * This is just a basic OpenGL widget that will allow a change of background
 * color.
 */
class BasicWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

 private:
  QString vertexShaderString() const;
  QString fragmentShaderString() const;
  void createShader();
  QOpenGLVertexArrayObject vao_;

 protected:
  // Required interaction overrides
  void keyReleaseEvent(QKeyEvent* keyEvent) override;

  // Required overrides form QOpenGLWidget
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  void setWireframe();
  void load(std::string fileName);

  std::string modelName;
  const std::string BUNNY = "bunny_centered.obj";
  const std::string MONKEY = "monkey_centered.obj";
  bool wireframe = true;

  QOpenGLBuffer vbo_;
  QOpenGLBuffer ibo_;
  QOpenGLShaderProgram shaderProgram_;

 public:
  BasicWidget(QWidget* parent = nullptr);
  virtual ~BasicWidget();

  // Make sure we have some size that makes sense.
  QSize sizeHint() const { return QSize(800, 600); }
};
