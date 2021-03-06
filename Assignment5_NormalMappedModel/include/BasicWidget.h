#pragma once

#include <QtGui>
#include <QtOpenGL>
#include <QtWidgets>

#include "BasicLight.h"
#include "Camera.h"
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
  QMatrix4x4 world;
  Camera camera;

  QElapsedTimer frameTimer;
  QVector<Renderable*> renderables;
  QOpenGLDebugLogger logger;

  enum MouseControl { NoAction = 0, Rotate, Zoom };
  QPoint lastMouseLoc;
  MouseControl mouseAction;

  bool wireframe = false;

 protected:
  // Required interaction overrides
  void keyReleaseEvent(QKeyEvent* keyEvent) override;
  void mousePressEvent(QMouseEvent* mouseEvent) override;
  void mouseMoveEvent(QMouseEvent* mouseEvent) override;
  void mouseReleaseEvent(QMouseEvent* mouseEvent) override;

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
