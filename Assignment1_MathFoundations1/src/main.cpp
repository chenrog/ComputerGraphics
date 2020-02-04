// Includes for the assignment
#include <iostream>
#include <string>
#include "Matrix4f.h"
#include "Vector4f.h"

// Tests for comparing our library
// You may compare your operations against the glm library
// which is a well tested library.
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

// VECTOR TESTS
bool compareVec(Vector4f v, glm::vec4 v2) {
  return v[0] == v2[0] && v[1] == v2[1] && v[2] == v2[2] && v[3] == v2[3];
}

// Constructor Test
bool VectorUnitTest0() {
  Vector4f v(1.0f, 1.0f, 1.0f, 1.0f);
  glm::vec4 v2 = glm::vec4(1.0f);

  // initial constructor setup
  if (compareVec(v, v2)) {
    return true;
  }

  return false;
}

// Constructor Test
bool VectorUnitTest1() {
  Vector4f v(1.0f);
  glm::vec4 v2 = glm::vec4(1.0f);

  // initial constructor setup
  if (compareVec(v, v2)) {
    return true;
  }

  return false;
}

// Multiplication Test
bool VectorUnitTest2() {
  Vector4f v(1.0f);
  glm::vec4 v2 = glm::vec4(1.0f);
  v *= 2;
  v2 *= 2;

  // initial constructor setup
  if (compareVec(v, v2)) {
    return true;
  }

  return false;
}

// Division Test
bool VectorUnitTest3() {
  Vector4f v(1.0f);
  glm::vec4 v2 = glm::vec4(1.0f);
  v /= 2;
  v2 /= 2;

  // initial constructor setup
  if (compareVec(v, v2)) {
    return true;
  }

  return false;
}

// Addition Test
bool VectorUnitTest4() {
  Vector4f v(1.0f);
  Vector4f v3(1.0f);
  glm::vec4 v2 = glm::vec4(1.0f);
  glm::vec4 v4 = glm::vec4(1.0f);
  v += v3;
  v2 += v4;

  // initial constructor setup
  if (compareVec(v, v2)) {
    return true;
  }

  return false;
}

// Subtraction Test
bool VectorUnitTest5() {
  Vector4f v(1.0f);
  Vector4f v3(1.0f);
  glm::vec4 v2 = glm::vec4(1.0f);
  glm::vec4 v4 = glm::vec4(1.0f);
  v -= v3;
  v2 -= v4;

  // initial constructor setup
  if (compareVec(v, v2)) {
    return true;
  }

  return false;
}

// Dot Product Test
bool VectorUnitTest6() {
  Vector4f v(3.0f);
  Vector4f v3(2.0f);
  glm::vec4 v2 = glm::vec4(3.0f);
  glm::vec4 v4 = glm::vec4(2.0f);
  float myDot = Dot(v, v3);
  float glmDot = glm::dot(v2, v4);

  // initial constructor setup
  if (myDot == glmDot) {
    return true;
  }

  return false;
}

// Magnitude Test
bool VectorUnitTest7() {
  Vector4f v(3.0f);
  glm::vec4 v2 = glm::vec4(3.0f);

  // initial constructor setup
  if (Magnitude(v) == glm::length(v2)) {
    return true;
  }

  return false;
}

// Normalize Test
bool VectorUnitTest8() {
  Vector4f v(3.0f);
  glm::vec4 v2 = glm::vec4(3.0f);
  v = Normalize(v);
  v2 = glm::normalize(v2);

  // initial constructor setup
  if (compareVec(v, v2)) {
    return true;
  }

  return false;
}

// CrossProduct Test
bool VectorUnitTest9() {
  Vector4f v(3.0f);
  Vector4f v3(2.0f);
  glm::vec3 v2 = glm::vec3(3.0f);
  glm::vec3 v4 = glm::vec3(2.0f);
  v = CrossProduct(v, v3);
  v2 = glm::cross(v2, v4);

  // initial constructor setup
  if (v[0] == v2[0] && v[1] == v2[1] && v[2] == v2[2]) {
    return true;
  }

  return false;
}

// MATRIX TESTS

bool compareMat(Matrix4f mat, glm::mat4 mat2) {
  return (
      mat[0][0] == mat2[0][0] && mat[0][1] == mat2[1][0] &&
      mat[0][2] == mat2[2][0] && mat[0][3] == mat2[3][0] &&
      mat[1][0] == mat2[0][1] && mat[1][1] == mat2[1][1] &&
      mat[1][2] == mat2[2][1] && mat[1][3] == mat2[3][1] &&
      mat[2][0] == mat2[0][2] && mat[2][1] == mat2[1][2] &&
      mat[2][2] == mat2[2][2] && mat[2][3] == mat2[3][2] &&
      mat[3][0] == mat2[0][3] && mat[3][1] == mat2[1][3] &&
      mat[3][2] == mat2[2][3] && mat[3][3] == mat2[3][3]);
}

