#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QOpenGLFunctions>
#include <QtOpenGL>

QT_BEGIN_NAMESPACE
class QOpenGLContext;
class QOpenGLPaintDevice;
QT_END_NAMESPACE

class GLWidget : public QGLWidget, protected QOpenGLFunctions
{

    Q_OBJECT
public:
    int WIDTH = 800,
        HEIGHT = 600;

    GLfloat baseLineSize = 90.0f,
            grassLineSize = 160.0f;

    explicit GLWidget(QWidget *parent = 0);

    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;

    /*
     * Draw a basic Baseball Field using only points.
     */
    void drawPointBF();

    /*
     * Function that handles the drawing of a circle.
     * Solid circle using TRIANGLE_FAN method.
     * Hollow circle using LINE_LOOP method.
     *
     * Params:
     *  quad (GLfloat) - the number of quads
     *	radius (GLFloat) - the radius that the painted circle will have
     *  segments (int) - # of triangles used to draw circle
     */
    void drawHollowCircle(GLfloat quad, GLfloat radius, int segments);

    /*
     * Draw a line using points
     *
     * Params:
     * x1 (GLfloat) - x position from point 1
     * y1 (GLfloat) - y position from point 1
     * x2 (GLfloat) - x position from point 2
     * y2 (GLfloat) - y position from point 2
     * points (int) - number of samples
     */
    void drawLine2f(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, int points);

    /*
     * Draw a rectangle using drawLine2f function.
     *
     * Params:
     * x1 (GLfloat) - x position from point 1
     * y1 (GLfloat) - y position from point 1
     * x2 (GLfloat) - x position from point 2
     * y2 (GLfloat) - y position from point 2
     * samples (int) - number of samples
     */
    void drawRect2f(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, int samples);
    void drawRect2f(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);

    void drawHomePlate(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, int samples);
    void drawBaseLine(GLfloat p1, GLfloat p2, GLfloat radius, int samples);
};

#endif // GLWIDGET_H

