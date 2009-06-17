/********************************************************************************
** Form generated from reading ui file 'pix_hellmn1970.ui'
**
** Created: Wed May 13 22:12:16 2009
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef PIX_HELLMN1970_H
#define PIX_HELLMN1970_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDial>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

#include <QTextStream>
#include <QPushButton>
#include <QFileDialog>
#include <QSpinBox>

#include "QOpenCVWidget.h"
#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>

typedef enum type_filtre {
  BLUR,
  BLUR_NS,
  GAUSSIAN_TROIS,
  GAUSSIAN_CINQ,
  MEDIAN,
  BILATERAL
} type_filtre;

typedef enum taille {
  TROIS = 3,
  CINQ = 5,
  SEPT = 7,
  NEUF = 9
} taille_;

typedef struct filtre {
  type_filtre type_du_filtre;
  taille_ taille;
} filtre;

class Ui_MainWindow : public QMainWindow {
  Q_OBJECT
  public:
    QAction *actionQuitter;
    QAction *actionFichier;
    QAction *actionWebcam;
    QWidget *centralwidget;
    QListView *listView;
    QLabel *label_2;
    QLabel *label_6;
    QComboBox *comboBox_4;
    QDialogButtonBox *buttonBox_2;
    QComboBox *comboBox;
    QMenuBar *menubar;
    QMenu *menuFichier;
    QMenu *menuOuvrir;
    QStatusBar *statusbar;

    QPushButton* apply_button;
    QPushButton* delete_button;

    QOpenCVWidget* cvwidget;
    CvCapture* source;
    IplImage* current_image;

    const char* default_image_path;
    void may_the_force_be_with_you();

    void update_image_infos();
    void fit_window();
    void setupUi(QMainWindow* MainWindow);
    void retranslateUi(QMainWindow* MainWindow);
   
    Ui_MainWindow(QWidget* parent);

    void timerEvent(QTimerEvent*);
    IplImage* apply_filter(IplImage*, type_filtre, int);

    int timer_id;
    int width;
    int height;
    int depth;
    int channels;

  public slots:
    void select_camera();
    void select_file();
    void apply_changes();
    void delete_filter();
    void stop_playback();

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {
      public:
        MainWindow(QWidget* parent);
    };
} // namespace Ui


template <class type>
class getter {
  protected:
    QAbstractSpinBox* widget;
  public:
    getter(type, type, type, int);
    virtual type get_value();
};

template <>
class getter<int> {
  protected:
    QSpinBox* widget;
  public:
    getter(int, int, int, int);
    int get_value();
};

template <>
class getter<double> {
  protected:
    QDoubleSpinBox* widget;
  public:
    getter(double, double, double, int);
    double get_value();
};

template <>
class getter<void> {};

template <class type1, class type2, class type3, class type4, class type5>
class fn {
  protected:
    getter<type1>* getter1();
    getter<type2>* getter2();
    getter<type3>* getter3();
    getter<type4>* getter4();
    getter<type5>* getter5();
    void* f;
    char* name;
    int n;
  public:
    fn(char* name_, void* f_, int n_ );
    void applique(IplImage* src, IplImage* dst);
};

#endif // PIX_HELLMN1970_H
