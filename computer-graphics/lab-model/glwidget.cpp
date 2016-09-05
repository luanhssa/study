#include "glwidget.h"
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLPaintDevice>
#include <GL/glut.h>
#include <QKeyEvent>
#include <iostream>

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


    gluPerspective(60.0, (GLfloat) width() / (GLfloat) height(), 0.1, 50.0);
    gluLookAt(cam.eye.x, cam.eye.y, cam.eye.z, cam.view.x, cam.view.y, cam.view.z, cam.up.x, cam.up.y, cam.up.z);

    drawFloor();
    //drawTriangle();
    drawLaTIM();

    swapBuffers();
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void GLWidget::drawFloor()
{
    int size = 100;
    for(float i = -size; i <= size; i += 5) {
          glBegin(GL_LINES);
              glColor3ub(150, 190, 150);
              glVertex3f(-size, 0, i);
              glVertex3f(size, 0, i);
              glVertex3f(i, 0,-size);
              glVertex3f(i, 0, size);
          glEnd();
      }
}

void GLWidget::drawPyramid()
{

    glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
       // Front
       glColor3f(1.0f, 0.0f, 0.0f);     // Red
       glVertex3f( 1.0f, 2.0f, 1.0f);
       glColor3f(0.0f, 1.0f, 0.0f);     // Green
       glVertex3f(0.0f, 0.0f, 2.0f);
       glColor3f(0.0f, 0.0f, 1.0f);     // Blue
       glVertex3f(2.0f, 0.0f, 2.0f);

       // Right
       glColor3f(1.0f, 0.0f, 0.0f);     // Red
       glVertex3f(1.0f, 2.0f, 1.0f);
       glColor3f(0.0f, 0.0f, 1.0f);     // Blue
       glVertex3f(2.0f, 0.0f, 2.0f);
       glColor3f(0.0f, 1.0f, 0.0f);     // Green
       glVertex3f(2.0f, 0.0f, 0.0f);

       // Back
       glColor3f(1.0f, 0.0f, 0.0f);     // Red
       glVertex3f(1.0f, 2.0f, 1.0f);
       glColor3f(0.0f, 1.0f, 0.0f);     // Green
       glVertex3f(2.0f, 0.0f, 0.0f);
       glColor3f(0.0f, 0.0f, 1.0f);     // Blue
       glVertex3f(0.0f, 0.0f, 0.0f);

       // Left
       glColor3f(1.0f,0.0f,0.0f);       // Red
       glVertex3f(1.0f, 2.0f, 1.0f);
       glColor3f(0.0f,0.0f,1.0f);       // Blue
       glVertex3f(0.0f, 0.0f, 0.0f);
       glColor3f(0.0f,1.0f,0.0f);       // Green
       glVertex3f(0.0f, 0.0f, 2.0f);
    glEnd();   // Done drawing the pyramid
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
    default:
        e->ignore();
    }

    paintGL();
}

void GLWidget::mouseMoveEvent(QMouseEvent *e)
{
    int x = e->x();
    int y = e->y();
    //std::cout << "X: " << x << " Y: " << y << std::endl;
    cam.moveMouse(x, y, width(), height());

    paintGL();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
            QPoint lastPoint = event->pos();
            lastPoint.setY(height() - lastPoint.y());
            std::cout << "Mouse:" << std::endl;
            std::cout << lastPoint.x() << " " << lastPoint.y() << std::endl;
            std::cout << "View:" << std::endl;
            std::cout << cam.view.x << " " << cam.view.y << std::endl;
        }
}