void printMat(Matrix4f mat) {
  std::cout << mat[0][0] << "," << mat[0][1] << "," << mat[0][2] << ","
            << mat[0][3] << std::endl;
  std::cout << mat[1][0] << "," << mat[1][1] << "," << mat[1][2] << ","
            << mat[1][3] << std::endl;
  std::cout << mat[2][0] << "," << mat[2][1] << "," << mat[2][2] << ","
            << mat[2][3] << std::endl;
  std::cout << mat[3][0] << "," << mat[3][1] << "," << mat[3][2] << ","
            << mat[3][3] << std::endl;
  std::cout << std::endl;
  return;
}

void printMat(glm::mat4 mat) {
  std::cout << mat[0][0] << "," << mat[0][1] << "," << mat[0][2] << ","
            << mat[0][3] << std::endl;
  std::cout << mat[1][0] << "," << mat[1][1] << "," << mat[1][2] << ","
            << mat[1][3] << std::endl;
  std::cout << mat[2][0] << "," << mat[2][1] << "," << mat[2][2] << ","
            << mat[2][3] << std::endl;
  std::cout << mat[3][0] << "," << mat[3][1] << "," << mat[3][2] << ","
            << mat[3][3] << std::endl;
  std::cout << std::endl;
  return;
}

// Identity Matrix
bool unitTest0() {
  Matrix4f myIdentity(1.0f, 0, 0, 0,
                      0, 1.0f, 0, 0,
                      0, 0, 1.0f, 0,
                      0, 0, 0, 1.0f);
  glm::mat4 glmIdentityMatrix = glm::mat4(1.0f);

  if (compareMat(myIdentity, glmIdentityMatrix)) {
    return true;
  }

  return false;
}

// Identity Matrix with vectors
bool unitTest1() {
  Vector4f a(1.0f, 0.0f, 0.0f, 0.0f);
  Vector4f b(0.0f, 1.0f, 0.0f, 0.0f);
  Vector4f c(0.0f, 0.0f, 1.0f, 0.0f);
  Vector4f d(0.0f, 0.0f, 0.0f, 1.0f);
  Matrix4f myIdentity(a, b, c, d);
  glm::mat4 glmIdentityMatrix = glm::mat4(1.0f);

  if (compareMat(myIdentity, glmIdentityMatrix)) {
    return true;
  }

  return false;
}

// Extra Constructor
bool unitTest2() {
  Matrix4f mat(3.0f);
  glm::mat4 mat2 = glm::mat4(3.0f);

  if (compareMat(mat, mat2)) {
    return true;
  }

  return false;
}

// Test against glm::scale
bool unitTest3() {
  Vector4f a(1.0f, 0, 0, 0);
  Vector4f b(0.0f, 1.0f, 0, 0);
  Vector4f c(0, 0, 1.0f, 0);
  Vector4f d(0, 0, 0, 1.0f);
  Matrix4f myScaled(a, b, c, d);
  myScaled = myScaled.MakeScale(1.2f, 3.0f, 4.5f);

  glm::mat4 glmScale = glm::mat4(1.0f);
  glmScale = glm::scale(glmScale, glm::vec3(1.2f, 3.0f, 4.5f));

  if (compareMat(myScaled, glmScale)) {
    return true;
  }

  return false;
}

