#pragma once

#include <QString>
#include <QStringList>
#include <QVector>
#include <fstream>
#include <iostream>
#include <string>

class ObjParser {
 private:
  ObjParser();
  ObjParser(ObjParser const&);
  virtual ~ObjParser();

  void clear();
  void pushVertices(QStringList data);
  void pushVertexNormals(QStringList data);
  void pushVertexTextures(QStringList data);
  void pushIndices(QStringList data);

 protected:
  QVector<float> vertices;
  QVector<float> vertexNormals;
  QVector<float> vertexTextures;
  QVector<uint> indices;

 public:
  static ObjParser* Instance();

  void parse(QString filePath);
  QVector<float> getVertices();
  QVector<float> getVertexNormals();
  QVector<float> getVertexTextures();
  QVector<uint> getIndices();
};
