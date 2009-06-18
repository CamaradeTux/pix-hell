#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include <assert.h>
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include "QOpenCVWidget.h"
#include "ui_pix_hell.h"

int main(int argc, char **argv) {
  int retval;
  QApplication app(argc, argv);
  a();
  Ui::MainWindow* window = new Ui::MainWindow(0);
  window->setupUi(window);
  window->setWindowTitle("OpenCV --> QtImage");
  window->show();
  retval = app.exec();
  return retval;
}

