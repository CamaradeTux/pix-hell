#ifdef AAA
#include "MyCameraWindow.h"

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
} taille;

typedef struct filtre {
  type_filtre type_du_filtre;
  taille taille;
} filtre;

MyCameraWindow::MyCameraWindow(CvCapture *cam, QWidget *parent) : QWidget(parent) {
    camera = cam;
    QVBoxLayout *layout = new QVBoxLayout;
    cvwidget = new QOpenCVWidget(this);
    layout->addWidget(cvwidget);
    setLayout(layout);
    resize(500, 400);

    startTimer(100);  // 0.1-second timer
 }

void MyCameraWindow::timerEvent(QTimerEvent*) {

    IplImage *image=cvQueryFrame(camera);
}

// change le type de filtre : a lier aux checkboxes
/* void MyCameraWindow::changeType(QMouseEvent* event) {
*/ 
// change le fichier a lire

// change les params pour un parametre de filtre, un a la fois
#endif
