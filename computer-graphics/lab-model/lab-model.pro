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
    camera.cpp \
    latimmodel.cpp

HEADERS  += window.h \
    glwidget.h \
    camera.h \
    latimmodel.h

FORMS    += window.ui

win32|win64 {
    LIBS += -m32 -lglut -lopengl32 -lGlu32 -lm
}

unix {
    LIBS += -lglut -lGL -lGLU -lm
}
