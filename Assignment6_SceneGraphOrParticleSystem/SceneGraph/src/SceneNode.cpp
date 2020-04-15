#include "SceneNode.h"

SceneNode::SceneNode(Renderable* ren) {
  this->ren = ren;
  this->parent = NULL;
  this->modelScale = QVector3D(1, 1, 1);
}

SceneNode::~SceneNode() {
  for (unsigned int i = 0; i < children.size(); ++i) {
    delete children[i];
  }
}

void SceneNode::addChild(SceneNode* node) {
  children.push_back(node);
  node->parent = this;
}

void SceneNode::update(const qint64 msSinceLastFrame) {
  float secs = (float)msSinceLastFrame / 1000.0f;
  float angle = (secs * (1.0 / 4.0)) * 180.0f;
  transform.rotate(-angle, 0.0, 0.0, 1.0);

  ren->update(msSinceLastFrame);

  if (parent) {
    worldTransform = parent->worldTransform * transform;
  } else {
    worldTransform = transform;
  }

  for (unsigned int i = 0; i < children.size(); ++i) {
    children[i]->update(msSinceLastFrame);
  }
}

void SceneNode::draw(const QMatrix4x4& world, const Camera& camera) {
  QMatrix4x4 scaledTransform = worldTransform;
  scaledTransform.scale(modelScale);

  ren->setModelMatrix(scaledTransform);
  ren->draw(world, camera);

  for (unsigned int i = 0; i < children.size(); ++i) {
    children[i]->draw(world, camera);
  }
}
