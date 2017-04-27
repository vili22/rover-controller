#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

class QSlider;
class QPushButton;

class GLWidget;

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    GLWidget *glWidget;
};

#endif
