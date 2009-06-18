#include "ui_pix_hell.h"

Ui_MainWindow::Ui_MainWindow(QWidget* parent) : QMainWindow(parent) {
  default_image_path = "star-wars-darth-vader-sense.jpg";
}

Ui::MainWindow::MainWindow(QWidget* parent) : Ui_MainWindow(parent) {}

/** Permet de choisir le fichier à lire, et déclenche la lecture */
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

/** Permet de lire depuis une webcam et déclenche la lecture */
void Ui_MainWindow::select_camera () {
  source = cvCreateCameraCapture(0);
  assert(source);
  timer_id = startTimer(40);
  return;
}

/** Applique un filtre à l'image, en évitant les allocations non nécessaires */
/*
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
*/
/** Redimensionne la fenêtre en fonction des attributs width et height */
void Ui_MainWindow::fit_window() {
  resize(360+width, 44+height);
  cvwidget->setGeometry(QRect(21, 17, 21+width, 18+height));
  filter_list->setGeometry(QRect(50+width, 0, 250, 130));
  label_2->setGeometry(QRect(60+width, 195, 56, 17));
  label_6->setGeometry(QRect(60+width, 156, 56, 17));
  comboBox_4->setGeometry(QRect(110+width, 150, 175, 26));
  buttonBox_2->setGeometry(QRect(80+width, 230, 180, 32));
  comboBox->setGeometry(QRect(110+width, 190, 175, 26));
  menubar->setGeometry(QRect(0, 0, 360+width, 25));
}

/** Joue la vidéo à intervalle fixe */
void Ui_MainWindow::timerEvent(QTimerEvent*){
  /* THAT SUCKS ! But I don't get how opencv manages memory */
  bool should_free = false;
  /* END OF MAJOR SUCKINESS */
  QString type, param;
  current_image = cvQueryFrame(source);
  if (!current_image) {
    stop_playback();
    return;
  }

  update_image_infos();
  fit_window();

  /* FIXME */
  QModelIndex index;
  QModelIndexList items = filter_list_selection_model->selectedIndexes();

  foreach (index, items) {
    QString text = QString("a");
    filter_list_model->setData(index, text);
  }

  cvwidget->putImage(current_image);
  if (should_free)
    cvReleaseImage(&current_image);
  return;
}

/** Met à jour la liste de filtre quand l'utilisateur clique sur "Appliquer" */
void Ui_MainWindow::apply_changes () {
  QModelIndex selected = filter_list_selection_model->selectedIndexes()[0];
  return;
}

/** Supprime le filtre sélectionné par l'utilisateur */
void Ui_MainWindow::delete_filter () {
  filter_list_selection_model->selectedIndexes()[0].~QModelIndex();
  return;
}

/** Arrête la lecture d'une vidéo et embraye sur Darth Vador */
void Ui_MainWindow::stop_playback() {
  killTimer(timer_id);
  cvReleaseCapture(&source);
  may_the_force_be_with_you();
}

/** Met à jour les infos sur l'image : width, height, channels, depth */
void Ui_MainWindow::update_image_infos() {
  width = current_image->width;
  height = current_image->height;
  channels = current_image->nChannels;
  depth = current_image->depth;
}

/** Affiche l'image de Darth Vader */
void Ui_MainWindow::may_the_force_be_with_you() {
  current_image = cvLoadImage(default_image_path);
  update_image_infos();
  fit_window();
  cvwidget->putImage(current_image);
  fit_window();
}

