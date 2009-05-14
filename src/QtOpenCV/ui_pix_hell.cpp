#include "ui_pix_hell.h"

const char* path = "/root/work/pix-hell/src/QtOpenCV/test.avi";

Ui_MainWindow::Ui_MainWindow(QWidget* parent) : QMainWindow(parent) {}

Ui::MainWindow::MainWindow(QWidget* parent) : Ui_MainWindow(parent) {
  /*
  source = cvCreateFileCapture(path);
  printf("chemin : %s\n", path);
  cvwidget = new QOpenCVWidget(this);
  assert(source);
  assert(cvwidget);
  IplImage* image = cvQueryFrame(source);
  cvwidget->putImage(image);*/
}

void Ui_MainWindow::new_file_source () {
  source = cvCreateFileCapture("/root/stream.dump");
}

void Ui_MainWindow::new_camera_source () {
  source = cvCreateCameraCapture(0);
  return;
}

void Ui_MainWindow::apply_changes () {
  QListWidgetItem* current_item = listWidget->currentItem();
  QString type, param, current_text, new_text;
  current_text = current_item->text();
  type = comboBox_4->currentText();
  param = comboBox->currentText();

  if (current_text == "Nouveau")
    listWidget->addItem(QApplication::translate("MainWindow", "Nouveau", 0, QApplication::UnicodeUTF8));
  
  QTextStream(&new_text) << type << " " << param;

  current_item->setText(new_text);

  return;
}

void Ui_MainWindow::discard_changes () {
  return;
}
