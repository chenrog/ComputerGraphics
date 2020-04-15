#pragma once

#include "Renderable.h"

class UnitQuad : public Renderable {
 protected:
  QVector3D lightPos;
  float sign;

 public:
  UnitQuad();
  virtual ~UnitQuad();

  // Our init method is much easier now.  We only need a texture!
  virtual void init(const QVector<VertexData>& vertices,
                    const QVector<unsigned int>& indices,
                    const QString& textureFile);
  virtual void update(const qint64 msSinceLastFrame) override;

 private:
};
