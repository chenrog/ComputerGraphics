#pragma once

#include <QtCore>
#include <QtGui>
#include <QtOpenGL>

#include "Rotation.h"

class Renderable {
 protected:
  QMatrix4x4 modelMatrix_;
  QOpenGLShaderProgram shader_;
  QOpenGLTexture texture_;
  QOpenGLBuffer vbo_;
  QOpenGLBuffer ibo_;
  QOpenGLVertexArrayObject vao_;
  unsigned int numTris_;
  int vertexSize_;

  Rotation rotation_;

  void createShaders();

 public:
  Renderable();
  virtual ~Renderable();

  virtual void init(const QVector<QVector3D>& positions,
                    const QVector<QVector3D>& normals,
                    const QVector<QVector2D>& texCoords,
                    const QVector<unsigned int>& indexes,
                    const QString& textureFile);

  virtual void update(const qint64 msSinceLastFrame);
  virtual void draw(const QMatrix4x4& view, const QMatrix4x4& projection);

  void setModelMatrix(const QMatrix4x4& transform);
  void setRotationAxis(const QVector3D& axis);
  void setRotationSpeed(float speed);

 private:
};
