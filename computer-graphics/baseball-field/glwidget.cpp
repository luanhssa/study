#include "glwidget.h"
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLPaintDevice>
#include <math.h>
#include <GL/glu.h>

GLWidget::GLWidget(QWidget *parent):
    QGLWidget(parent)
{

}

/* Colors
 * Grass color
 *  glColor3f(0.54, 0.77, 0.24);
 *
 * Sand color
 *  glColor3f(0.95, 0.67, 0.43);
 */

void GLWidget::initializeGL()
{

    initializeOpenGLFunctions();

    glClearColor (0.0, 0.0, 0.0, 0.0);
    glViewport(0, 0, WIDTH, HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0.0, GLdouble(WIDTH), GLdouble(HEIGHT), 0.0, 0.0, 100.0);
    glMatrixMode(GL_MODELVIEW);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WIDTH, 0, HEIGHT, 1.0, -1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawPointBF();
/*
    glPushMatrix();
        glTranslatef(100, 100, 0);
        glColor3f(1.0, 1.0, 1.0);
        drawBaseLine(0.0, baseLineSize, 26.0f, 10000);
    glPopMatrix();
*/
    glFlush();

}

void GLWidget::resizeGL(int w, int h)
{
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glOrtho(0.0, w, h, 0.0, -1.0, 1.0);

        glMatrixMode(GL_MODELVIEW);
}

void GLWidget::drawPointBF() {

    glPushMatrix();
      glTranslatef(400.0f, 100.0f, 0.f);
      glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
      glScalef(3.0f, 3.0f, 0.0f);
      // grass line
      glPushMatrix();
        glColor3f(0.95, 0.67, 0.43);
        drawLine2f(0.0f, 0.0f, grassLineSize, 0.0f, 1000);
        glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
        drawLine2f(0.0f, 0.0f, grassLineSize, 0.0f, 1000);
        glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
        drawHollowCircle(0.5f, grassLineSize, 1000);
      glPopMatrix();
      // base line
      glPushMatrix();
        glColor3f(0.54, 0.77, 0.24);
        glTranslatef(10.0f, 10.0f, 0.f);
        drawBaseLine(0.0f, baseLineSize, 26.0f, 1000);
        // pitching mound
        glPushMatrix();
          glColor3f(0.95, 0.67, 0.43);
          glTranslatef(baseLineSize/2, baseLineSize/2, 0.f);
          drawHollowCircle(2.0f, 18.0, 100);
          // center base plate
          glPushMatrix();
            glColor3f(1.0, 1.0, 1.0);
            glTranslatef(-2.5f, 1.5f, 0.f);
            glRotatef(-45.0f, 0.0f, 0.0f, 1.0f);
            drawRect2f(0.0f, 0.0f, 5.0f, 3.0f);
          glPopMatrix();
        glPopMatrix();
        // first base
        glPushMatrix();
            glColor3f(0.95, 0.67, 0.43);
            glTranslatef(baseLineSize+5.0, -5.0f, 0.f);
            glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
            glColor3f(1.0, 1.0, 1.0);
            drawRect2f(0.0, 0.0, 10.0, 10.0);
        glPopMatrix();
        // second base
        glPushMatrix();
            glColor3f(0.95, 0.67, 0.43);
            glTranslatef(baseLineSize+5.0, baseLineSize+5.0, 0.f);
            glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
            glColor3f(1.0, 1.0, 1.0);
            drawRect2f(0.0, 0.0, 10.0, 10.0);
        glPopMatrix();
        // third base
        glPushMatrix();
            glColor3f(0.95, 0.67, 0.43);
            glTranslatef(-5.0f, baseLineSize+5.0, 0.f);
            glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
            glColor3f(1.0, 1.0, 1.0);
            drawRect2f(0.0, 0.0, 10.0, 10.0);
        glPopMatrix();
      glPopMatrix();
      // catcher's box
      glPushMatrix();
        glColor3f(0.95, 0.67, 0.43);
        glTranslatef(5.0f, 5.0f, 0.f);
        drawHollowCircle(2.0f, 26.0f, 100);
        // home base plate
        glColor3f(1.0, 1.0, 1.0);
        glTranslatef(5.0f, 5.0f, 0.f);
        glRotatef(135.0f, 0.0f, 0.0f, 1.0f);
        drawHomePlate(0.0f, 0.0f, 10.0f, 5.0f, 1000);
      glPopMatrix();
    glPopMatrix();
}


