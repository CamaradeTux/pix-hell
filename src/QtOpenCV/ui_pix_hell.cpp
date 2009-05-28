#include "ui_pix_hell.h"

Ui_MainWindow::Ui_MainWindow(QWidget* parent) : QMainWindow(parent) {}

Ui::MainWindow::MainWindow(QWidget* parent) : Ui_MainWindow(parent) {
  cvwidget = new QOpenCVWidget(this);
}

void Ui_MainWindow::select_file(){
  QString filename = QFileDialog::getOpenFileName(this,tr("OpenImage"), "/home");
  if (filename != NULL) {
    killTimer(timer_id);
    QByteArray filename_array = filename.toLatin1();
    const char* filename_string = filename_array.data();
    source = cvCreateFileCapture(filename_string);
    assert(source);
    timer_id = startTimer(40);
  }
  return;
}

void Ui_MainWindow::select_camera () {
  source = cvCreateCameraCapture(0);
  assert(source);
  timer_id = startTimer(40);
  return;
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

void apply_filter(IplImage* image, IplImage* dest, type_filtre filtre, int taille) {
  switch(filtre) {
    case BLUR:
      return cvSmooth(image, dest, CV_BLUR, taille, taille, 0, 0);
    case BLUR_NS:
      return cvSmooth(image, dest, CV_BLUR, taille, taille, 0, 0);
    case GAUSSIAN_TROIS:
      return cvSmooth(image, dest, CV_GAUSSIAN, taille, taille, 3, 0);
    case GAUSSIAN_CINQ:
      return cvSmooth(image, dest, CV_GAUSSIAN, taille, taille, 5, 0);
    case MEDIAN:
      return cvSmooth(image, dest, CV_MEDIAN, taille, taille, 0, 0);
    case BILATERAL:
      return cvSmooth(image, dest, CV_BILATERAL, taille, taille, 3, 3);
  }
  return;
}

void Ui_MainWindow::timerEvent(QTimerEvent*){
  int i, count, taille;
  QString type, param;
  QListWidgetItem* item_i;
  count = listWidget->count();
  IplImage* image = cvQueryFrame(source);
  int width = image->width;
  int height = image->height;
  int channels = image->nChannels;
  int depth = image->depth;
  IplImage* dest;
  cvwidget->setGeometry(QRect(19, 13, width, height));
  resize(360+width, 20+height);
  listWidget->setGeometry(QRect(50+width, 0, 250, 130));
  label_2->setGeometry(QRect(60+width, 195, 56, 17));
  label_6->setGeometry(QRect(60+width, 156, 56, 17));
  comboBox_4->setGeometry(QRect(110+width, 150, 175, 26));
  buttonBox_2->setGeometry(QRect(80+width, 230, 180, 32));
  comboBox->setGeometry(QRect(110+width, 190, 175, 26));
  menubar->setGeometry(QRect(0, 0, 360+width, 25));

  for(i = 0; i < count - 1; i++) {
    item_i = listWidget->item(i);
    type = item_i->text().section(" ", 0, 0);
    param = item_i->text().section(" ", 1, 1);
    taille = param.at(0).digitValue();
    dest = cvCreateImage(cvSize(width, height), depth, channels);
    apply_filter(image, dest, filter_of_id(type), taille);
    image = dest;
  }
  cvwidget->putImage(image);
  return;
}

void Ui_MainWindow::apply_changes () {
  QListWidgetItem* current_item = listWidget->currentItem();
  QString type, param, current_text, new_text;
  current_text = current_item->text();
  type = comboBox_4->currentText();
  param = comboBox->currentText();

  if (current_text == "Nouveau") {
    QListWidgetItem* new_item = new QListWidgetItem("Nouveau");
    listWidget->addItem(new_item);
    listWidget->setCurrentItem(new_item);
  }
  
  QTextStream(&new_text) << type << " " << param;

  current_item->setText(new_text);

  return;
}

void Ui_MainWindow::delete_filter () {
  QListWidgetItem* current_item = listWidget->currentItem();
  if (current_item->text() != QString("Nouveau"))
    delete current_item;
  return;
}

