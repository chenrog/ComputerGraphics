#include "Rotation.h"

Rotation::Rotation(const QVector3D& axis, float speed, float angle) {
  axis_ = axis;
  speed_ = speed;
  angle_ = angle;
}

Rotation::~Rotation() {}

void Rotation::update(const qint64 msSinceLastFrame) {
  // For this lab, we want our polygon to rotate.
  float sec = msSinceLastFrame / 1000.0f;
  float anglePart = sec * speed_ * 360.f;
  angle_ += anglePart;
  while (angle_ >= 360.0) {
    angle_ -= 360.0;
  }
}

void Rotation::setAxis(const QVector3D& axis) { axis_ = axis; }

void Rotation::setSpeed(float speed) { speed_ = speed; }

QMatrix4x4 Rotation::getMatrix() {
  QMatrix4x4 matrix;
  matrix.setToIdentity();
  matrix.rotate(angle_, axis_);
  return matrix;
}
