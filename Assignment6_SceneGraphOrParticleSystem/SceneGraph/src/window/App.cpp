#include "App.h"

App::App(QWidget* parent) : QMainWindow(parent) { buildGui(); }

App::~App(){};

void App::buildGui() {
  // Our basic widget.
  this->widget = new BasicWidget(this);
  setCentralWidget(widget);

  // A simple menubar.
  QMenuBar* menu = menuBar();
  QMenu* file = menu->addMenu("File");
  QAction* exit = file->addAction("Quit", [this]() { close(); });
}
