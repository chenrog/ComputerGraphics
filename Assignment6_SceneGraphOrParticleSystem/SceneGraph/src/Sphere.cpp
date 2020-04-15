#include "Sphere.h"

Sphere::Sphere(QString textureFile) {
  init();
  Renderable::init(vertices, index_, textureFile);
}

// Algorithm for rendering a sphere
// The algorithm was obtained here: http://learningwebgl.com/blog/?p=1253
// Please review the page so you can understand the algorithm.
void Sphere::init() {
  unsigned int latitudeBands = 30;
  unsigned int longitudeBands = 30;
  float radius = 1.0f;
  double PI = 3.14159265359;

  for (unsigned int latNumber = 0; latNumber <= latitudeBands; latNumber++) {
    float theta = latNumber * PI / latitudeBands;
    float sinTheta = sin(theta);
    float cosTheta = cos(theta);

    for (unsigned int longNumber = 0; longNumber <= longitudeBands;
         longNumber++) {
      float phi = longNumber * 2 * PI / longitudeBands;
      float sinPhi = sin(phi);
      float cosPhi = cos(phi);

      float x = cosPhi * sinTheta;
      float y = cosTheta;
      float z = sinPhi * sinTheta;
      // Why is this "1-" Think about the range of texture coordinates
      float u = 1 - ((float)longNumber / (float)longitudeBands);
      float v = 1 - ((float)latNumber / (float)latitudeBands);

      QVector3D position = QVector3D(radius * x, radius * y, radius * z);
      QVector3D normal = QVector3D(radius * x, radius * y, radius * z);
      QVector2D textureCoords = QVector2D(u, v);
      VertexData vertex = VertexData(position, normal, textureCoords);
      vertices.push_back(vertex);
    }
  }

  // Now that we have all of our vertices
  // generated, we need to generate our indices for our
  // index element buffer.
  // This diagram shows it nicely visually
  // http://learningwebgl.com/lessons/lesson11/sphere-triangles.png
  for (unsigned int latNumber1 = 0; latNumber1 < latitudeBands; latNumber1++) {
    for (unsigned int longNumber1 = 0; longNumber1 < longitudeBands;
         longNumber1++) {
      unsigned int first = (latNumber1 * (longitudeBands + 1)) + longNumber1;
      unsigned int second = first + longitudeBands + 1;
      index_.push_back(first);
      index_.push_back(second);
      index_.push_back(first + 1);

      index_.push_back(second);
      index_.push_back(second + 1);
      index_.push_back(first + 1);
    }
  }
}
