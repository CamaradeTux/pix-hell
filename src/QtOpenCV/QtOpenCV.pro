TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .
LIBS += -lcv -lhighgui
CONFIG += debug

# Input
HEADERS += QOpenCVWidget.h ui_pix_hell.h
SOURCES += main.cpp QOpenCVWidget.cpp ui_pix_hell.cpp
