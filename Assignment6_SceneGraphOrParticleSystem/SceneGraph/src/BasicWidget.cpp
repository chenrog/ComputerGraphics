#include "BasicWidget.h"

//////////////////////////////////////////////////////////////////////
// Publics
BasicWidget::BasicWidget(QWidget* parent)
    : QOpenGLWidget(parent), logger(this) {
  setFocusPolicy(Qt::StrongFocus);
  camera.setPosition(QVector3D(0.0, 0.5, -5.0));
  camera.setLookAt(QVector3D(0.0, 0.5, 0.0));
  world.setToIdentity();
}

BasicWidget::~BasicWidget() { delete root; }

//////////////////////////////////////////////////////////////////////
// Privates

///////////////////////////////////////////////////////////////////////
// Protected
void BasicWidget::keyReleaseEvent(QKeyEvent* keyEvent) {
  // Handle key events here.
  int key = keyEvent->key();

  if (key == Qt::Key_W) {
    qDebug() << "Wireframe On/Off";
    setWireframe();
    update();
  } else if (keyEvent->key() == Qt::Key_R) {
    camera.setPosition(QVector3D(0.0, 0.5, -5.0));
    camera.setLookAt(QVector3D(0.0, 0.5, 0.0));
    update();
  } else if (key == Qt::Key_Q) {
    qDebug() << "Quit";
    std::exit(0);
  } else {
    qDebug() << "You Pressed an unsupported Key!";
  }
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

void BasicWidget::mousePressEvent(QMouseEvent* mouseEvent) {
  if (mouseEvent->button() == Qt::LeftButton) {
    mouseAction = Rotate;
  } else if (mouseEvent->button() == Qt::RightButton) {
    mouseAction = Zoom;
  }
  lastMouseLoc = mouseEvent->pos();
}

void BasicWidget::mouseMoveEvent(QMouseEvent* mouseEvent) {
  if (mouseAction == NoAction) {
    return;
  }
  QPoint delta = mouseEvent->pos() - lastMouseLoc;
  lastMouseLoc = mouseEvent->pos();
  if (mouseAction == Rotate) {
    float angle = qDegreesToRadians(0.5f * delta.x());
    camera.rotateY(angle);
  } else if (mouseAction == Zoom) {
    camera.translateCamera(camera.gazeVector() * 0.03f * -delta.y());
  }
  update();
}

void BasicWidget::mouseReleaseEvent(QMouseEvent* mouseEvent) {
  mouseAction = NoAction;
}

void BasicWidget::initializeGL() {
  makeCurrent();
  initializeOpenGLFunctions();

  Sphere* sunSphere = new Sphere("./planets/sun.ppm");
  SceneNode* sunNode = new SceneNode(sunSphere);
  QMatrix4x4 mat;
  mat.setToIdentity();
  sunNode->setTransform(mat);

  root = sunNode;

  glViewport(0, 0, width(), height());
  frameTimer.start();
}

void BasicWidget::resizeGL(int w, int h) {
  if (!logger.isLogging()) {
    logger.initialize();
    // Setup the logger for real-time messaging
    connect(&logger, &QOpenGLDebugLogger::messageLogged, [=]() {
      const QList<QOpenGLDebugMessage> messages = logger.loggedMessages();
      for (auto msg : messages) {
        qDebug() << msg;
      }
    });
    logger.startLogging();
  }
  glViewport(0, 0, w, h);

  camera.setPerspective(70.f, (float)w / (float)h, 0.001, 1000.0);
  glViewport(0, 0, w, h);
}

void BasicWidget::paintGL() {
  qint64 msSinceRestart = frameTimer.restart();
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

  glClearColor(0.f, 0.f, 0.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  root->update(msSinceRestart);
  root->draw(world, camera);
  update();
}
