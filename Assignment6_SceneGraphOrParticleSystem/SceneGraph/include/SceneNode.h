#pragma once

#include <QVector>
#include <QtGui>

#include "Renderable.h"

class SceneNode {
 private:
  QVector<SceneNode*> children;
  Renderable* ren;
  QMatrix4x4 transform;
  QMatrix4x4 worldTransform;
  QVector3D modelScale;

 protected:
  SceneNode* parent;

 public:
  SceneNode(Renderable* ren);
  ~SceneNode();

  void setTransform(const QMatrix4x4& transform) {
    this->transform = transform;
  }

  const QMatrix4x4 getTransform() { return this->transform; }
  QMatrix4x4 getWorldTransform() { return this->worldTransform; }

  void setModelScale(QVector3D scale) { modelScale = scale; }
  QVector3D getModelScale() const { return this->modelScale; }

  void addChild(SceneNode* node);

  virtual void update(const qint64 msSinceLastFrame);
  virtual void draw(const QMatrix4x4& world, const Camera& camera);
};
