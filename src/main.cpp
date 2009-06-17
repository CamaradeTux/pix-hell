#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include <assert.h>
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include "QOpenCVWidget.h"
#include "ui_pix_hell.h"

void g(int a, int b, int c) {
  printf("%d ; %d ; %d\n", a, b, c);
  return;
}

void a() {
  void* h = (void*) &g;
  fn<int,int,int,void,void>* b = new fn<int,int,int,void,void>("a", &h, 3);
}

int main(int argc, char **argv) {
  a();
  int retval;
  QApplication app(argc, argv);
  Ui::MainWindow* window = new Ui::MainWindow(0);
  window->setupUi(window);
  window->setWindowTitle("OpenCV --> QtImage");
  window->show();
  retval = app.exec();
  return retval;
}

