#pragma once

#include <QVector>
#include <QtGui>

#include "Renderable.h"

class SceneNode {
 private:
  QVector<SceneNode*> children;
  Renderable* ren;
  QMatrix4x4 localTransform;
  QMatrix4x4 worldTransform;

 protected:
  SceneNode* parent;

 public:
  SceneNode(Renderable* ren);
  ~SceneNode();

  void setLocalTransform(const QMatrix4x4& transform) {
    this->localTransform = transform;
  }

  const QMatrix4x4 getLocalTransform() { return this->localTransform; }
  QMatrix4x4 getWorldTransform() { return this->worldTransform; }

  void addChild(SceneNode* node);

  virtual void update(const qint64 msSinceLastFrame);
  virtual void draw(const QMatrix4x4& world, const Camera& camera);
};
