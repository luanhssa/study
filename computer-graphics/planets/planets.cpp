#include <iostream>
#include <GL/glut.h>
//#include <stdlib.h>

GLsizei winWidth = 800, winHeight = 600;
int year = 0, day = 0;

void init(void) {
  glClearColor(0.0, 0.0, 0.0, 0.0); // black background
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT); // clear pixels

  // The sun
  glColor3f(1.0, 1.0, 0.0);
  glPushMatrix();
    glRotatef((GLfloat) year, 1.0, 0.0, 0.0);
    glRotatef((GLfloat) day, 0.0, 0.0, 1.0);
    glutWireSphere(1.0, 20, 16);
  glPopMatrix();

// Planet 1
  glPushMatrix();
    glColor3f(0.7, 0.0, 0.0);
    glRotatef((GLfloat) year, 0.0, 1.0, 0.0);
    glTranslatef(1.5, 0.0, 0.0);
    glRotatef((GLfloat) day, 0.0, 1.0, 0.0);
    glutWireSphere(0.3, 10, 8);

      // Moon 1
      glPushMatrix();
        glColor3f(0.8, 0.8, 0.8);
        glRotatef((GLfloat) year*2, 0.0, 1.0, 1.0);
        glTranslatef(0.6, 0.0, 0.0);
        glRotatef((GLfloat) day, 0.0, 1.0, 0.0);
        glutWireSphere(0.05, 10, 8);
      glPopMatrix();
      // Moon 2
      glColor3f(0.4, 0.4, 0.4);
      glPushMatrix();
        glRotatef((GLfloat) year*2, 0.0, 1.0, 0.0);
        glTranslatef(0.4, 0.0, 0.0);
        glRotatef((GLfloat) day, 0.0, 1.0, 0.0);
        glutWireSphere(0.05, 10, 8);
      glPopMatrix();
  glPopMatrix();

  // Planet 2
  glColor3f(0.0, 0.0, 0.7);
  glPushMatrix();
    glRotatef((GLfloat) year * (-1), 0.0, 1.0, 0.0);
    glTranslatef(3.0, 0.0, 0.0);
    glRotatef((GLfloat) day, 0.0, 1.0, 0.0);
    glutWireSphere(0.1, 10, 8);
  glPopMatrix();

  glutSwapBuffers();
}

void reshape(GLint w, GLint h) {
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluPerspective(60.0, (GLfloat) w / (GLfloat) h, 1.0, 20.0);
  gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboardEventListener(unsigned char key, int x, int y) {
  switch(key) {
    case 'd':
      day = (day + 10) % 360;
      break;
    case 'D':
      day = (day - 10) % 360;
      break;
    case 'y':
      year = (year + 5) % 360;
      break;
    case 'Y':
      year = (year - 5) % 360;
      break;
    case 27:// ESC
      exit(0);
      break;
    default:
      break;
  }
  glutPostRedisplay();
}

int main(int argc, char** argv) {
  glutInit(&argc,argv);

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(500, 50);
  glutInitWindowSize(winWidth, winHeight);
  glutCreateWindow("Rotacao de Planetas");
  init();

  glutDisplayFunc(display);
  glutIdleFunc(display);
  glutReshapeFunc(reshape);
  //glutMouseFunc(mouseEventListener);
  glutKeyboardFunc(keyboardEventListener);

  glutMainLoop();
  return 0;
}
