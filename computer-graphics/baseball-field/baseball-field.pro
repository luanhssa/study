QT += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4) QT += widgets

TARGET = baseball-field
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    window.cpp \
    glwidget.cpp

HEADERS += \
    window.h \
    glwidget.h

FORMS += window.ui

LIBS += -lglut -lGL -lGLU -lm
