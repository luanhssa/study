#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QOpenGLFunctions>
#include <QtOpenGL>
#include <QMouseEvent>
#include "camera.h"


QT_BEGIN_NAMESPACE
class QOpenGLContext;
class QOpenGLPaintDevice;
QT_END_NAMESPACE

class GLWidget : public QGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;

    void drawPyramid();
    void drawFloor();
    void drawLaTIM();

    /**
     * wall1: wall that contains the window or the door
     * wall2: wall that contains cabinets
     * w: width
     * h: height
     * d: depth
     */
    GLdouble wall1_w = 5.90f
            , wall1_h = 3.0f
            , wall1_d = 0.1f
            , wall2_w = 6.80f
            , wall2_h = 3.0f
            , wall2_d = 0.1f;

    /**
     * deskArm: desk arm side
     * deskCen: desk centre side
     *
     * desk_y: height of the desk from the floor
     *
     * nDeskL: new desk left side
     * nDeskR: new desk right side
     */
    GLdouble deskArm_w = 1.40f
            , deskArm_h = 0.05f
            , deskArm_d = 0.60f
            , deskCen_w = 1.0f
            , deskCen_h = 0.05f
            , deskCen_d = 0.60
            , desk_y = 0.7f
            , nDeskR_w = 4.16f
            , nDeskR_h = 0.05f
            , nDeskR_d = 0.60f
            , nDeskL_w = 1.33f
            , nDeskL_h = 0.05f
            , nDeskL_d = 0.60f
            , deskDiv1_w = deskArm_w*2 + 0.05f
            , deskDiv2_w = deskArm_d*4 + deskCen_w*2 + 0.05f
            , deskDiv_h = 1.2f
            , deskDiv_d = 0.05f;

    GLdouble cabinet1_w = 0.80f
            , cabinet1_h = 2.08f
            , cabinet1_d = 0.57f
            , cabinet2_w = 1.0f
            , cabinet2_h = 2.20f
            , cabinet2_d = 0.57f;

    GLdouble door_w = 1.0f
            , door_h = 2.20f
            , door_d = 0.05f;

protected:
    Camera cam;

    void keyPressEvent(QKeyEvent *e);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    void drawHexahedron(GLdouble width, GLdouble height, GLdouble depth);
    void drawRect(GLdouble p1_x, GLdouble p1_y, GLdouble p1_z,
                  GLdouble p2_x, GLdouble p2_y, GLdouble p2_z,
                  GLdouble p3_x, GLdouble p3_y, GLdouble p3_z,
                  GLdouble p4_x, GLdouble p4_y, GLdouble p4_z);
    void drawDesk();
    void drawCabinet(GLdouble w, GLdouble h, GLdouble d);
};

#endif // GLWIDGET_H