/** Crée l'interface : boutons, intitulés, menus... */
void Ui_MainWindow::setupUi(QMainWindow *MainWindow) {
  if (MainWindow->objectName().isEmpty())
    MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
  actionQuitter = new QAction(MainWindow);
  actionQuitter->setObjectName(QString::fromUtf8("actionQuitter"));
  actionFichier = new QAction(MainWindow);
  actionFichier->setObjectName(QString::fromUtf8("actionFichier"));
  actionWebcam = new QAction(MainWindow);
  actionWebcam->setObjectName(QString::fromUtf8("actionWebcam"));
  centralwidget = new QWidget(MainWindow);
  centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
  filter_list_model = new FilterListModel(centralwidget);
  filter_list = new QListView;
  filter_list->setModel(filter_list_model);
  QListWidget* t = new QListWidget(0);
  filter_list_selection_model = t->selectionModel();
  delete t;
  /*
  new QListWidgetItem(listWidget);
  listWidget->setObjectName(QString::fromUtf8("listWidget"));
  listWidget->setDragDropMode(QAbstractItemView::InternalMove); 
  */
  cvwidget = new QOpenCVWidget(this);
  cvwidget->setObjectName(QString::fromUtf8("cvwidget"));
  label_2 = new QLabel(centralwidget);
  label_2->setObjectName(QString::fromUtf8("label_2"));
  label_6 = new QLabel(centralwidget);
  label_6->setObjectName(QString::fromUtf8("label_6"));
  comboBox_4 = new QComboBox(centralwidget);
  comboBox_4->setObjectName(QString::fromUtf8("comboBox_4"));
  buttonBox_2 = new QDialogButtonBox(centralwidget);
  buttonBox_2->setObjectName(QString::fromUtf8("buttonBox_2"));
  apply_button = new QPushButton(tr("Appliquer"));
  delete_button = new QPushButton(tr("Supprimer"));
  buttonBox_2->addButton(apply_button, QDialogButtonBox::AcceptRole);
  buttonBox_2->addButton(delete_button, QDialogButtonBox::RejectRole);
  comboBox = new QComboBox(centralwidget);
  comboBox->setObjectName(QString::fromUtf8("comboBox"));
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

  may_the_force_be_with_you();

  retranslateUi(MainWindow);
  QObject::connect(actionQuitter, SIGNAL(triggered()), MainWindow, SLOT(close()));
  QObject::connect(actionFichier, SIGNAL(triggered()), MainWindow, SLOT(select_file()));
  QObject::connect(buttonBox_2, SIGNAL(accepted()), MainWindow, SLOT(apply_changes()));
  QObject::connect(buttonBox_2, SIGNAL(rejected()), MainWindow, SLOT(delete_filter()));
  QObject::connect(actionWebcam, SIGNAL(triggered()), MainWindow, SLOT(select_camera()));

  QMetaObject::connectSlotsByName(MainWindow);
}

