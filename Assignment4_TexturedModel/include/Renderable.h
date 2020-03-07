#pragma once

#include <QtCore>
#include <QtGui>
#include <QtOpenGL>

#include "Rotation.h"

class Renderable {
 protected:
  QMatrix4x4 modelMatrix;
  QOpenGLShaderProgram shader;
  QOpenGLTexture texture;
  QOpenGLBuffer vbo;
  QOpenGLBuffer ibo;
  QOpenGLVertexArrayObject vao;
  unsigned int numTris;
  int vertexSize;
  Rotation rotation;

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
