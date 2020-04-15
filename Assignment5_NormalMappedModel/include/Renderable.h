#pragma once

#include <QtCore>
#include <QtGui>
#include <QtOpenGL>

#include "Camera.h"
#include "Rotation.h"
#include "VertexData.h"

class Renderable {
 protected:
  QMatrix4x4 modelMatrix;
  QOpenGLShaderProgram shader;
  QOpenGLTexture texture;
  QOpenGLBuffer vbo;
  QOpenGLBuffer ibo;
  QOpenGLVertexArrayObject vao;
  unsigned int elementCount;
  int vertexSize;
  Rotation rotation;

  void createShaders();

 public:
  Renderable();
  virtual ~Renderable();

  virtual void init(const QVector<VertexData>& vertices,
                    const QVector<unsigned int>& indices,
                    const QString& textureFile);

  virtual void update(const qint64 msSinceLastFrame);

  virtual void draw(const QMatrix4x4& world, const Camera& camera);

  void setModelMatrix(const QMatrix4x4& transform);
  void setRotationAxis(const QVector3D& axis);
  void setRotationSpeed(float speed);

 private:
};
