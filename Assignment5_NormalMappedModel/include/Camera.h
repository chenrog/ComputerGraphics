#pragma once

#include <QtGui/QMatrix4x4>
#include <QtGui/QVector3D>
#include <QtMath>

class Camera {
 protected:
  QVector3D position;
  QVector3D lookAt;
  QVector3D up;
  QMatrix4x4 projection;

 public:
  Camera();
  virtual ~Camera();

  // Manipulate our Camera
  void setPerspective(float fov, float aspect, float near, float far);

  // Move our position.
  void setPosition(const QVector3D& position);
  QVector3D getPosition() const;
  void translateCamera(const QVector3D& delta);

  // Rotate position
  void rotateY(const float angle);

  // Move our gaze
  void setGazeVector(const QVector3D& gaze);
  QVector3D gazeVector() const;
  QVector3D upVector() const;
  void setLookAt(const QVector3D& lookAt);
  void translateLookAt(const QVector3D& delta);
  QVector3D getLookAt() const;

  // Get our camera matrix
  QMatrix4x4 getViewMatrix() const;
  QMatrix4x4 getProjectionMatrix() const;

 private:
};
