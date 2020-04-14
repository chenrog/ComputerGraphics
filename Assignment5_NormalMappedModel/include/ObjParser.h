#pragma once

#include <QString>
#include <QStringList>
#include <QVector>
#include <QtGui>
#include <fstream>
#include <iostream>
#include <string>

#include "VertexData.h"

class ObjParser {
 private:
  ObjParser();
  ObjParser(ObjParser const&);
  virtual ~ObjParser();

  void clear();
  QString constructFilePath(QString filePath, QString newFileName);
  void pushVertexPositions(QStringList data);
  void pushVertexTextures(QStringList data);
  void pushVertexNormals(QStringList data);
  void pushVerticesAndIndices(QStringList data);
  void getTextureFile(QString mtlFilePath);

 protected:
  QVector<VertexData> vertices;
  QVector<QVector3D> vertexPositions;
  QVector<QVector2D> vertexTextures;
  QVector<float> vertexNormals;
  QVector<uint> indices;
  QString textureFilePath;

 public:
  static ObjParser* Instance();

  void parse(QString filePath);
  QVector<VertexData> getVertices();
  QVector<uint> getIndices();
  QString getTextureFilePath();
};