void GLWidget::drawLaTIM()
{
    glPushMatrix();

    glColor3f(0.9f, 0.9f, 0.9f); //wall colors
    //back wall
    glTranslated(-(0.1f), 0.0f, 0.0f);
    drawHexahedron(0.1f, wall1_h, wall1_d);
    glTranslated((0.1f), 0.0f, 0.0f);
    //door
    glColor3f(0.25f, 0.25f, 0.25f); //door colors
    drawHexahedron(door_w, door_h, door_d);
    //back wall
    glColor3f(0.9f, 0.9f, 0.9f); //wall colors
    glTranslated(0.0f, door_h, 0.0f);
    drawHexahedron(door_w, wall1_h - door_h, door_d);
    glTranslated(0.0f, -door_h, 0.0f);

    //back wall
    glTranslated(-(0.1f), 0.0f, 0.0f);
    glTranslated((0.1f + door_w), 0.0f, 0.0f);
    drawHexahedron(wall1_w - 0.1f - door_w, wall1_h, wall1_d);
    glTranslated(-(0.1f + door_w), 0.0f, 0.0f);
    //front wall
    glTranslated(0.0f, 0.0f, 6.80f);
    drawHexahedron(wall1_w, wall1_h, wall1_d);
    glTranslated(0.0f, 0.0f, -6.80f);
    //left wall
    glTranslated(wall1_w, 0.0f, 0.0f);
    glRotated(90.0f, 0.0f, -1.0f, 0.0f);
    drawHexahedron(wall2_w, wall2_h, wall2_d);
    glRotated(-90.0f, 0.0f, -1.0f, 0.0f);
    glTranslated(-wall1_w, 0.0f, 0.0f);
    //right wall
    glRotated(90.0f, 0.0f, -1.0f, 0.0f);
    drawHexahedron(wall2_w, wall2_h, wall2_d);
    glRotated(-90.0f, 0.0f, -1.0f, 0.0f);

    //new desk
    //right side
    glColor3f(0.75f, 0.75f, 0.75f); //desk color
    glTranslated(0.0f, desk_y, wall2_w);
    glRotated(90.0f, 0.0f, 1.0f, 0.0f);
    drawHexahedron(nDeskR_w, nDeskR_h, nDeskR_d);
    glRotated(-90.0f, 0.0f, 1.0f, 0.0f);
    glTranslated(0.0f, -0.7f, -wall2_w);
    //left side
    glTranslated(nDeskL_d, desk_y, (wall2_w - nDeskL_d));
    drawHexahedron(nDeskL_w, nDeskL_h, nDeskL_d);
    glTranslated(-nDeskL_d, -desk_y, -(wall2_w -nDeskL_d));

    //desks
    glColor3f(0.55f, 0.55f, 0.55f); //desk color
    glTranslated((nDeskL_d + nDeskL_w), desk_y, (wall2_w - nDeskL_d));
    //desk 1
    drawDesk();
    //desk 2
    glTranslated(0.0f, 0.0f, -2.25f);
    drawDesk();
    //desk 4
    glTranslated(2.85f, 0.0f, -1.0f);
    glRotated(180.0f, 0.0f, 1.0f, 0.0f);
    drawDesk();
    glRotated(-180.0f, 0.0f, 1.0f, 0.0f);
    glTranslated(-2.85f, 0.0f, 1.0f);
    //desk 3
    glTranslated(2.85f, 0.0f, 1.25f);
    glRotated(180.0f, 0.0f, 1.0f, 0.0f);
    drawDesk();
    glRotated(-180.0f, 0.0f, 1.0f, 0.0f);
    glTranslated(-2.85f, 0.0f, -1.25f);
    glTranslated(0.0f, 0.0f, 2.25f);
    glTranslated(-(nDeskL_d + nDeskL_w), -desk_y, -(wall2_w - nDeskL_d));

    //desks divider
    glColor3f(0.85f, 0.85f, 0.85f); //divider color
    //divider 1
    glTranslated((deskArm_w + deskCen_d - deskDiv_d - 0.02f), 0.0f, (wall2_w - (deskArm_d*2 + deskCen_w) - 0.05f));
    drawHexahedron(deskDiv1_w, deskDiv_h, deskDiv_d);
    //divider 2
    glTranslated(0.0f, 0.0f, -(deskCen_w + deskArm_d*2 + deskDiv_d));
    drawHexahedron(deskDiv1_w, deskDiv_h, deskDiv_d);
    glTranslated(0.0f, 0.0f, (deskCen_w + deskArm_d*2 + deskDiv_d));
    //divider 3
    glTranslated((deskArm_w - 0.02f), 0.0f, (deskCen_w + deskArm_d*2 + deskDiv_d));
    glRotated(90.0f, 0.0f, 1.0f, 0.0f);
    drawHexahedron(deskDiv2_w, deskDiv_h, deskDiv_d);
    glRotated(-90.0f, 0.0f, 1.0f, 0.0f);
    glTranslated(-(deskArm_w - 0.02f), 0.0f, -(deskCen_w + deskArm_d*2 + deskDiv_d));
    glTranslated(-(deskArm_w + deskCen_d - deskDiv_d), 0.0f, -(wall2_w - (deskArm_d*2 + deskCen_w) - 0.05f));

    //cabinets
    //cabinet 1
    glColor3f(0.85f, 0.85f, 0.85f); //cabinet color
    glTranslated((wall1_w - cabinet1_d - wall1_d), 0.0f, (cabinet1_w + wall1_d + 0.2f));
    glRotated(90.0f, 0.0f, 1.0f, 0.0f);
    drawCabinet(cabinet1_w, cabinet1_h, cabinet1_d);
    glRotated(-90.0f, 0.0f, 1.0f, 0.0f);
    glTranslated(-(wall1_w - cabinet1_d - wall1_d), 0.0f, -(cabinet1_w + wall1_d + 0.2f));

    //cabinet 2
    glColor3f(0.85f, 0.85f, 0.85f); //cabinet color
    glTranslated(cabinet2_d + 0.05f, 0.0f, (wall2_w - nDeskR_w - cabinet2_w - 0.01f));
    glRotated(-90.0f, 0.0f, 1.0f, 0.0f);
    drawCabinet(cabinet2_w, cabinet2_h, cabinet2_d);
    glRotated(90.0f, 0.0f, 1.0f, 0.0f);
    glPopMatrix();
}

