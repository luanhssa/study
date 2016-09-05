#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();

protected:
    void keyPressEvent(QKeyEvent *e);

private:
    Ui::MainWindow *ui;

};
#endif // WINDOW_H
