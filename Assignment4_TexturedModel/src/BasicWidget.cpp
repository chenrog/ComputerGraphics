#include "BasicWidget.h"

//////////////////////////////////////////////////////////////////////
// Publics
BasicWidget::BasicWidget(QWidget* parent)
    : QOpenGLWidget(parent), logger(this) {
  setFocusPolicy(Qt::StrongFocus);
}

BasicWidget::~BasicWidget() {
  for (auto renderable : renderables) {
    delete renderable;
  }
  renderables.clear();
}

//////////////////////////////////////////////////////////////////////
// Privates

///////////////////////////////////////////////////////////////////////
// Protected
void BasicWidget::keyReleaseEvent(QKeyEvent* keyEvent) {
  // Handle key events here.
  int key = keyEvent->key();

  if (key == Qt::Key_Left) {
    qDebug() << "Left Arrow Pressed";
    update();
  } else if (key == Qt::Key_Right) {
    qDebug() << "Right Arrow Pressed";
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

  QString texFile = "./cat3.ppm";
  QVector<QVector3D> pos;
  QVector<QVector3D> norm;
  QVector<QVector2D> texCoord;
  QVector<unsigned int> idx;
  // left cat
  pos << QVector3D(-0.5, -0.5, 0.0);
  pos << QVector3D(0.5, -0.5, 0.0);
  pos << QVector3D(-0.5, 0.5, 0.0);
  pos << QVector3D(0.5, 0.5, 0.0);
  // right cat
  // We don't actually use the normals right now, but this will be useful later!
  norm << QVector3D(0.0, 0.0, 1.0);
  norm << QVector3D(0.0, 0.0, 1.0);
  norm << QVector3D(0.0, 0.0, 1.0);
  norm << QVector3D(0.0, 0.0, 1.0);
  // TODO:  Make sure to add texture coordinates to pass into the initialization
  // of our renderable
  texCoord << QVector2D(0.0, 1.0);
  texCoord << QVector2D(1.0, 1.0);
  texCoord << QVector2D(0.0, 0.0);
  texCoord << QVector2D(1.0, 0.0);

  idx << 0 << 1 << 2 << 2 << 1 << 3;

  Renderable* ren = new Renderable();
  ren->init(pos, norm, texCoord, idx, texFile);
  QMatrix4x4 ren_position;
  ren_position.setToIdentity();
  ren_position.translate(-1.0, 0.0, 0.0);
  ren->setModelMatrix(ren_position);
  ren->setRotationSpeed(0.2);
  renderables.push_back(ren);

  Renderable* ren2 = new Renderable();
  ren2->init(pos, norm, texCoord, idx, texFile);
  ren_position.setToIdentity();
  ren_position.translate(1.0, 0.0, 0.0);
  ren2->setModelMatrix(ren_position);
  ren2->setRotationAxis(QVector3D(0.0, 1.0, 0.0));
  ren2->setRotationSpeed(1.2);
  renderables.push_back(ren2);

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
  view.setToIdentity();
  view.lookAt(QVector3D(0.0f, 0.0f, 2.0f), QVector3D(0.0f, 0.0f, 0.0f),
              QVector3D(0.0f, 1.0f, 0.0f));
  projection.setToIdentity();
  projection.perspective(70.f, (float)w / (float)h, 0.001, 1000.0);
  glViewport(0, 0, w, h);
}

void BasicWidget::paintGL() {
  qint64 msSinceRestart = frameTimer.restart();
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

  glClearColor(0.f, 0.f, 0.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for (auto renderable : renderables) {
    renderable->update(msSinceRestart);
    renderable->draw(view, projection);
  }
  update();
}
