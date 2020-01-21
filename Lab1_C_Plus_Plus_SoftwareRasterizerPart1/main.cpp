/** @file main.cpp
 *  @brief Entry point into our program.
 *
 *  Welcome to the Great Looking Software Render
 *  code base (Yes, I needed something with a gl prefix).
 *
 *  This is where you will implement your graphics API.
 *
 *  Compile on the terminal with:
 *
 *  clang++ -std=c++11 main.cpp -o main
 *
 *  @author Mike Shah
 *  @bug No known bugs.
 */

// Some define values
#define WINDOW_HEIGHT 320
#define WINDOW_WIDTH 320

// C++ Standard Libraries
#include <iostream>
#include <unordered_map>

// User libraries
#include "Color.h"
#include "GL.h"
#include "Maths.h"
#include "TGA.h"

// Create a canvas to draw on.
TGA canvas(WINDOW_WIDTH, WINDOW_HEIGHT);
std::unordered_map<int, int*> triangle_points;

void record_point(int x, int y) {
  if (triangle_points.find(y) == triangle_points.end()) {
    int* arr = new int[2];
    arr[0] = x;
    arr[1] = x;
    triangle_points[y] = arr;
  }
  // If key found then iterator to that key is returned
  else {
    int* existing_x = triangle_points.at(y);

    int min = *existing_x;
    int max = *(existing_x + 1);

    if (x < min) {
      *existing_x = x;
    }
    if (x > max) {
      *(existing_x + 1) = x;
    }
  }
}

// Implementation of Bresenham's Line Algorithm
// The input to this algorithm is two points and a color
// This algorithm will then modify a canvas (i.e. image)
// filling in the appropriate colors.
void drawLine(Vec2 v0, Vec2 v1, TGA& image, ColorRGB c, bool record = false) {
  bool steep = false;
  if (std::abs(v0.x - v1.x) < std::abs(v0.y - v1.y)) {
    // If the line is steep we want to transpose the image.
    std::swap(v0.x, v0.y);
    std::swap(v1.x, v1.y);
    steep = true;
  }
  if (v0.x > v1.x) {  // make it left-to-right
    std::swap(v0.x, v1.x);
    std::swap(v0.y, v1.y);
  }
  for (int x = v0.x; x <= v1.x; ++x) {
    float t = (x - v0.x) / (float)(v1.x - v0.x);
    int y = v0.y * (1.0f - t) + v1.y * t;
    if (steep) {
      canvas.setPixelColor(y, x, c);
      if (record) {
        record_point(y, x);
      }
    } else {
      canvas.setPixelColor(x, y, c);
      if (record) {
        record_point(x, y);
      }
    }
  }
}

// Draw a triangle
void triangle(Vec2 v0, Vec2 v1, Vec2 v2, TGA& image, ColorRGB c) {
  if (glFillMode == LINE) {
    drawLine(v0, v1, image, c);
    drawLine(v1, v2, image, c);
    drawLine(v2, v0, image, c);
  }
  // TODO: Draw a filled triangle
  if (glFillMode == FILL) {
    drawLine(v0, v1, image, c, true);
    drawLine(v1, v2, image, c, true);
    drawLine(v2, v0, image, c, true);

    std::unordered_map<int, int*>::iterator itr;
    int counter = 0;
    for (itr = triangle_points.begin(); itr != triangle_points.end(); itr++) {
        int y = itr->first;
        int* xs = itr->second;
        int x1 = *xs;
        int x2 = *(xs + 1);

        Vec2 v4 = Vec2(x1, y);
        Vec2 v5 = Vec2(x2, y);
        drawLine(v4, v5, image, c);

        delete[] itr->second;
     }

     triangle_points.clear();
  }
}

// Main
int main() {
  // A sample of color(s) to play with
  ColorRGB red = {255, 0, 0};
  ColorRGB green = {0, 255, 0};
  ColorRGB blue = {0, 0, 255};

  // Points for our Line
  Vec2 line[2] = {Vec2(0, 0), Vec2(100, 100)};

  // Set the fill mode
  glPolygonMode(FILL);

  // Draw a line
  // drawLine(line[0], line[1], canvas, red);

  // Data for our triangle
  Vec2 tri[3] = {Vec2(30, 30), Vec2(100, 90), Vec2(50, 75)};
  Vec2 tri2[3] = {Vec2(250, 150), Vec2(200, 60), Vec2(150, 150)};
  Vec2 tri3[3] = {Vec2(75, 300), Vec2(75, 250), Vec2(50, 250)};

  // Draw a triangle
  triangle(tri[0], tri[1], tri[2], canvas, red);
  triangle(tri2[0], tri2[1], tri2[2], canvas, green);
  triangle(tri3[0], tri3[1], tri3[2], canvas, blue);

  // Output the final image
  canvas.outputTGAImage("graphics_lab2.ppm");

  return 0;
}
