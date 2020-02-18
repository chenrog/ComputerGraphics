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

void ObjParser::parse(std::string fileName) {
  std::ifstream file;
  file.open("./objects/" + fileName);

  std::string line;
  while (getline(file, line)) {
    QString qline = QString::fromStdString(line);
    QStringList data = qline.split(' ', QString::SkipEmptyParts);

    // vertex normal
    if (line[0] == 'v' && line[1] == 'n') {
      for (int i = 0; i < data.size(); i++) {
        vertex_normals.push_back(data[i].toFloat());
      }
    }
    // vertex
    else if (line[0] == 'v') {
      for (int i = 0; i < data.size(); i++) {
        vertices.push_back(data[i].toFloat());
      }
    }
    // face
    else if (line[0] == 'f') {
      for (int i = 0; i < data.size(); i++) {
        indices.push_back(data[i].toUInt() - 1);
      }
    }
  }
}

QVector<float> ObjParser::getVertices() { return vertices; }

QVector<float> ObjParser::getVertexNormals() { return vertex_normals; }

QVector<uint> ObjParser::getIndices() { return indices; }