#include "window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    int WIDTH = 800;
    int HEIGHT = 600;
    QApplication app(argc, argv);
    Window w;
    w.resize(QSize(WIDTH, HEIGHT));
    w.show();

    return app.exec();
}
