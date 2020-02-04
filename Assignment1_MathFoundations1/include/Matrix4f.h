// High level design note
// Our matrix should match the behavior of the glm library.
#ifndef MATRIX4F_H
#define MATRIX4F_H

#include <cmath>

// We need to Vector4f header in order to multiply a matrix
// by a vector.
#include "Vector4f.h"

// Matrix 4f represents 4x4 matrices in Math
struct Matrix4f{
private:
    float n[4][4];  // Store each value of the matrix

public:
    Matrix4f() = default;

    // Matrix constructor with 9 scalar values.
    // ROW MAJOR
    Matrix4f( float n00, float n01, float n02, float n03,
              float n10, float n11, float n12, float n13,
              float n20, float n21, float n22, float n23,
              float n30, float n31, float n32, float n33){

        n[0][0] = n00; n[0][1] = n01; n[0][2] = n02; n[0][3] = n03;
        n[1][0] = n10; n[1][1] = n11; n[1][2] = n12; n[1][3] = n13;
        n[2][0] = n20; n[2][1] = n21; n[2][2] = n22; n[2][3] = n23;
        n[3][0] = n30; n[3][1] = n31; n[3][2] = n32; n[3][3] = n33;
    }

    Matrix4f(float a) {
      n[0][0] = a; n[0][1] = 0.0f; n[0][2] = 0.0f; n[0][3] = 0.0f;
      n[1][0] = 0.0f; n[1][1] = a; n[1][2] = 0.0f; n[1][3] = 0.0f;
      n[2][0] = 0.0f; n[2][1] = 0.0f; n[2][2] = a; n[2][3] = 0.0f;
      n[3][0] = 0.0f; n[3][1] = 0.0f; n[3][2] = 0.0f; n[3][3] = a;
    }

    // Matrix constructor from four vectors.
    // Note: 'd' will almost always be 0,0,0,1
    Matrix4f(const Vector4f& a, const Vector4f& b, const Vector4f& c, const Vector4f& d){
      n[0][0] = a.x; n[0][1] = a.y; n[0][2] = a.z; n[0][3] = a.w;
      n[1][0] = b.x; n[1][1] = b.y; n[1][2] = b.z; n[1][3] = b.w;
      n[2][0] = c.x; n[2][1] = c.y; n[2][2] = c.z; n[2][3] = c.w;
      n[3][0] = d.x; n[3][1] = d.y; n[3][2] = d.z; n[3][3] = d.w;
    }

    // Makes the matrix an identity matrix
    void identity() {
      n[0][0] = 1.0f; n[0][1] = 0.0f; n[0][2] = 0.0f; n[0][3] = 0.0f;
      n[1][0] = 0.0f; n[1][1] = 1.0f; n[1][2] = 0.0f; n[1][3] = 0.0f;
      n[2][0] = 0.0f; n[2][1] = 0.0f; n[2][2] = 1.0f; n[2][3] = 0.0f;
      n[3][0] = 0.0f; n[3][1] = 0.0f; n[3][2] = 0.0f; n[3][3] = 1.0f;
    }

    // Index operator with two dimensions
    // Example: M(1,1) returns row 1 and column 1 of matrix M.
    float& operator ()(int i, int j){
      return (n[j][i]);
    }

    // Index operator with two dimensions
    // Example: M(1,1) returns row 1 and column 1 of matrix M.
    const float& operator ()(int i, int j) const{
      return (n[j][i]);
    }

    // Return a single  vector from the matrix (row or columnn major? hmm).
    Vector4f& operator [](int j){
      return (*reinterpret_cast<Vector4f *>(n[j]));
    }

    // Return a single  vector from the matrix (row or columnn major? hmm).
    const Vector4f& operator [](int j) const{
      return (*reinterpret_cast<const Vector4f *>(n[j]));
    }

    Vector4f col(int j) {
      float a = (*this)[0][j];
      float b = (*this)[1][j];
      float c = (*this)[2][j];
      float d = (*this)[3][j];
      return Vector4f(a, b, c, d);
    }

    const Vector4f col(int j) const {
      float a = (*this)[0][j];
      float b = (*this)[1][j];
      float c = (*this)[2][j];
      float d = (*this)[3][j];
      return Vector4f(a, b, c, d);
    }

    // Make a matrix rotate about various axis
    Matrix4f MakeRotationX(float t);
    Matrix4f MakeRotationY(float t);
    Matrix4f MakeRotationZ(float t);
    Matrix4f MakeScale(float sx,float sy, float sz);
};

// Matrix multiply by a vector

Vector4f operator*(const Matrix4f& M, const Vector4f& v) {
  float x = Dot(M[0], v);
  float y = Dot(M[1], v);
  float z = Dot(M[2], v);
  float w = Dot(M[3], v);

  Vector4f vec = Vector4f(x, y, z, w);
  return vec;
}

// Matrix Multiplication
Matrix4f operator *(const Matrix4f& A, const Matrix4f& B) {
  // TODO:
  float a = Dot(A[0], B.col(0));
  float b = Dot(A[0], B.col(1));
  float c = Dot(A[0], B.col(2));
  float d = Dot(A[0], B.col(3));
  Vector4f v(a, b, c, d);

  float a1 = Dot(A[1], B.col(0));
  float b1 = Dot(A[1], B.col(1));
  float c1 = Dot(A[1], B.col(2));
  float d1 = Dot(A[1], B.col(3));
  Vector4f v1(a1, b1, c1, d1);

  float a2 = Dot(A[2], B.col(0));
  float b2 = Dot(A[2], B.col(1));
  float c2 = Dot(A[2], B.col(2));
  float d2 = Dot(A[2], B.col(3));
  Vector4f v2(a2, b2, c2, d2);

  float a3 = Dot(A[3], B.col(0));
  float b3 = Dot(A[3], B.col(1));
  float c3 = Dot(A[3], B.col(2));
  float d3 = Dot(A[3], B.col(3));
  Vector4f v3(a3, b3, c3, d3);

  Matrix4f mat4(v, v1, v2, v3);
  return mat4;
}

Matrix4f Matrix4f::MakeRotationX(float t) {
  // TODO:
  Matrix4f mat;
  mat.identity();

  mat[1][1] = cos(t);
  mat[1][2] = -sin(t);
  mat[2][1] = sin(t);
  mat[2][2] = cos(t);

  mat = *this * mat;

  return (mat);
}

Matrix4f Matrix4f::MakeRotationY(float t) {
  // TODO:
  Matrix4f mat;
  mat.identity();

  mat[0][0] = cos(t);
  mat[0][2] = sin(t);
  mat[2][0] = -sin(t);
  mat[2][2] = cos(t);

  mat = *this * mat;

  return (mat);
}

Matrix4f Matrix4f::MakeRotationZ(float t) {
  // TODO:
  Matrix4f mat;
  mat.identity();

  mat[0][0] = cos(t);
  mat[0][1] = -sin(t);
  mat[1][0] = sin(t);
  mat[1][1] = cos(t);

  mat = *this * mat;

  return (mat);
}

Matrix4f Matrix4f::MakeScale(float sx, float sy, float sz) {
  // TODO:
  Matrix4f mat;
  mat.identity();

  mat[0][0] = sx;
  mat[1][1] = sy;
  mat[2][2] = sz;

  mat = *this * mat;

  return (mat);
}

#endif
