#include "PPM.h"
#include <QString>
#include <QStringList>
#include <fstream>
#include <iostream>

PPM::PPM(std::string fileName) {
  std::ifstream ppm_file;
  ppm_file.open(fileName);

  if (ppm_file.is_open()) {
    int values_stored = 0;  // where in the pixel data array are you
    int step = 0;           // header, img_size, max, data
    std::string line;

    while (getline(ppm_file, line)) {
      // ignore comments
      if (line[0] == '#') {
        continue;
      }

      // capture header information
      else if (step == 0) {
        header = line;
        step++;
      }
      // get width and height
      else if (step == 1) {
        setPPMSize(line);
        step++;
      }
      // max value
      else if (step == 2) {
        max_value = std::stoi(line);
        step++;
      }
      // read data
      else {
        QString qline = QString::fromStdString(line);
        QStringList data = qline.split(' ', QString::SkipEmptyParts);

        for (int i = 0; i < data.size(); i++) {
          m_PixelData[values_stored] = std::stoi(data[i].toStdString());
          values_stored++;
        }
      }
    }
  }
}

void PPM::setPPMSize(std::string line) {
  QString qline = QString::fromStdString(line);
  QStringList img_size = qline.split(' ');
  m_width = std::stoi(img_size[0].toStdString());
  m_height = std::stoi(img_size[1].toStdString());
  m_PixelData = new unsigned int[m_width * m_height * 3];
}

// Destructor clears any memory that has been allocated
PPM::~PPM() { delete[] m_PixelData; }

// Saves a PPM Image to a new file.
void PPM::savePPM(std::string outputFileName) {
  // TODO: Save a PPM image to disk
  std::ofstream outFile;
  outFile.open(outputFileName);
  outFile << header << std::endl;
  outFile << m_width << " " << m_height << std::endl;
  outFile << max_value << std::endl;

  for (int i = 0; i < (m_width * m_height * 3); i++) {
    outFile << *(m_PixelData + i) << std::endl;
  }
}

// Darken subtracts 50 from each of the red, green
// and blue color components of all of the pixels
// in the PPM. Note that no values may be less than
// 0 in a ppm.
void PPM::darken() {
  for (int i = 0; i < (m_width * m_height * 3); i++) {
    int old_val = *(m_PixelData + i);
    int new_val = old_val - (50 * (max_value / 255));
    if (new_val < 0) {
      new_val = 0;
    }
    *(m_PixelData + i) = new_val;
  }
}

// Sets a pixel to a specific R,G,B value
void PPM::setPixel(int x, int y, int R, int G, int B) {
  // TODO: Implement
  int index = (x + (y * m_width)) * 3;
  *(m_PixelData + index) = R;
  *(m_PixelData + index + 1) = G;
  *(m_PixelData + index + 2) = B;
}