// Testing operator
bool unitTest4() {
  glm::mat4 glmTest = glm::mat4(1.0f);
  glmTest[1][3] = 72.0f;
  glmTest[2][3] = 2.1f;

  Matrix4f myMatrix(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

  myMatrix[1][3] = 72.0f;
  myMatrix[2][3] = 2.1f;

  if (glmTest[1][3] == myMatrix[1][3] && glmTest[2][3] == myMatrix[2][3]) {
    return true;
  }

  return false;
}

// col getter
bool unitTest5() {
  Matrix4f mat(3.0f);
  Vector4f v(0, 3.0f, 0, 0);

  if (mat.col(1) == v) {
    return true;
  }

  return false;
}

// mat * vector
bool unitTest6() {
  glm::mat4 mat2 = glm::mat4(3.0f);
  mat2[1][3] = 72.0f;
  mat2[2][3] = 2.1f;
  glm::vec4 v2 = glm::vec4(2.0f);
  v2[3] = 3.0f;
  v2 = mat2 * v2;

  Matrix4f mat(3.0f);
  mat[3][1] = 72.0f;
  mat[3][2] = 2.1f;
  Vector4f v(2.0f);
  v[3] = 3.0f;
  v = mat * v;

  if (compareVec(v, v2)) {
    return true;
  }

  return false;
}

// mat * mat
bool unitTest7() {
  glm::mat4 mat2 = glm::mat4(3.0f);
  mat2[1][3] = 72.0f;
  mat2[2][3] = 2.1f;
  glm::mat4 mat4 = glm::mat4(3.0f);
  mat2[2][0] = 72.0f;
  mat2[1][1] = 2.1f;
  mat2 = mat2 * mat4;

  Matrix4f mat(3.0f);
  mat[3][1] = 72.0f;
  mat[3][2] = 2.1f;
  Matrix4f mat3(3.0f);
  mat[0][2] = 72.0f;
  mat[1][1] = 2.1f;
  mat = mat * mat3;

  if (compareMat(mat, mat2)) {
    return true;
  }

  return false;
}

// RotationX
bool unitTest8() {
  Matrix4f mat(3.0f);
  mat[3][1] = 72.0f;
  mat[3][2] = 2.1f;

  glm::mat4 glmMat = glm::mat4(3.0f);
  glmMat[1][3] = 72.0f;
  glmMat[2][3] = 2.1f;

  float angle = .454;
  mat = mat.MakeRotationX(angle);
  glmMat = glm::rotate(glmMat, angle, glm::vec3(1, 0, 0));
  if (compareMat(mat, glmMat)) {
    return true;
  }

  return false;
}

// RotationY
bool unitTest9() {
  Matrix4f mat(3.0f);
  mat[3][1] = 72.0f;
  mat[3][2] = 2.1f;

  glm::mat4 glmMat = glm::mat4(3.0f);
  glmMat[1][3] = 72.0f;
  glmMat[2][3] = 2.1f;

  float angle = .454;
  mat = mat.MakeRotationY(angle);
  glmMat = glm::rotate(glmMat, angle, glm::vec3(0, 1, 0));
  if (compareMat(mat, glmMat)) {
    return true;
  }

  return false;
}

// RotationZ
bool unitTest10() {
  Matrix4f mat(3.0f);
  mat[3][1] = 72.0f;
  mat[3][2] = 2.1f;

  glm::mat4 glmMat = glm::mat4(3.0f);
  glmMat[1][3] = 72.0f;
  glmMat[2][3] = 2.1f;

  float angle = .454;
  mat = mat.MakeRotationZ(angle);
  glmMat = glm::rotate(glmMat, angle, glm::vec3(0, 0, 1));
  if (compareMat(mat, glmMat)) {
    return true;
  }

  return false;
}

int main() {
  // Keep track of the tests passed
  unsigned int testsPassed = 0;
  std::cout << "VECTOR4 TESTS"
            << "\n";
  std::cout << "4FloatsConstructor: " << VectorUnitTest0() << " \n";
  std::cout << "1FloatConstructor: " << VectorUnitTest1() << " \n";
  std::cout << "Multiplication: " << VectorUnitTest2() << " \n";
  std::cout << "Division: " << VectorUnitTest3() << " \n";
  std::cout << "Addition: " << VectorUnitTest4() << " \n";
  std::cout << "Subtraction: " << VectorUnitTest5() << " \n";
  std::cout << "Dot: " << VectorUnitTest6() << " \n";
  std::cout << "Magnitude: " << VectorUnitTest7() << " \n";
  std::cout << "Normalize: " << VectorUnitTest8() << " \n";
  std::cout << "CrossProduct: " << VectorUnitTest9() << " \n";

  // Run 'unit tests'
  std::cout << "\nMATRIX4 TESTS"
            << "\n";
  std::cout << "Passed 0: " << unitTest0() << " \n";
  std::cout << "Passed 1: " << unitTest1() << " \n";
  std::cout << "Passed 2: " << unitTest2() << " \n";
  std::cout << "Passed 3: " << unitTest3() << " \n";
  std::cout << "Passed 4: " << unitTest4() << " \n";
  std::cout << "Passed 5: " << unitTest5() << " \n";
  std::cout << "Passed 6: " << unitTest6() << " \n";
  std::cout << "Passed 7: " << unitTest7() << " \n";
  std::cout << "Passed 8: " << unitTest8() << " \n";
  std::cout << "Passed 9: " << unitTest9() << " \n";
  std::cout << "Passed 10: " << unitTest10() << " \n";

  return 0;
}
