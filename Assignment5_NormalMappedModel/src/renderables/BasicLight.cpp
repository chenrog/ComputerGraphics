#include "BasicLight.h"

BasicLight::BasicLight() : lightPos(0.0f, 0.0f, -6.0f), sign(1.0f) {}

BasicLight::~BasicLight() {}

void BasicLight::init(const QVector<VertexData>& vertices,
                    const QVector<unsigned int>& indices,
                    const QString& textureFile) {
  Renderable::init(vertices, indices, textureFile);
}

void BasicLight::update(const qint64 msSinceLastFrame) {
  // This is where we want to maintain our light.
  float secs = (float)msSinceLastFrame / 1000.0f;
  float angle = (secs * (2.0f / 3.0f)) * 180.0f;

  // Rotate our light around the scene
  QMatrix4x4 rot;
  rot.setToIdentity();
  rot.rotate(angle, 0.0, 1.0, 0.0);

  QVector3D rotatingLightPosition = rot * lightPos;
  lightPos = rotatingLightPosition;

  // TODO:  Understand how the light gets initialized/setup.
  shader.bind();
  shader.setUniformValue("pointLights[0].color", 0.996f, 0.5f, 0.614f);
  shader.setUniformValue("pointLights[0].position", rotatingLightPosition);
  shader.setUniformValue("pointLights[0].ambientIntensity", 1.5f);
  shader.setUniformValue("pointLights[0].specularStrength", 1.5f);
  shader.setUniformValue("pointLights[0].constant", 0.05f);
  shader.setUniformValue("pointLights[0].linear", 0.10f);
  shader.setUniformValue("pointLights[0].quadratic", 0.064f);

  QVector3D innerLightPosition = QVector3D(0.0f, 0.0f, 0.0f);
  shader.setUniformValue("pointLights[1].color", 1.0, 1.0f, 1.0f);
  shader.setUniformValue("pointLights[1].position", innerLightPosition);
  shader.setUniformValue("pointLights[1].ambientIntensity", 10.0f);
  shader.setUniformValue("pointLights[1].specularStrength", 0.5f);
  shader.setUniformValue("pointLights[1].constant", 0.50f);
  shader.setUniformValue("pointLights[1].linear", 5.00f);
  shader.setUniformValue("pointLights[1].quadratic", 2.032f);

  shader.release();
}
