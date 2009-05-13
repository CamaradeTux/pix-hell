
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

filtre blur_ns, blur, gaussian, median, bilateral;

MyCameraWindow::MyCameraWindow(CvCapture *cam, QWidget *parent) : QWidget(parent) {
    blur.enabled = false;
    blur_ns.enabled = false;
    gaussian.enabled = false;
    median.enabled = false;
    bilateral.enabled = false;

    camera = cam;
    QVBoxLayout *layout = new QVBoxLayout;
    cvwidget = new QOpenCVWidget(this);
    layout->addWidget(cvwidget);
    setLayout(layout);
    resize(500, 400);

    startTimer(100);  // 0.1-second timer
 }

void MyCameraWindow::timerEvent(QTimerEvent*) {

blur_ns.enabled = true;
blur_ns.param1 = 5;
blur_ns.param2 = 5;

gaussian.enabled = true;
gaussian.param1 = 9;
gaussian.param2 = 9;

    IplImage *image=cvQueryFrame(camera);
    if (blur_ns.enabled)
        cvSmooth(image, image, CV_BLUR_NO_SCALE, blur_ns.param1, blur_ns.param2, blur_ns.param3);
    if (blur.enabled)
        cvSmooth(image, image, CV_BLUR, blur.param1, blur.param2, blur.param3);
    if (gaussian.enabled)
        cvSmooth(image, image, CV_GAUSSIAN, gaussian.param1, gaussian.param2, gaussian.param3);
    if (median.enabled)
        cvSmooth(image, image, CV_MEDIAN, median.param1, median.param2, median.param3);
    if (bilateral.enabled)
        cvSmooth(image, image, CV_BILATERAL, bilateral.param1, bilateral.param2, bilateral.param3);
    cvwidget->putImage(image);
}

// change le type de filtre : a lier aux checkboxes
/* void MyCameraWindow::changeType(QMouseEvent* event) {
*/ 
// change le fichier a lire

// change les params pour un parametre de filtre, un a la fois
