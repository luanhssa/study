#-------------------------------------------------
#
# Project created by QtCreator 2016-09-03T02:05:12
#
#-------------------------------------------------

QT += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab-model
TEMPLATE = app


SOURCES += main.cpp\
        window.cpp \
    glwidget.cpp \
    camera.cpp

HEADERS  += window.h \
    glwidget.h \
    camera.h

FORMS    += window.ui

LIBS += -lglut -lGL -lGLU -lm
