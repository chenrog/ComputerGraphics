#include "Camera.h"

Camera::Camera()
    : position(0.0, 0.0, 0.0), lookAt(0.0, 0.0, 0.0), up(0.0, 1.0, 0.0) {
  projection.setToIdentity();
}

Camera::~Camera() {}

void Camera::setPerspective(float fov, float aspect, float near, float far) {
  projection.setToIdentity();
  projection.perspective(fov, aspect, near, far);
}

void Camera::setPosition(const QVector3D& position) {
  this->position = position;
}

QVector3D Camera::getPosition() const { return position; }

void Camera::translateCamera(const QVector3D& delta) { position += delta; }

void Camera::rotateY(const float angle) {
  position -= lookAt;
  float x = position.x();
  float z = position.z();
  position.setX((x * qCos(angle)) - (z * qSin(angle)));
  position.setZ((z * qCos(angle)) + (x * qSin(angle)));
  position += lookAt;
}

void Camera::setGazeVector(const QVector3D& gaze) {
  lookAt = gaze + position;
  lookAt.normalize();
}

QVector3D Camera::gazeVector() const {
  QVector3D gaze = lookAt - position;
  gaze.normalize();
  return gaze;
}

QVector3D Camera::getLookAt() const { return lookAt; }

QVector3D Camera::upVector() const { return up; }

void Camera::setLookAt(const QVector3D& lookAt) { this->lookAt = lookAt; }

void Camera::translateLookAt(const QVector3D& delta) { lookAt += delta; }

QMatrix4x4 Camera::getViewMatrix() const {
  QMatrix4x4 ret;
  ret.setToIdentity();
  ret.lookAt(position, lookAt, up);
  return ret;
}

QMatrix4x4 Camera::getProjectionMatrix() const { return projection; }
