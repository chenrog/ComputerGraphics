#pragma once

#include <QString>
#include <QStringList>
#include <QVector>
#include <fstream>
#include <iostream>
#include <string>

class ObjParser {
 private:
 protected:
  QVector<float> vertices;
  QVector<float> vertex_normals;
  QVector<uint> indices;

 public:
  ObjParser();
  virtual ~ObjParser();

  void parse(std::string fileName);
  QVector<float> getVertices();
  QVector<float> getVertexNormals();
  QVector<uint> getIndices();
};
