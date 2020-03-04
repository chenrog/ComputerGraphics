#pragma once

struct VertexData {
  float x, y, z;
  float s, t;

  VertexData(float _x, float _y, float _z, float _s, float _t)
      : x(_x), y(_y), z(_z), s(_s), t(_t) {}

  // Tests if two VertexData are equal
  bool operator==(const VertexData &other) {
    return (x == other.x) &&
           (y == other.y) &&
           (z == other.z) &&
           (s == other.s) &&
           (t == other.t);
  }
};