void GLWidget::drawHollowCircle(GLfloat quad, GLfloat radius, int segments) {
    GLfloat points = 1/ (GLfloat) segments;
    GLfloat twicePi = quad * M_PI;

    GLfloat x, y;

    glBegin(GL_POINTS);
        for(GLfloat angle = 0; angle <= twicePi; angle += points)
        {
            x = radius * cos(angle);
            y = radius * sin(angle);

            glVertex3f(x, y, 0.0f);
        }
    glEnd();
}

void GLWidget::drawLine2f(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, int samples) {

    GLfloat dx = (x2 - x1) / (GLfloat) samples;
    GLfloat dy = (y2 - y1) / (GLfloat) samples;

    glBegin(GL_POINTS);
        for(int i = 0; i < samples; ++i) {
            glVertex2f(i * dx, i * dy);
        }
    glEnd();
}

void GLWidget::drawRect2f(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, int samples) {
    glPushMatrix();
        glTranslatef(x1, y1, 0.0f);
        drawLine2f(x1, y1, x2, y1, samples);
        drawLine2f(x1, y1, x1, y2, samples);

        glTranslatef(0.0f, y2 - y1, 0.0f);
        drawLine2f(x1, y2, x2, y2, samples);

        glTranslatef(x2 - x1, -(y2 - y1), 0.0f);
        drawLine2f(x2, y1, x2, y2, samples);
    glPopMatrix();
}

void GLWidget::drawRect2f(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
    drawRect2f(x1, y1, x2, y2, 10000);
}

void GLWidget::drawHomePlate(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, int samples) {
    GLfloat cx = (x2-x1) / 2, cy = (y2 - y1)/2;
    glPushMatrix();
        glTranslatef(-cx, -cy, 0.0f);
        drawLine2f(x1, y1, x2, y1, samples);
        drawLine2f(x1, y1, x1, y2, samples);

        glTranslatef(0.0f, y2 - y1, 0.0f);
        GLfloat y3 = y2/2;
        GLfloat x3 = x2/2;
        drawLine2f(x3, y3, x2, y2, samples);

        glTranslatef(x3-x1, y3 - y1, 0.0f);
        drawLine2f(x1, y2, x3, y3, samples);

        glTranslatef(-(x3 - x1), -(y3 - y1), 0.0f);
        glTranslatef(x2 - x1, -(y2 - y1), 0.0f);
        drawLine2f(x2, y1, x2, y2, samples);
    glPopMatrix();
}

void GLWidget::drawBaseLine(GLfloat x1, GLfloat x2, GLfloat radius, int samples) {
    GLfloat side = x2 - (2*radius);

    // Draw left
    drawHollowCircle(0.5f, radius, samples);
    glTranslatef(0.0f, radius, 0.0f);
    drawLine2f(x1, x1, x1, side, samples);
    glTranslatef(0.0f, x2 - radius, 0.0f);
    glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
    drawHollowCircle(0.5f, radius, samples);
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);

    // Draw top
    glTranslatef(radius, 0.0f, 0.0f);
    drawLine2f(x1, x1, side, x1, samples);
    glTranslatef(x2 - radius, 0.0f, 0.0f);
    glRotatef(-180.0f, 0.0f, 0.0f, 1.0f);
    drawHollowCircle(0.5f, radius, samples);
    glRotatef(180.0f, 0.0f, 0.0f, 1.0f);

    // Draw bottom
    glTranslatef(-(x2 - radius), -x2, 0.0f);
    drawLine2f(x1, x1, side, x1, samples);
    glTranslatef(x2 - radius, 0.0f, 0.0f);
    glRotatef(-270.0f, 0.0f, 0.0f, 1.0f);
    drawHollowCircle(0.5f, radius, samples);
    glRotatef(270.0f, 0.0f, 0.0f, 1.0f);

    // Draw right
    glTranslatef(0.0f, radius, 0.0f);
    drawLine2f(x1, x1, x1, side, samples);
    glTranslatef(-x2, -radius, 0.0f);

}
