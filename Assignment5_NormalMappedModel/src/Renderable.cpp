#include "Renderable.h"

#include <QtGui>
#include <QtOpenGL>

Renderable::Renderable()
    : vbo(QOpenGLBuffer::VertexBuffer),
      ibo(QOpenGLBuffer::IndexBuffer),
      texture(QOpenGLTexture::Target2D),
      elementCount(0),
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

void Renderable::init(const QVector<VertexData>& vertices,
                      const QVector<unsigned int>& indices,
                      const QString& textureFile) {
  // Set our model matrix to identity
  modelMatrix.setToIdentity();
  // Load our texture.
  texture.setData(QImage(textureFile));
  // set our number of triangles.
  elementCount = indices.size();

  // num verts (used to size our vbo)
  int numVerts = vertices.size();
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
    data[i * vertexSize + 0] = vertices.at(i).x;
    data[i * vertexSize + 1] = vertices.at(i).y;
    data[i * vertexSize + 2] = vertices.at(i).z;
    data[i * vertexSize + 3] = vertices.at(i).s;
    data[i * vertexSize + 4] = vertices.at(i).t;
  }

  vbo.allocate(data, numVBOEntries * sizeof(float));
  delete[] data;

  // Create our index buffer
  ibo.create();
  ibo.bind();
  ibo.setUsagePattern(QOpenGLBuffer::StaticDraw);
  // create a temporary array for our indexes
  unsigned int* idxAr = new unsigned int[indices.size()];
  for (int i = 0; i < indices.size(); ++i) {
    idxAr[i] = indices.at(i);
  }
  ibo.allocate(idxAr, indices.size() * sizeof(unsigned int));
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

void Renderable::draw(const QMatrix4x4& world, const Camera& camera) {
  // incorporate a real world transform if want it.
  QMatrix4x4 modelMat = world * modelMatrix * rotation.toMatrix();

  // Make sure our state is what we want
  shader.bind();

  // Set our matrix uniforms!
  QMatrix4x4 id;
  id.setToIdentity();
  shader.setUniformValue("modelMatrix", modelMat);
  shader.setUniformValue("viewMatrix", camera.getViewMatrix());
  shader.setUniformValue("projectionMatrix", camera.getProjectionMatrix());

  vao.bind();
  texture.bind();
  glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, 0);
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
