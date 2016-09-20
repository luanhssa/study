#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QOpenGLFunctions>
#include <QtOpenGL>
#include <QMouseEvent>
#include "camera.h"
#include "latimmodel.h"


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

    void drawFloor();

protected:
    Camera cam;
    LaTIMModel latim;
    GLenum polygonFace = GL_FRONT_AND_BACK
            , polygonMode = GL_FILL;

    void keyPressEvent(QKeyEvent *e);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private:
};

#endif // GLWIDGET_H