/** Traduit l'interface */
void Ui_MainWindow::retranslateUi(QMainWindow *MainWindow) {
  MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
  actionQuitter->setText(QApplication::translate("MainWindow", "Quitter", 0, QApplication::UnicodeUTF8));
  actionFichier->setText(QApplication::translate("MainWindow", "Fichier", 0, QApplication::UnicodeUTF8));
  actionWebcam->setText(QApplication::translate("MainWindow", "Webcam", 0, QApplication::UnicodeUTF8));

  /* const bool __sortingEnabled = listWidget->isSortingEnabled(); */
  /* listWidget->item(0)->setText(QApplication::translate("MainWindow", "Nouveau", 0, QApplication::UnicodeUTF8));
  listWidget->setCurrentItem(listWidget->item(0));
  listWidget->setSortingEnabled(false);

  listWidget->setSortingEnabled(__sortingEnabled); */
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

getter<int>::getter(int min, int incr, int max, int n) {
  widget = new QSpinBox();
  widget->setMinimum(min);
  widget->setSingleStep(incr);
  widget->setMaximum(max);
  widget->setGeometry(QRect(10, 20 + 30*n, 91, 27));
}

int getter<int>::get() {
  return widget->value();
}

getter<double>::getter(double min, double incr, double max, int n) {
  widget = new QDoubleSpinBox();
  widget->setMinimum(min);
  widget->setSingleStep(incr);
  widget->setMaximum(max);
  widget->setGeometry(QRect(10, 20 + 30*n, 91, 27));
}

double getter<double>::get() {
  return widget->value();
}

template <class type1, class type2, class type3, class type4, class type5>
void fn<type1, type2, type3, type4, type5>::applique(IplImage* src, IplImage* dst) {
  switch(n) {
    case 1:
      f1(src, dst, getter1->get());
      break;
    case 2:
      f2(src, dst, getter1->get(), getter2->get());
      break;
    case 3:
      f3(src, dst, getter1->get(), getter2->get(), getter3->get());
      break;
    case 4:
      f4(src, dst, getter1->get(), getter2->get(), getter3->get(), getter4->get());
      break;
    case 5:
      f5(src, dst, getter1->get(), getter2->get(), getter3->get(), getter4->get(), getter5->get());
      break;
  }
  return;
}

template <class type1, class type2, class type3, class type4, class type5>
fn<type1, type2, type3, type4, type5>::fn(char* name_, void* f_, type1 min1, type1 step1, type1 max1) {
  name = name_;
  f1 = (void (*)(IplImage*, IplImage*, type1))f_;
  n = 1;
  getter1 = new getter<type1>(min1, step1, max1, 1);
}

template <class type1, class type2, class type3, class type4, class type5>
fn<type1, type2, type3, type4, type5>::fn(char* name_, void* f_, type1 min1, type1 step1, type1 max1, type2 min2, type2 step2, type2 max2) {
  name = name_;
  f2 = (void (*)(IplImage*, IplImage*, type1, type2))f_;
  n = 2;
  getter1 = new getter<type1>(min1, step1, max1, 1);
  getter2 = new getter<type2>(min2, step2, max2, 2);
}

template <class type1, class type2, class type3, class type4, class type5>
fn<type1, type2, type3, type4, type5>::fn(char* name_, void* f_, type1 min1, type1 step1, type1 max1, type2 min2, type2 step2, type2 max2, type3 min3, type3 step3, type3 max3) {
  name = name_;
  f3 = (void (*)(IplImage*, IplImage*, type1, type2, type3))f_;
  n = 3;
  getter1 = new getter<type1>(min1, step1, max1, 1);
  getter2 = new getter<type2>(min2, step2, max2, 2);
  getter3 = new getter<type3>(min3, step3, max3, 3);
}

template <class type1, class type2, class type3, class type4, class type5>
fn<type1, type2, type3, type4, type5>::fn(char* name_, void* f_, type1 min1, type1 step1, type1 max1, type2 min2, type2 step2, type2 max2, type3 min3, type3 step3, type3 max3, type4 min4, type4 step4, type4 max4) {
  name = name_;
  f4 = (void (*)(IplImage*, IplImage*, type1, type2, type3, type4))f_;
  n = 4;
  getter1 = new getter<type1>(min1, step1, max1, 1);
  getter2 = new getter<type2>(min2, step2, max2, 2);
  getter3 = new getter<type3>(min3, step3, max3, 3);
  getter4 = new getter<type4>(min4, step4, max4, 4);
}
template <class type1, class type2, class type3, class type4, class type5>
fn<type1, type2, type3, type4, type5>::fn(char* name_, void* f_, type1 min1, type1 step1, type1 max1, type2 min2, type2 step2, type2 max2, type3 min3, type3 step3, type3 max3, type4 min4, type4 step4, type4 max4, type5 min5, type5 step5, type5 max5) {
  name = name_;
  f5 = (void (*)(IplImage*, IplImage*, type1, type2, type3, type4, type5))f_;
  n = 5;
  getter1 = new getter<type1>(min1, step1, max1, 1);
  getter2 = new getter<type2>(min2, step2, max2, 2);
  getter3 = new getter<type3>(min3, step3, max3, 3);
  getter4 = new getter<type4>(min4, step4, max4, 4);
  getter5 = new getter<type5>(min5, step5, max5, 5);
}

int FilterListModel::rowCount(const QModelIndex &parent) const {
  return filters.count();
}

QVariant FilterListModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();
  if (index.row() >= filters.size())
    return QVariant();
  if (role == Qt::DisplayRole)
    return filters.at(index.row());
  else
    return QVariant();
}


void g(void*, void*, int a, int b, int c) {
  printf("%d ; %d ; %d\n", a, b, c);
  return;
}

void i(void*, void*, int a, int b) {
  printf("%d ; %d\n", a, b);
  return;
}

void a() {
  void* h = (void*) &g;
  void* j = (void*) &i;
  fn<int,int,int,int,int>* b = new fn<int,int,int,int,int>("a", &h, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  fn<int,int,int,int,int>* c = new fn<int,int,int,int,int>("a", &j, 0, 0, 0, 0, 0, 0);
  b->applique(NULL, NULL);
  c->applique(NULL, NULL);
}

