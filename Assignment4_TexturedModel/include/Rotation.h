#pragma once

#include <QtOpenGL>

class Rotation {
 protected:
  QVector3D axis_;
  float speed_;
  float angle_;

 public:
  Rotation(const QVector3D& axis, float speed, float angle);
  virtual ~Rotation();

  virtual void update(const qint64 msSinceLastFrame);

  void setAxis(const QVector3D& axis);

  void setSpeed(float speed);

  void setAngle(float angle);

  QMatrix4x4 getMatrix();

 private:
};
