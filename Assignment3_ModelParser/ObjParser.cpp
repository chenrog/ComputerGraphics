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

  vertex_normals.clear();
  vertices.clear();
  indices.clear();

  std::string line;
  while (getline(file, line)) {
    QString qline = QString::fromStdString(line);
    QStringList data = qline.split(' ', QString::SkipEmptyParts);
    data.takeFirst();  // removes the type from array so only numbers

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
        QStringList tuple = data[i].split("//");
        uint vertex = tuple[0].toUInt() - 1;
        uint vertexNormal = tuple[1].toUInt() - 1;
        indices.push_back(vertex);
      }
    }
  }
}

QVector<float> ObjParser::getVertices() { return vertices; }

QVector<float> ObjParser::getVertexNormals() { return vertex_normals; }

QVector<uint> ObjParser::getIndices() { return indices; }
