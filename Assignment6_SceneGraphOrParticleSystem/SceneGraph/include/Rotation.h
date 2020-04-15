#pragma once

#include <QtOpenGL>

class Rotation {
 protected:
  QVector3D axis;
  float speed;
  float angle;

 public:
  Rotation(const QVector3D& axis, float speed, float angle);
  virtual ~Rotation();

  virtual void update(const qint64 msSinceLastFrame);

  void setAxis(const QVector3D& axis);

  void setSpeed(const float speed);

  QMatrix4x4 toMatrix();

 private:
};
