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
  QMenu* objectsMenu = file->addMenu("Objects");
  populateObjectSelectMenu(objectsMenu);
  QAction* exit = file->addAction("Quit", [this]() { close(); });
}

void App::selectObject(QString filePath) {
  std::cout << filePath.toStdString() << std::endl;
}

void App::populateObjectSelectMenu(QMenu* objectMenu) {
  QDirIterator objectsDirIterator("objects", QStringList() << "*.obj",
                                  QDir::NoFilter, QDirIterator::Subdirectories);

  QMap<QString, QString> objects;
  while (objectsDirIterator.hasNext()) {
    objectsDirIterator.next();
    // ex. "bunny.obj" -> "bunny"
    QString fileName = objectsDirIterator.fileName().split('.')[0];
    QString filePath = objectsDirIterator.filePath();
    objects[fileName] = filePath;
  }

  foreach (QString fileName, objects.keys()) {
    QString filePath = objects[fileName];
    auto select = [this, filePath]() { selectObject(filePath); };
    objectMenu->addAction(fileName, select);
  }
}
