#include "Renderable.h"

#include <QtGui>
#include <QtOpenGL>

Renderable::Renderable()
    : vbo(QOpenGLBuffer::VertexBuffer),
      ibo(QOpenGLBuffer::IndexBuffer),
      texture(QOpenGLTexture::Target2D),
      numTris(0),
      vertexSize(0),
      rotation(QVector3D(0.0, 0.0, 1.0), 0.25, 0.0) {}

Renderable::~Renderable() {
  if (texture.isCreated()) {
    texture.destroy();
  }
  if (vbo.isCreated()) {
    vbo.destroy();
  }
  if (ibo.isCreated()) {
    ibo.destroy();
  }
  if (vao.isCreated()) {
    vao.destroy();
  }
}

void Renderable::createShaders() {
  QString vertexFilename = "./shaders/vert.glsl";
  bool ok =
      shader.addShaderFromSourceFile(QOpenGLShader::Vertex, vertexFilename);
  if (!ok) {
    qDebug() << shader.log();
  }
  QString fragmentFilename = "./shaders/frag.glsl";
  ok =
      shader.addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentFilename);
  if (!ok) {
    qDebug() << shader.log();
  }
  ok = shader.link();
  if (!ok) {
    qDebug() << shader.log();
  }
}

void Renderable::init(const QVector<QVector3D>& positions,
                      const QVector<QVector3D>& normals,
                      const QVector<QVector2D>& texCoords,
                      const QVector<unsigned int>& indexes,
                      const QString& textureFile) {
  // NOTE:  We do not currently do anything with normals -- we just
  // have it here for a later implementation!
  // We need to make sure our sizes all work out ok.
  if (positions.size() != texCoords.size() ||
      positions.size() != normals.size()) {
    qDebug() << "[Renderable]::init() -- positions size mismatch with "
                "normals/texture coordinates";
    return;
  }

  // Set our model matrix to identity
  modelMatrix.setToIdentity();
  // Load our texture.
  texture.setData(QImage(textureFile));

  // set our number of trianges.
  numTris = indexes.size() / 3;

  // num verts (used to size our vbo)
  int numVerts = positions.size();
  vertexSize = 3 + 2;  // Position + texCoord
  int numVBOEntries = numVerts * vertexSize;

  // Setup our shader.
  createShaders();

  // Now we can set up our buffers.
  // The VBO is created -- now we must create our VAO
  vao.create();
  vao.bind();
  vbo.create();
  vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
  vbo.bind();
  // Create a temporary data array
  float* data = new float[numVBOEntries];
  for (int i = 0; i < numVerts; ++i) {
    data[i * vertexSize + 0] = positions.at(i).x();
    data[i * vertexSize + 1] = positions.at(i).y();
    data[i * vertexSize + 2] = positions.at(i).z();
    data[i * vertexSize + 3] = texCoords.at(i).x();
    data[i * vertexSize + 4] = texCoords.at(i).y();
  }
  vbo.allocate(data, numVBOEntries * sizeof(float));
  delete[] data;

  // Create our index buffer
  ibo.create();
  ibo.bind();
  ibo.setUsagePattern(QOpenGLBuffer::StaticDraw);
  // create a temporary array for our indexes
  unsigned int* idxAr = new unsigned int[indexes.size()];
  for (int i = 0; i < indexes.size(); ++i) {
    idxAr[i] = indexes.at(i);
  }
  ibo.allocate(idxAr, indexes.size() * sizeof(unsigned int));
  delete[] idxAr;

  // Make sure we setup our shader inputs properly
  shader.enableAttributeArray(0);
  shader.setAttributeBuffer(0, GL_FLOAT, 0, 3, vertexSize * sizeof(float));
  shader.enableAttributeArray(1);
  shader.setAttributeBuffer(1, GL_FLOAT, 3 * sizeof(float), 2,
                            vertexSize * sizeof(float));

  // Release our vao and THEN release our buffers.
  vao.release();
  vbo.release();
  ibo.release();
}

void Renderable::update(const qint64 msSinceLastFrame) {
  rotation.update(msSinceLastFrame);
}

void Renderable::draw(const QMatrix4x4& view, const QMatrix4x4& projection) {
  // Create our model matrix.
  QMatrix4x4 rotMatrix = rotation.toMatrix();

  QMatrix4x4 modelMat = modelMatrix * rotMatrix;
  // Make sure our state is what we want
  shader.bind();
  // Set our matrix uniforms!
  QMatrix4x4 id;
  id.setToIdentity();
  shader.setUniformValue("modelMatrix", modelMat);
  shader.setUniformValue("viewMatrix", view);
  shader.setUniformValue("projectionMatrix", projection);

  vao.bind();
  texture.bind();
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  texture.release();
  vao.release();
  shader.release();
}

void Renderable::setModelMatrix(const QMatrix4x4& transform) {
  modelMatrix = transform;
}

void Renderable::setRotationAxis(const QVector3D& axis) {
  rotation.setAxis(axis);
}

void Renderable::setRotationSpeed(const float speed) {
  rotation.setSpeed(speed);
}
