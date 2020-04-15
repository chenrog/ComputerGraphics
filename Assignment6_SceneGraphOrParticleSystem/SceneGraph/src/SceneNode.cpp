#include "SceneNode.h"

SceneNode::SceneNode(Renderable* ren) {
  this->ren = ren;
  this->parent = NULL;
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
  if (parent) {
    worldTransform = parent->worldTransform * Transform;
  } else {
    worldTransform = Transform;
  }

  for (unsigned int i = 0; i < children.size(); ++i) {
    children[i]->update(msSinceLastFrame);
  }
}

void SceneNode::draw(const QMatrix4x4& world, const Camera& camera) {
  ren->draw(world, camera);
}