void GLWidget::drawHexahedron(GLdouble w, GLdouble h, GLdouble d)
{
    //front side
    drawRect(0.0f, 0.0f, 0.0f,
                w, 0.0f, 0.0f,
                w,    h, 0.0f,
             0.0f,    h, 0.0f);

    //back side
    drawRect(0.0f, 0.0f, d,
                w, 0.0f, d,
                w,    h, d,
             0.0f,    h, d);

    //left side
    drawRect(0.0f, 0.0f, 0.0f,
             0.0f, 0.0f, d,
             0.0f,    h, 0.0f,
             0.0f,    h, d);

    //right side
    drawRect(w, 0.0f, 0.0f,
             w, 0.0f, d,
             w,    h, d,
             w,    h, 0.0f);

    //bottom side
    drawRect(0.0f, 0.0f, 0.0f,
             0.0f, 0.0f, d,
             w,    0.0f, d,
             w,    0.0f, 0.0f);

    //top side
    drawRect(0.0f, h, 0.0f,
             w, h, 0.0f,
             w, h, d,
             0.0f, h, d);

}

void GLWidget::drawRect(GLdouble p1_x, GLdouble p1_y, GLdouble p1_z,
                        GLdouble p2_x, GLdouble p2_y, GLdouble p2_z,
                        GLdouble p3_x, GLdouble p3_y, GLdouble p3_z,
                        GLdouble p4_x, GLdouble p4_y, GLdouble p4_z)
{
    glBegin(GL_POLYGON);
        glVertex3f(p1_x, p1_y, p1_z); //bottom left
        glVertex3f(p2_x, p2_y, p2_z); //bottom right
        glVertex3f(p3_x, p3_y, p3_z); //top right
        glVertex3f(p4_x, p4_y, p4_z); //top left
    glEnd();
}

void GLWidget::drawDesk()
{
    //right side
    drawHexahedron(deskArm_w, deskArm_h, deskArm_d);
    //middle
    glTranslated(deskArm_w, 0.0f, -1.0f);
    glRotated(90.0f, 0.0f, -1.0f, 0.0f);
    drawHexahedron(deskCen_w, deskCen_h, deskCen_d);
    glRotated(-90.0f, 0.0f, -1.0f, 0.0f);
    glTranslated(-deskArm_w, 0.0f, 1.0f);
    // left side
    glTranslated(0.0f, 0.0f, -(deskCen_w + deskArm_d));
    drawHexahedron(deskArm_w, deskArm_h, deskArm_d);
    glTranslated(0.0f, 0.0f, (deskCen_w + deskArm_d));
}

void GLWidget::drawCabinet(GLdouble w, GLdouble h, GLdouble d)
{
    //left side
    drawRect(0.0f, 0.0f, 0.0f,
             0.0f, 0.0f, d,
             0.0f,    h, 0.0f,
             0.0f,    h, d);

    //right side
    drawRect(w, 0.0f, 0.0f,
             w, 0.0f, d,
             w,    h, d,
             w,    h, 0.0f);

    //bottom side
    drawRect(0.0f, 0.0f, 0.0f,
             0.0f, 0.0f, d,
             w,    0.0f, d,
             w,    0.0f, 0.0f);

    //top side
    drawRect(0.0f, h, 0.0f,
             w, h, 0.0f,
             w, h, d,
             0.0f, h, d);

    glColor3f(0.85f, 0.85f, 0.85f); //cabinet color
    //back side
    drawRect(0.0f, 0.0f, d,
                w, 0.0f, d,
                w,    h, d,
             0.0f,    h, d);

    glColor3f(0.6f, 0.6f, 0.6f); //cabinet color
    //right door
    drawRect(0.0f, 0.0f, 0.0f,
                w/2 - 0.005f, 0.0f, 0.0f,
                w/2 - 0.005f,    h, 0.0f,
               0.0f,    h, 0.0f);

    //left door
    drawRect(w/2 + 0.005f, 0.0f, 0.0f,
                w, 0.0f, 0.0f,
                w,    h, 0.0f,
               w/2 + 0.005f,    h, 0.0f);
}
