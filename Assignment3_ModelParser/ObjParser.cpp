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
  vertexNormals.clear();
  vertexTextures.clear();
  vertices.clear();
  indices.clear();
}

void ObjParser::pushVertices(QStringList data) {
  for (int i = 0; i < data.size(); i++) {
    vertices.push_back(data[i].toFloat());
  }
}

void ObjParser::pushVertexNormals(QStringList data) {
  for (int i = 0; i < data.size(); i++) {
    vertexNormals.push_back(data[i].toFloat());
  }
}

void ObjParser::pushVertexTextures(QStringList data) {
  for (int i = 0; i < data.size(); i++) {
    vertexTextures.push_back(data[i].toFloat());
  }
}

void ObjParser::pushIndices(QStringList data) {
  for (int i = 0; i < data.size(); i++) {
    QStringList tuple = data[i].split("//");
    uint vertex = tuple[0].toUInt() - 1;
    uint vertexNormal = tuple[1].toUInt() - 1;
    indices.push_back(vertex);
  }
}

void ObjParser::parse(QString filePath) {
  std::ifstream file;
  file.open(filePath.toStdString());

  this->clear();

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
    // vertex
    else if (line[0] == 'v') {
      pushVertices(data);
    }
    // face
    else if (line[0] == 'f') {
      pushIndices(data);
    }
    // nothing valid
    else {
      continue;
    }
  }

  file.close();
}

QVector<float> ObjParser::getVertices() { return vertices; }

QVector<float> ObjParser::getVertexNormals() { return vertexNormals; }

QVector<uint> ObjParser::getIndices() { return indices; }
