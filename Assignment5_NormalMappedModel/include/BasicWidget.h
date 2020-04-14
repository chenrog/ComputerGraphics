#pragma once

#include <QtGui>
#include <QtOpenGL>
#include <QtWidgets>

#include "ObjParser.h"
#include "Renderable.h"
#include "VertexData.h"

/**
 * This is just a basic OpenGL widget that will allow a change of background
 * color.
 */
class BasicWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

 private:
  // camera, abstract maybe
  QMatrix4x4 model;
  QMatrix4x4 view;
  QMatrix4x4 projection;

  QElapsedTimer frameTimer;
  QVector<Renderable*> renderables;
  QOpenGLDebugLogger logger;

  bool wireframe = false;

 protected:
  // Required interaction overrides
  void keyReleaseEvent(QKeyEvent* keyEvent) override;

  // Required overrides form QOpenGLWidget
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void setWireframe();

 public:
  BasicWidget(QWidget* parent = nullptr);
  virtual ~BasicWidget();

  // Make sure we have some size that makes sense.
  QSize sizeHint() const { return QSize(800, 600); }
  void load(QString);
};
