#include "glwidget.h"
#include "window.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>

#include <iostream>

Window::Window()
{
    setAttribute(Qt::WA_DeleteOnClose);
    glWidget = new GLWidget;



    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *container = new QHBoxLayout;
    container->addWidget(glWidget);

    QWidget *w = new QWidget;
    w->setLayout(container);
    mainLayout->addWidget(w);
    setLayout(mainLayout);

    setWindowTitle(tr("Hello GL"));
}


void Window::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape) {
        close();
    } else if (e->key() == Qt::Key_Up) {
        glWidget->translate(0.0f, -1.0f, 0.0f);
    } else if (e->key() == Qt::Key_Right) {
        glWidget->translate(-1.0f, 0.0f, 0.0f);
    } else if (e->key() == Qt::Key_Down) {
        glWidget->translate(0.0f, 1.0f, 0.0f);
    } else if (e->key() == Qt::Key_Left) {
        glWidget->translate(1.0f, 0.0f, 0.0f);
    } else {
        QWidget::keyPressEvent(e);
    }
}
