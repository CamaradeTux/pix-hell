#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include <assert.h>
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include "QOpenCVWidget.h"
#include "MyCameraWindow.h"

/* int type = -1, param1, param2, param3; */

/*
int type = CV_GAUSSIAN;
int param1 = 9;
int param2 = 9;
int param3 = 90;
*/

int main(int argc, char **argv) {
    CvCapture * camera = cvCreateCameraCapture(0);
    assert(camera);
    IplImage * image=cvQueryFrame(camera);
    assert(image);

    printf("Image depth=%i\n", image->depth);
    printf("Image nChannels=%i\n", image->nChannels);

    QApplication app(argc, argv);
    MyCameraWindow *mainWin = new MyCameraWindow(camera);
    mainWin->setWindowTitle("OpenCV --> QtImage");
    mainWin->show();    
    int retval = app.exec();
    
    cvReleaseCapture(&camera);
    
    return retval;
}

