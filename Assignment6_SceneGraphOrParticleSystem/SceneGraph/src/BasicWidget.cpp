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

  // SUN
  Sphere* sunSphere = new Sphere("./planets/sun.ppm");
  sunSphere->setRotationAxis(QVector3D(0.0, 0.0, 1.0));
  sunSphere->setRotationSpeed(0.25);

  SceneNode* sunNode = new SceneNode(sunSphere);
  QMatrix4x4 mat;
  mat.setToIdentity();
  sunNode->setTransform(mat);
  sunNode->setModelScale(QVector3D(0.5, 0.5, 0.5));
  root = sunNode;

  // MERCURY
  Sphere* mercSphere = new Sphere("./planets/mercury.ppm");
  mercSphere->setRotationAxis(QVector3D(0.0, 0.0, 1.0));
  mercSphere->setRotationSpeed(1.0);

  SceneNode* mercNode = new SceneNode(mercSphere);
  mat.setToIdentity();
  mat.translate(2, 0, 0);
  mercNode->setTransform(mat);
  mercNode->setModelScale(QVector3D(0.25, 0.25, 0.25));
  sunNode->addChild(mercNode);

  // MERCURY MOON 1
  Sphere* mercMoonSphere = new Sphere("./planets/rock.ppm");
  SceneNode* mercMoonNode = new SceneNode(mercMoonSphere);
  mat.setToIdentity();
  mat.translate(0.5, 0.5, 0);
  mercMoonNode->setTransform(mat);
  mercMoonNode->setModelScale(QVector3D(0.1, 0.1, 0.1));
  mercNode->addChild(mercMoonNode);

  // MERCURY MOON 2
  Sphere* mercMoonSphere2 = new Sphere("./planets/rock.ppm");
  SceneNode* mercMoonNode2 = new SceneNode(mercMoonSphere2);
  mat.setToIdentity();
  mat.translate(-0.5, 0, 0);
  mercMoonNode2->setTransform(mat);
  mercMoonNode2->setModelScale(QVector3D(0.1, 0.1, 0.1));
  mercNode->addChild(mercMoonNode2);

  // MERCURY MOON 3
  Sphere* mercMoonSphere3 = new Sphere("./planets/rock.ppm");
  SceneNode* mercMoonNode3 = new SceneNode(mercMoonSphere3);
  mat.setToIdentity();
  mat.translate(0.7, 0, 0);
  mercMoonNode3->setTransform(mat);
  mercMoonNode3->setModelScale(QVector3D(0.15, 0.15, 0.15));
  mercNode->addChild(mercMoonNode3);

  // EARTH
  Sphere* earthSphere = new Sphere("./planets/earth.ppm");
  earthSphere->setRotationAxis(QVector3D(0.0, 0.0, 1.0));
  earthSphere->setRotationSpeed(-0.25);

  SceneNode* earthNode = new SceneNode(earthSphere);
  mat.setToIdentity();
  mat.translate(-2, 2, 0);
  earthNode->setTransform(mat);
  earthNode->setModelScale(QVector3D(0.4, 0.4, 0.4));
  sunNode->addChild(earthNode);

  glViewport(0, 0, width(), height());
  frameTimer.start();

  // MOON
  Sphere* moonSphere = new Sphere("./planets/rock.ppm");
  SceneNode* moonNode = new SceneNode(moonSphere);
  mat.setToIdentity();
  mat.translate(-0.7, 0, 0);
  moonNode->setTransform(mat);
  moonNode->setModelScale(QVector3D(0.1, 0.1, 0.1));
  earthNode->addChild(moonNode);

  // PLANET
  Sphere* planetSphere = new Sphere("./planets/planet.ppm");
  planetSphere->setRotationAxis(QVector3D(0.0, 0.0, 1.0));
  planetSphere->setRotationSpeed(-0.05);

  SceneNode* planetNode = new SceneNode(planetSphere);
  mat.setToIdentity();
  mat.translate(0, -4, 0);
  planetNode->setTransform(mat);
  planetNode->setModelScale(QVector3D(0.7, 0.7, 0.7));
  sunNode->addChild(planetNode);

  glViewport(0, 0, width(), height());
  frameTimer.start();

  // PLANET MOON 1
  Sphere* planetMoonSphere = new Sphere("./planets/rock.ppm");
  SceneNode* planetMoonNode = new SceneNode(planetMoonSphere);
  mat.setToIdentity();
  mat.translate(-1.2, 0, 0);
  planetMoonNode->setTransform(mat);
  planetMoonNode->setModelScale(QVector3D(0.1, 0.1, 0.1));
  planetNode->addChild(planetMoonNode);

  // PLANET MOON 2
  Sphere* planetMoonSphere2 = new Sphere("./planets/rock.ppm");
  SceneNode* planetMoonNode2 = new SceneNode(planetMoonSphere2);
  mat.setToIdentity();
  mat.translate(1.2, 0, 0);
  planetMoonNode2->setTransform(mat);
  planetMoonNode2->setModelScale(QVector3D(0.1, 0.1, 0.1));
  planetNode->addChild(planetMoonNode2);
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
