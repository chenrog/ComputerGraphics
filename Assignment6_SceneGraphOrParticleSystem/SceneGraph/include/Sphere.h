#pragma once
/** @file Sphere.h
 *  @brief Draw a simple sphere primitive.
 *
 *  Draws a simple sphere primitive, that is derived
 *  from the Object class.
 *
 *  @author Mike
 *  @bug No known bugs.
 */
#include <QtGui>
#include <cmath>

#include "Renderable.h"
#include "VertexData.h"

class Sphere : public Renderable {
 public:
  // Constructor for the Sphere
  Sphere(QString textureFile);
  // The intialization routine for this object.
  virtual void init();

  // Getters for our data.
  QVector<VertexData> getVertices() { return this->vertices; }
  // QVector<QVector3D> positions() const { return positions_; }
  // QVector<QVector3D> normals() const { return normals_; }
  // QVector<QVector2D> texCoords() const { return textureCoords_; }
  QVector<unsigned int> getIndexes() { return index_; }

 private:
  QVector<VertexData> vertices;
  // QVector<QVector3D> positions_;
  // QVector<QVector3D> normals_;
  // QVector<QVector2D> textureCoords_;
  QVector<unsigned int> index_;
};
