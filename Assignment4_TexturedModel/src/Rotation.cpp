#include "Rotation.h"

Rotation::Rotation(const QVector3D& axis, float speed, float angle) {
  this->axis = axis;
  this->speed = speed;
  this->angle = angle;
}

Rotation::~Rotation() {}

void Rotation::update(const qint64 msSinceLastFrame) {
  // For this lab, we want our polygon to rotate.
  float sec = msSinceLastFrame / 1000.0f;
  float anglePart = sec * this->speed * 360.f;
  this->angle += anglePart;
  while (this->angle >= 360.0) {
    this->angle -= 360.0;
  }
}

void Rotation::setAxis(const QVector3D& axis) { this->axis = axis; }

void Rotation::setSpeed(float speed) { this->speed = speed; }

QMatrix4x4 Rotation::toMatrix() {
  QMatrix4x4 matrix;
  matrix.setToIdentity();
  matrix.rotate(this->angle, this->axis);
  return matrix;
}
