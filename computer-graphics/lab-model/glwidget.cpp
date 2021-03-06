#include "glwidget.h"
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLPaintDevice>
#include <GL/glu.h>
#include <QKeyEvent>
#include <iostream>
#include <QOpenGLWindow>

GLWidget::GLWidget(QWidget *parent):QGLWidget(parent) {
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
    installEventFilter(this);
}

void GLWidget::initializeGL()
{

    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    gluPerspective(60.0, (GLfloat) width() / (GLfloat) height(), 0.01, 50.0);
    gluLookAt(cam.eye.x, cam.eye.y, cam.eye.z, cam.view.x, cam.view.y, cam.view.z, cam.up.x, cam.up.y, cam.up.z);

    glPolygonMode(polygonFace, polygonMode);
    drawFloor();
    latim.draw();

}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void GLWidget::drawFloor()
{
    int size = 30;
    for(float i = -size; i <= size; i += 5) {
          glBegin(GL_QUADS);
              glColor3ub(214, 198, 188);
              glVertex3f(-size, 0, i);
              glVertex3f(size, 0, i);
              glVertex3f(i, 0,-size);
              glVertex3f(i, 0, size);
          glEnd();
      }
}

void GLWidget::keyPressEvent(QKeyEvent *e)
{
    switch(e->key()) {
    case Qt::Key_A:
    case Qt::Key_Left:
        cam.moveSideways(-1);
        break;
    case Qt::Key_D:
    case Qt::Key_Right:
        cam.moveSideways(1);
        break;
    case Qt::Key_S:
    case Qt::Key_Down:
        cam.moveCamera(-1);
        break;
    case Qt::Key_W:
    case Qt::Key_Up:
        cam.moveCamera(1);
        break;
    case Qt::Key_F1:
        //FILL FRONT_AND_BACK
        polygonFace = GL_FRONT_AND_BACK;
        polygonMode = GL_FILL;
        break;
    case Qt::Key_F2:
        //LINE FRONT_AND_BACK
        polygonFace = GL_FRONT_AND_BACK;
        polygonMode = GL_LINE;
        break;
    case Qt::Key_F3:
        //LINE FRONT_AND_BACK
        polygonFace = GL_FRONT;
        polygonMode = GL_FILL;
        break;
    case Qt::Key_F4:
        //LINE FRONT_AND_BACK
        polygonFace = GL_BACK;
        polygonMode = GL_FILL;
        break;
    default:
        e->ignore();
    }

    update();
}

void GLWidget::mouseMoveEvent(QMouseEvent *e)
{
    int x = e->x();
    int y = e->y();
    //std::cout << "X: " << x << " Y: " << y << std::endl;
    cam.moveMouse(x, y, width(), height());

    update();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        latim.moveDoor();
    }

    update();
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    cam.moveUp(event->delta()/120);
    update();
}

