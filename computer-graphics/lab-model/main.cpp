#include "window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    int WIDTH = 840;
    int HEIGHT = 630;
    QApplication app(argc, argv);
    Window w;
    w.resize(QSize(WIDTH, HEIGHT));
    w.setGeometry(0, 0, WIDTH, HEIGHT);
    w.show();

    return app.exec();
}
