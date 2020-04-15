#pragma once

#include <QtGui>

struct VertexData {
  float x, y, z;    // position
  float xn, yn, zn; // normal
  float s, t;       // texture coordinates

  VertexData(float _x, float _y, float _z,
             float _xn, float _yn, float _zn,
             float _s, float _t)
      : x(_x), y(_y), z(_z), xn(_xn), yn(_yn), zn(_zn), s(_s), t(_t) {}

  VertexData(QVector3D position, QVector3D normal, QVector2D texture)
      : x(position.x()), y(position.y()), z(position.z()),
        xn(normal.x()), yn(normal.y()), zn(normal.z()),
        s(texture.x()), t(texture.y()) {}

  // Tests if two VertexData are equal
  bool operator==(const VertexData &other) {
    return (x == other.x) &&
           (y == other.y) &&
           (z == other.z) &&
           (xn == other.xn) &&
           (yn == other.yn) &&
           (zn == other.zn) &&
           (s == other.s) &&
           (t == other.t);
  }

  QVector3D position() { return QVector3D(x, y, z); }

  QVector3D normal() { return QVector3D(xn, yn, zn); }

  QVector3D texture() { return QVector2D(s, t); }

  static int size() { return 8; }
};

inline bool operator==(const VertexData &a, const VertexData &b) {
  return (a.x == b.x) &&
         (a.y == b.y) &&
         (a.z == b.z) &&
         (a.xn == b.xn) &&
         (a.yn == b.yn) &&
         (a.zn == b.zn) &&
         (a.s == b.s) &&
         (a.t == b.t);
}
