#ifndef Vector4f_H
#define Vector4f_H

#include <cmath>
#include <string>

// Vector4f performs vector operations with 4-dimensions
// The purpose of this class is primarily for 3D graphics
// applications.
struct Vector4f {
  // Note: x,y,z,w are a convention
  // x,y,z,w could be position, but also any 4-component value.
  float x, y, z, w;

  // Default conostrutcor
  // 'why default?'
  // https://stackoverflow.com/questions/20828907/the-new-keyword-default-in-c11
  Vector4f() = default;

  // The "Real" constructor we want to use.
  // This initializes the values x,y,z
  Vector4f(float a, float b, float c, float d) {
    x = a;
    y = b;
    z = c;
    w = d;
  }

  Vector4f(float a) {
    x = a;
    y = a;
    z = a;
    w = a;
  }

  // Index operator, allowing us to access the individual
  // x,y,z,w components of our vector.
  float& operator[](int i) { return ((&x)[i]); }

  // Index operator, allowing us to access the individual
  // x,y,z,w components of our vector.
  const float& operator[](int i) const { return ((&x)[i]); }

  // Multiplication Operator
  // Multiply vector by a uniform-scalar.
  Vector4f& operator*=(float s) {
    (*this)[0] *= s;
    (*this)[1] *= s;
    (*this)[2] *= s;
    (*this)[3] *= s;

    return (*this);
  }

  // Division Operator
  Vector4f& operator/=(float s) {
    (*this)[0] /= s;
    (*this)[1] /= s;
    (*this)[2] /= s;
    (*this)[3] /= s;

    return (*this);
  }

  // Addition operator
  Vector4f& operator+=(const Vector4f& v) {
    (*this)[0] += v[0];
    (*this)[1] += v[1];
    (*this)[2] += v[2];
    (*this)[3] += v[3];

    return (*this);
  }

  // Subtraction operator
  Vector4f& operator-=(const Vector4f& v) {
    (*this)[0] -= v[0];
    (*this)[1] -= v[1];
    (*this)[2] -= v[2];
    (*this)[3] -= v[3];

    return (*this);
  }

  std::string toString() {
    std::string string = "";
    string = string + "Vector4[";
    string = string + "x:" + std::to_string(x);
    string = string + ", ";
    string = string + "y:" + std::to_string(y);
    string = string + ", ";
    string = string + "z:" + std::to_string(z);
    string = string + ", ";
    string = string + "w:" + std::to_string(w);
    string = string + "]";
    return string;
  }
};

// Compute the dot product of a Vector4f
inline float Dot(const Vector4f& a, const Vector4f& b) {
  float sum = 0;

  sum += (a[0] * b[0]);
  sum += (a[1] * b[1]);
  sum += (a[2] * b[2]);
  sum += (a[3] * b[3]);

  return sum;
}

// Multiplication of a vector by a scalar values
inline Vector4f operator*(const Vector4f& v, float s) {
  Vector4f vec;

  vec[0] = v[0] * s;
  vec[1] = v[1] * s;
  vec[2] = v[2] * s;
  vec[3] = v[3] * s;

  return vec;
}

// Division of a vector by a scalar value.
inline Vector4f operator/(const Vector4f& v, float s) {
  Vector4f vec;

  vec[0] = v[0] / s;
  vec[1] = v[1] / s;
  vec[2] = v[2] / s;
  vec[3] = v[3] / s;

  return vec;
}

// Negation of a vector
// Use Case: Sometimes it is handy to apply a force in an opposite direction
inline Vector4f operator-(const Vector4f& v) {
  Vector4f vec;

  vec[0] = v[0] * -1;
  vec[1] = v[1] * -1;
  vec[2] = v[2] * -1;
  vec[3] = v[3] * -1;

  return vec;
}

// Return the magnitude of a vector
inline float Magnitude(const Vector4f& v) {
  float sum = 0;

  sum += (v[0] * v[0]);
  sum += (v[1] * v[1]);
  sum += (v[2] * v[2]);
  sum += (v[3] * v[3]);

  return sqrt(sum);
}

// alias for magnitude
inline float Length(const Vector4f& v) { return Magnitude(v); }

// Add two vectors together
inline Vector4f operator+(const Vector4f& a, const Vector4f& b) {
  Vector4f vec;

  vec[0] = a[0] + b[0];
  vec[1] = a[1] + b[1];
  vec[2] = a[2] + b[2];
  vec[3] = a[3] + b[3];

  return vec;
}

// Subtract two vectors
inline Vector4f operator-(const Vector4f& a, const Vector4f& b) {
  Vector4f vec;

  vec[0] = a[0] - b[0];
  vec[1] = a[1] - b[1];
  vec[2] = a[2] - b[2];
  vec[3] = a[3] - b[3];

  return vec;
}

// Set a vectors magnitude to 1
// Note: This is NOT generating a normal vector
inline Vector4f Normalize(const Vector4f& v) {
  float mag = Magnitude(v);
  Vector4f vec = v / mag;
  return vec;
}

// Vector Projection
// Note: This is the vector projection of 'a' onto 'b'
inline Vector4f Project(const Vector4f& a, const Vector4f& b) {
  float mag = Dot(a, (b / Magnitude(b)));
  Vector4f vec = Normalize(b) * mag;
  return vec;
}

// a x b (read: 'a crossed b')
// Produces a new vector perpendicular to a and b.
// (So long as a and b are not parallel which returns zero vector)
// Note: For a Vector4f, we can only compute a cross porduct to
//       to vectors in 3-dimensions. Simply ignore w, and set to (0,0,0,1)
//       for this vector.
inline Vector4f CrossProduct(const Vector4f& a, const Vector4f& b) {
  // TODO:
  float x = (a[1] * b[2]) - (a[2] * b[1]);
  float y = (a[2] * b[0]) - (a[0] * b[2]);
  float z = (a[0] * b[1]) - (a[1] * b[0]);
  float w = 1;
  Vector4f vec = Vector4f(x, y, z, w);
  return vec;
}

#endif
