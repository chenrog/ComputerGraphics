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
  textureFilePath = "";
}

QString ObjParser::constructFilePath(QString filePath, QString newFileName) {
  QStringList directory = filePath.split('/', QString::SkipEmptyParts);
  directory.removeLast();  // get rid of old filename
  directory.append(newFileName);
  return directory.join("/");
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
  // jump by 2 so we can capture each set of coordinates
  for (int i = 0; i < data.size() / 2; i += 2) {
    // multiplying by -1 seems to flip it to the correct orientation
    float s = data[i].toFloat() * -1;
    float t = data[i + 1].toFloat() * -1;
    QVector2D texture = QVector2D(s, t);
    vertexTextures.push_back(texture);
  }
}

void ObjParser::pushVertexNormals(QStringList data) {
  // stubbed for now
}

void ObjParser::pushVerticesAndIndices(QStringList data) {
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

    indices.push_back(vertices.indexOf(vertex));
  }
}

void ObjParser::getTextureFile(QString filePath) {
  std::ifstream file;
  file.open(filePath.toStdString());

  std::string line;
  while (getline(file, line)) {
    if (line.empty()) {
      continue;
    }

    QString qline = QString::fromStdString(line);
    QStringList data = qline.split(' ', QString::SkipEmptyParts);
    QString type = data.takeFirst();  // this also removes type

    if (type == "map_Kd") {
      textureFilePath = constructFilePath(filePath, data[0]);
    }
  }

  file.close();
}

void ObjParser::parse(QString filePath) {
  std::ifstream file;
  file.open(filePath.toStdString());

  clear();
  QString mtlFilePath;

  std::string line;
  while (getline(file, line)) {
    if (line.empty()) {
      continue;
    }

    QString qline = QString::fromStdString(line);
    QStringList data = qline.split(' ', QString::SkipEmptyParts);
    QString type = data.takeFirst();  // this also removes type

    // vertex normal
    if (type == "vn") {
      pushVertexNormals(data);
    }
    // vertex texure, we ignore this for now but would mess with vertex
    else if (type == "vt") {
      pushVertexTextures(data);
    }
    // vertex positions
    else if (type == "v") {
      pushVertexPositions(data);
    }
    // face / VertexData
    else if (type == "f") {
      pushVerticesAndIndices(data);
    }
    // find path to mtl
    else if (type == "mtllib") {
      mtlFilePath = constructFilePath(filePath, data[0]);
    }
    // invalid or ignored
    else {
      continue;
    }
  }

  file.close();

  if (!mtlFilePath.isEmpty()) {
    getTextureFile(mtlFilePath);
  }
}

QVector<VertexData> ObjParser::getVertices() { return vertices; }
QVector<uint> ObjParser::getIndices() { return indices; }
QString ObjParser::getTextureFilePath() { return textureFilePath; }
