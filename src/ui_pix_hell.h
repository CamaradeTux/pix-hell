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
#include <QAbstractListModel>
#include <QSpinBox>

#include "QOpenCVWidget.h"
#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>

class FilterListModel : public QAbstractListModel {
  Q_OBJECT
  public:
    FilterListModel(QObject *parent = 0) : QAbstractListModel(parent) {};
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
  private:
    QStringList filters;
};

class Ui_MainWindow : public QMainWindow {
  Q_OBJECT
  public:
    QAction *actionQuitter;
    QAction *actionFichier;
    QAction *actionWebcam;
    QWidget *centralwidget;
    QAbstractListModel* filter_list_model;
    QListView* filter_list;
    QItemSelectionModel* filter_list_selection_model;
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
    int get();
};

template <>
class getter<double> {
  protected:
    QDoubleSpinBox* widget;
  public:
    getter(double, double, double, int);
    double get();
};

template <>
class getter<char> {};

template <class type1, class type2, class type3, class type4, class type5>
class fn {
  protected:
    getter<type1>* getter1;
    getter<type2>* getter2;
    getter<type3>* getter3;
    getter<type4>* getter4;
    getter<type5>* getter5;
    void (*f1)(const IplImage*, IplImage*, type1);
    void (*f2)(const IplImage*, IplImage*, type1, type2);
    void (*f3)(const IplImage*, IplImage*, type1, type2, type3);
    void (*f4)(const IplImage*, IplImage*, type1, type2, type3, type4);
    void (*f5)(const IplImage*, IplImage*, type1, type2, type3, type4, type5);
    char* name;
    int n;
  public:
    fn(char* name_, void* f_, type1, type1, type1);
    fn(char* name_, void* f_, type1, type1, type1, type2, type2, type2);
    fn(char* name_, void* f_, type1, type1, type1, type2, type2, type2, type3, type3, type3);
    fn(char* name_, void* f_, type1, type1, type1, type2, type2, type2, type3, type3, type3, type4, type4, type4);
    fn(char* name_, void* f_, type1, type1, type1, type2, type2, type2, type3, type3, type3, type4, type4, type4, type5, type5, type5);
    void applique(const IplImage* src, IplImage* dst);
};

void a();
#endif // PIX_HELLMN1970_H
