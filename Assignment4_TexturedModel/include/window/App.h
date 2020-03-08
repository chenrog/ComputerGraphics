#pragma once

#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <iostream>
#include <string>

#include "BasicWidget.h"

class App : public QMainWindow {
  Q_OBJECT

 public:
  App(QWidget* parent = 0);
  virtual ~App();

 signals:

 private slots:
  void selectObject(QString filepath);

 private:
  BasicWidget* widget;

  void buildGui();
  void populateObjectSelectMenu(QMenu* objectMenu);
};
