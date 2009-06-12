#include "ui_pix_hell.h"

Ui_MainWindow::Ui_MainWindow(QWidget* parent) : QMainWindow(parent) {}

Ui::MainWindow::MainWindow(QWidget* parent) : Ui_MainWindow(parent) {

}

void Ui_MainWindow::select_file(){
  QString filename = QFileDialog::getOpenFileName(this,tr("OpenImage"), "/home");
  if (filename != NULL) {
    killTimer(timer_id);
    QByteArray filename_array = filename.toLatin1();
    const char* filename_string = filename_array.data();
    source = cvCreateFileCapture(filename_string);
    assert(source);
    timer_id = startTimer(1);
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

IplImage* Ui_MainWindow::apply_filter(IplImage* image, type_filtre filtre, int taille) {
  IplImage* dest;
  switch(filtre) {
    case BLUR:
      cvSmooth(image, image, CV_BLUR, taille, taille, 0, 0);
      return image;
    case BLUR_NS:
      cvSmooth(image, image, CV_BLUR, taille, taille, 0, 0);
      return image;
    case GAUSSIAN_TROIS:
      cvSmooth(image, image, CV_GAUSSIAN, taille, taille, 3, 0);
      return image;
    case GAUSSIAN_CINQ:
      cvSmooth(image, image, CV_GAUSSIAN, taille, taille, 5, 0);
      return image;
    case MEDIAN:
      dest = cvCreateImage(cvSize(width, height), depth, channels);
      cvSmooth(image, dest, CV_MEDIAN, taille, taille, 0, 0);
      return dest;
    case BILATERAL:
      dest = cvCreateImage(cvSize(width, height), depth, channels);
      cvSmooth(image, dest, CV_BILATERAL, taille, taille, 3, 3);
      return dest;
  }
  return NULL;
}

void Ui_MainWindow::timerEvent(QTimerEvent*){
  int i, count, taille;
  /* THAT SUCKS ! But I don't get how opencv manages memory */
  bool should_free = false;
  /* END OF MAJOR SUCKINESS */
  type_filtre filter;
  QString type, param;
  QListWidgetItem* item_i;
  count = listWidget->count();
  IplImage* image = cvQueryFrame(source);
  if (!image) {
    stop_playback();
    return;
  }
  if (image->width != width
      || image-> height != height 
      || image->nChannels != channels
      || image->depth != depth ) {
    width = image->width;
    height = image->height;
    channels = image->nChannels;
    depth = image->depth;
    cvwidget->setGeometry(QRect(19, 13, width, height));
    resize(360+width, 20+height);
    listWidget->setGeometry(QRect(50+width, 0, 250, 130));
    label_2->setGeometry(QRect(60+width, 195, 56, 17));
    label_6->setGeometry(QRect(60+width, 156, 56, 17));
    comboBox_4->setGeometry(QRect(110+width, 150, 175, 26));
    buttonBox_2->setGeometry(QRect(80+width, 230, 180, 32));
    comboBox->setGeometry(QRect(110+width, 190, 175, 26));
    menubar->setGeometry(QRect(0, 0, 360+width, 25));
  }

  for(i = 0; i < count; i++) {
    item_i = listWidget->item(i);
    if (item_i->text() != "Nouveau") {
      type = item_i->text().section(" ", 0, 0);
      filter = filter_of_id(type);
      if (MEDIAN == filter || BILATERAL == filter)
        should_free = true;
      param = item_i->text().section(" ", 1, 1);
      taille = param.at(0).digitValue();
      image = apply_filter(image, filter_of_id(type), taille);
    }
  }
  cvwidget->putImage(image);
  if (should_free)
    cvReleaseImage(&image);
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

void Ui_MainWindow::stop_playback() {
  killTimer(timer_id);
  cvReleaseCapture(&source);
}

void Ui_MainWindow::setupUi(QMainWindow *MainWindow) {
  if (MainWindow->objectName().isEmpty())
    MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
  MainWindow->resize(1000,500);
  actionQuitter = new QAction(MainWindow);
  actionQuitter->setObjectName(QString::fromUtf8("actionQuitter"));
  actionFichier = new QAction(MainWindow);
  actionFichier->setObjectName(QString::fromUtf8("actionFichier"));
  actionWebcam = new QAction(MainWindow);
  actionWebcam->setObjectName(QString::fromUtf8("actionWebcam"));
  centralwidget = new QWidget(MainWindow);
  centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
  listWidget = new QListWidget(centralwidget);
  new QListWidgetItem(listWidget);
  listWidget->setObjectName(QString::fromUtf8("listWidget"));
  listWidget->setGeometry(QRect(690, 0, 250, 130));
  listWidget->setDragDropMode(QAbstractItemView::InternalMove);
  cvwidget = new QOpenCVWidget(this);
  cvwidget->setObjectName(QString::fromUtf8("cvwidget"));
  cvwidget->setGeometry(QRect(19, 13, 640, 480));
  label_2 = new QLabel(centralwidget);
  label_2->setObjectName(QString::fromUtf8("label_2"));
  label_2->setGeometry(QRect(700, 195, 56, 17));
  label_6 = new QLabel(centralwidget);
  label_6->setObjectName(QString::fromUtf8("label_6"));
  label_6->setGeometry(QRect(700, 156, 56, 17));
  comboBox_4 = new QComboBox(centralwidget);
  comboBox_4->setObjectName(QString::fromUtf8("comboBox_4"));
  comboBox_4->setGeometry(QRect(750, 150, 175, 26));
  buttonBox_2 = new QDialogButtonBox(centralwidget);
  buttonBox_2->setObjectName(QString::fromUtf8("buttonBox_2"));
  buttonBox_2->setGeometry(QRect(720, 230, 180, 32));
  apply_button = new QPushButton(tr("Appliquer"));
  delete_button = new QPushButton(tr("Supprimer"));
  buttonBox_2->addButton(apply_button, QDialogButtonBox::AcceptRole);
  buttonBox_2->addButton(delete_button, QDialogButtonBox::RejectRole);
  comboBox = new QComboBox(centralwidget);
  comboBox->setObjectName(QString::fromUtf8("comboBox"));
  comboBox->setGeometry(QRect(750, 190, 175, 26));
  MainWindow->setCentralWidget(centralwidget);
  menubar = new QMenuBar(MainWindow);
  menubar->setObjectName(QString::fromUtf8("menubar"));
  menubar->setGeometry(QRect(0, 0, 540, 25));
  menuFichier = new QMenu(menubar);
  menuFichier->setObjectName(QString::fromUtf8("menuFichier"));
  menuOuvrir = new QMenu(menuFichier);
  menuOuvrir->setObjectName(QString::fromUtf8("menuOuvrir"));
  MainWindow->setMenuBar(menubar);
  statusbar = new QStatusBar(MainWindow);
  statusbar->setObjectName(QString::fromUtf8("statusbar"));
  MainWindow->setStatusBar(statusbar);

  menubar->addAction(menuFichier->menuAction());
  menuFichier->addAction(menuOuvrir->menuAction());
  menuFichier->addAction(actionQuitter);
  menuOuvrir->addAction(actionFichier);
  menuOuvrir->addAction(actionWebcam);

  retranslateUi(MainWindow);
  QObject::connect(actionQuitter, SIGNAL(triggered()), MainWindow, SLOT(close()));
  QObject::connect(actionFichier, SIGNAL(triggered()), MainWindow, SLOT(select_file()));
  QObject::connect(buttonBox_2, SIGNAL(accepted()), MainWindow, SLOT(apply_changes()));
  QObject::connect(buttonBox_2, SIGNAL(rejected()), MainWindow, SLOT(delete_filter()));
  QObject::connect(actionWebcam, SIGNAL(triggered()), MainWindow, SLOT(select_camera()));

  QMetaObject::connectSlotsByName(MainWindow);
}

void Ui_MainWindow::retranslateUi(QMainWindow *MainWindow) {
  MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
  actionQuitter->setText(QApplication::translate("MainWindow", "Quitter", 0, QApplication::UnicodeUTF8));
  actionFichier->setText(QApplication::translate("MainWindow", "Fichier", 0, QApplication::UnicodeUTF8));
  actionWebcam->setText(QApplication::translate("MainWindow", "Webcam", 0, QApplication::UnicodeUTF8));

  const bool __sortingEnabled = listWidget->isSortingEnabled();
  listWidget->item(0)->setText(QApplication::translate("MainWindow", "Nouveau", 0, QApplication::UnicodeUTF8));
  listWidget->setCurrentItem(listWidget->item(0));
  listWidget->setSortingEnabled(false);

  listWidget->setSortingEnabled(__sortingEnabled);
  label_2->setText(QApplication::translate("MainWindow", "Taille", 0, QApplication::UnicodeUTF8));
  label_6->setText(QApplication::translate("MainWindow", "Type", 0, QApplication::UnicodeUTF8));
  comboBox_4->clear();
  comboBox_4->insertItems(0, QStringList()
      << QApplication::translate("MainWindow", "BLUR", 0, QApplication::UnicodeUTF8)
      << QApplication::translate("MainWindow", "BLUR_NS", 0, QApplication::UnicodeUTF8)
      << QApplication::translate("MainWindow", "GAUSSIAN_TROIS", 0, QApplication::UnicodeUTF8)
      << QApplication::translate("MainWindow", "GAUSSIAN_CINQ", 0, QApplication::UnicodeUTF8)
      << QApplication::translate("MainWindow", "MEDIAN", 0, QApplication::UnicodeUTF8)
      << QApplication::translate("MainWindow", "BILATERAL", 0, QApplication::UnicodeUTF8)
      );
  comboBox->clear();
  comboBox->insertItems(0, QStringList()
      << QApplication::translate("MainWindow", "3x3", 0, QApplication::UnicodeUTF8)
      << QApplication::translate("MainWindow", "5x5", 0, QApplication::UnicodeUTF8)
      << QApplication::translate("MainWindow", "7x7", 0, QApplication::UnicodeUTF8)
      << QApplication::translate("MainWindow", "9x9", 0, QApplication::UnicodeUTF8)
      );
  menuFichier->setTitle(QApplication::translate("MainWindow", "Fichier", 0, QApplication::UnicodeUTF8));
  menuOuvrir->setTitle(QApplication::translate("MainWindow", "Ouvrir", 0, QApplication::UnicodeUTF8));
}


