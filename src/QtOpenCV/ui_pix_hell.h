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

#include "QOpenCVWidget.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>

class Ui_MainWindow : public QMainWindow {
  Q_OBJECT
  public:
    QAction *actionQuitter;
    QAction *actionFichier;
    QAction *actionWebcam;
    QWidget *centralwidget;
    QListWidget *listWidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_6;
    QComboBox *comboBox_4;
    QDialogButtonBox *buttonBox_2;
    QComboBox *comboBox;
    QMenuBar *menubar;
    QMenu *menuFichier;
    QMenu *menuOuvrir;
    QStatusBar *statusbar;

    QOpenCVWidget* cvwidget;
    CvCapture* source;

    void setupUi(QMainWindow *MainWindow)
    {
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
    new QListWidgetItem(listWidget);
    new QListWidgetItem(listWidget);
    listWidget->setObjectName(QString::fromUtf8("listWidget"));
    listWidget->setGeometry(QRect(690, 0, 250, 130));
    listWidget->setDragDropMode(QAbstractItemView::InternalMove);
    cvwidget = new QOpenCVWidget(this);
    cvwidget->setObjectName(QString::fromUtf8("cvwidget"));
    cvwidget->setGeometry(QRect(19, 13, 640, 480));
    label = new QLabel(centralwidget);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(730, 140, 101, 17));
    label_2 = new QLabel(centralwidget);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setGeometry(QRect(750, 190, 56, 17));
    label_6 = new QLabel(centralwidget);
    label_6->setObjectName(QString::fromUtf8("label_6"));
    label_6->setGeometry(QRect(750, 160, 56, 17));
    comboBox_4 = new QComboBox(centralwidget);
    comboBox_4->setObjectName(QString::fromUtf8("comboBox_4"));
    comboBox_4->setGeometry(QRect(820, 150, 150, 26));
    buttonBox_2 = new QDialogButtonBox(centralwidget);
    buttonBox_2->setObjectName(QString::fromUtf8("buttonBox_2"));
    buttonBox_2->setGeometry(QRect(760, 230, 180, 32));
    buttonBox_2->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    comboBox = new QComboBox(centralwidget);
    comboBox->setObjectName(QString::fromUtf8("comboBox"));
    comboBox->setGeometry(QRect(820, 190, 150, 26));
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
    QObject::connect(actionFichier, SIGNAL(triggered()), MainWindow, SLOT(new_file_source()));
    QObject::connect(buttonBox_2, SIGNAL(accepted()), MainWindow, SLOT(apply_changes()));
    QObject::connect(buttonBox_2, SIGNAL(rejected()), MainWindow, SLOT(discard_changes()));

    QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
    MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
    actionQuitter->setText(QApplication::translate("MainWindow", "Quitter", 0, QApplication::UnicodeUTF8));
    actionFichier->setText(QApplication::translate("MainWindow", "Fichier", 0, QApplication::UnicodeUTF8));
    actionWebcam->setText(QApplication::translate("MainWindow", "Webcam", 0, QApplication::UnicodeUTF8));

    const bool __sortingEnabled = listWidget->isSortingEnabled();
    listWidget->setSortingEnabled(false);
    listWidget->item(0)->setText(QApplication::translate("MainWindow", "Filtre 1 (param1, param2, param3)", 0, QApplication::UnicodeUTF8));
    listWidget->item(1)->setText(QApplication::translate("MainWindow", "Filtre 2", 0, QApplication::UnicodeUTF8));
    listWidget->item(2)->setText(QApplication::translate("MainWindow", "Nouveau", 0, QApplication::UnicodeUTF8));

    listWidget->setSortingEnabled(__sortingEnabled);
    label->setText(QApplication::translate("MainWindow", "Filtre 1", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("MainWindow", "Taille", 0, QApplication::UnicodeUTF8));
    label_6->setText(QApplication::translate("MainWindow", "Type", 0, QApplication::UnicodeUTF8));
    comboBox_4->clear();
    comboBox_4->insertItems(0, QStringList()
     << QApplication::translate("MainWindow", "BLUR", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("MainWindow", "BLUR_NS", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("MainWindow", "GAUSSIAN", 0, QApplication::UnicodeUTF8)
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
    } // retranslateUi
    
    void setSource(CvCapture* _source) { source = _source; return; };

    Ui_MainWindow(QWidget* parent);

    void timerEvent(QTimerEvent*);

  public slots:
    void new_camera_source();
    void new_file_source();
    void apply_changes();
    void discard_changes();

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {
      public:
        MainWindow(QWidget* parent);
    };
} // namespace Ui


typedef enum type_filtre {
  BLUR,
  BLUR_NS,
  GAUSSIAN_TROIS,
  GAUSSIAN_CINQ,
  MEDIAN,
  BILATERAL
} type_filtre;

typedef enum taille_ {
  TROIS = 3,
  CINQ = 5,
  SEPT = 7,
  NEUF = 9
} taille;

typedef struct filtre {
  type_filtre type_du_filtre;
  taille_ taille;
} filtre;

#endif // PIX_HELLMN1970_H