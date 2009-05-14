#include "ui_pix_hell.h"

const char* path = "/root/work/pix-hell/src/QtOpenCV/test.avi";

Ui_MainWindow::Ui_MainWindow(QWidget* parent) : QMainWindow(parent) {}

Ui::MainWindow::MainWindow(QWidget* parent) : Ui_MainWindow(parent) {
  source = cvCreateFileCapture("/root/test.avi");
  printf("chemin : %s\n", path);
  cvwidget = new QOpenCVWidget(this);
  assert(source);
  assert(cvwidget);
  startTimer(40);
}

void Ui_MainWindow::new_file_source () {
  source = cvCreateFileCapture("/root/test.avi");
}

type_filtre filter_of_id(QString name) {
  if (QString("BLUR_NS") == name)
    return BLUR_NS;
  if (QString("BLUR") == name)
    return BLUR;
  if (QString("GAUSSIAN_TROIS") == name)
    return GAUSSIAN_TROIS;
  if (QString("GAUSSIAN_CINQ") == name)
    return GAUSSIAN_CINQ;
  if (QString("MEDIAN") == name)
    return MEDIAN;
  if (QString("BILATERAL") == name)
    return BILATERAL;
}

void apply_filter(IplImage* image, type_filtre filtre, int taille) {
  switch(filtre) {
    case BLUR:
      return cvSmooth(image, image, CV_BLUR, taille, taille, 0, 0);
    case BLUR_NS:
      return cvSmooth(image, image, CV_BLUR, taille, taille, 0, 0);
    case GAUSSIAN_TROIS:
      return cvSmooth(image, image, CV_GAUSSIAN, taille, taille, 3, 0);
    case GAUSSIAN_CINQ:
      return cvSmooth(image, image, CV_GAUSSIAN, taille, taille, 5, 0);
    case MEDIAN:
      return cvSmooth(image, image, CV_MEDIAN, taille, taille, 0, 0);
    case BILATERAL:
      return cvSmooth(image, image, CV_BILATERAL, taille, taille, 3, 3);
  }
}

void Ui_MainWindow::timerEvent(QTimerEvent*){
  int i, count, taille;
  QString type, param;
  QListWidgetItem* item_i;
  count = listWidget->count();
  IplImage* image = cvQueryFrame(source);
  for(i = 0; i < count - 1; i++) {
    item_i = listWidget->item(i);
    type = item_i->text().section(" ", 0, 0);
    param = item_i->text().section(" ", 1, 1);
    taille = param.at(0).digitValue();
    apply_filter(image, filter_of_id(type), taille);
  }
  cvwidget->putImage(image);
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
  QListWidgetItem* current_item = listWidget->currentItem();
  int index;
  index = comboBox_4->findText(current_item->text().section(" ", 0, 0));
  comboBox_4->setCurrentIndex(index);
  index = comboBox->findText(current_item->text().section(" ", 1, 1));
  comboBox->setCurrentIndex(index);
  return;
}
