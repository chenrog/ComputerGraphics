#include "ObjParser.h"

ObjParser* OP_Instance = NULL;

//////////////////////////////////////////////////////////////////////
// Publics
ObjParser::ObjParser() {}

ObjParser::ObjParser(ObjParser const&) {}

ObjParser::~ObjParser() {}

ObjParser* ObjParser::Instance() {
  if (!OP_Instance) {
    OP_Instance = new ObjParser;
  }

  return OP_Instance;
}

void ObjParser::clear() {
  vertexPositions.clear();
  vertexTextures.clear();
  vertexNormals.clear();
  vertices.clear();
  indices.clear();
}

void ObjParser::pushVertexPositions(QStringList data) {
  for (int i = 0; i < data.size(); i += 3) {
    float x = data[i].toFloat();
    float y = data[i + 1].toFloat();
    float z = data[i + 2].toFloat();
    QVector3D position = QVector3D(x, y, z);
    vertexPositions.push_back(position);
  }
}

void ObjParser::pushVertexTextures(QStringList data) {
  for (int i = 0; i < data.size() / 2; i += 2) {
    float s = data[i].toFloat();
    float t = data[i + 1].toFloat();
    QVector2D texture = QVector2D(s, t);
    vertexTextures.push_back(texture);
  }
}

void ObjParser::pushVertexNormals(QStringList data) {
  // stubbed for now
}

void ObjParser::pushVertices(QStringList data) {
  for (int i = 0; i < data.size(); i++) {
    QStringList tuple = data[i].split("/");
    // get indices
    uint positionIdx = tuple[0].toUInt() - 1;
    uint textureIdx = tuple[1].toUInt() - 1;
    // uint vertexNormal = tuple[2].toUInt() - 1;
    // create VertexData
    QVector3D position = vertexPositions[positionIdx];
    QVector2D texture = vertexTextures[textureIdx];
    VertexData vertex = VertexData(position, texture);
    // add to vertices if not already included
    if (!vertices.contains(vertex)) {
      vertices.push_back(vertex);
    }
  }
}

void ObjParser::parse(QString filePath) {
  std::ifstream file;
  file.open(filePath.toStdString());

  clear();

  std::string line;
  while (getline(file, line)) {
    QString qline = QString::fromStdString(line);
    QStringList data = qline.split(' ', QString::SkipEmptyParts);
    data.takeFirst();  // removes the type from array so only numbers

    // vertex normal
    if (line[0] == 'v' && line[1] == 'n') {
      pushVertexNormals(data);
    }
    // vertex texure, we ignore this for now but would mess with vertex
    else if (line[0] == 'v' && line[1] == 't') {
      pushVertexTextures(data);
    }
    // vertex positions
    else if (line[0] == 'v') {
      pushVertexPositions(data);
    }
    // face / VertexData
    else if (line[0] == 'f') {
      pushVertices(data);
    }
    // invalid
    else {
      continue;
    }
  }

  file.close();
}

QVector<VertexData> ObjParser::getVertices() { return vertices; }
