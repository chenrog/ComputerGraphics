#pragma once

#include <QtGui>

struct VertexData {
  float x, y, z;
  float s, t;

  VertexData(float _x, float _y, float _z, float _s, float _t)
      : x(_x), y(_y), z(_z), s(_s), t(_t) {}

  VertexData(QVector3D position, QVector2D texture)
      : x(position.x()),
        y(position.y()),
        z(position.z()),
        s(texture.x()),
        t(texture.y()) {}

  // Tests if two VertexData are equal
  bool operator==(const VertexData &other) {
    return (x == other.x) &&
           (y == other.y) &&
           (z == other.z) &&
           (s == other.s) &&
           (t == other.t);
  }

  QVector3D position() { return QVector3D(x, y, z); }

  QVector3D texture() { return QVector2D(s, t); }
};
