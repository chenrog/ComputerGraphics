#pragma once

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

class App : public QMainWindow {
  Q_OBJECT

 public:
  App(QWidget* parent = 0);
  virtual ~App();

 signals:

 public slots:

 private:
  void buildGui();
};
