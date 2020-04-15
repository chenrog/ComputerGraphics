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

 private:
  BasicWidget* widget;

  void buildGui();
};
