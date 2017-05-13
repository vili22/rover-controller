#include <MapContent.h>
#include <MapVisualizer.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>

#include <iostream>

using namespace std;

MapVisualizer::MapVisualizer(function<void()> f) :
		closeAction(f) {
    setAttribute(Qt::WA_DeleteOnClose);
    mapContent = new MapContent;

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *container = new QHBoxLayout;
    container->addWidget(mapContent);

    QWidget *w = new QWidget;
    w->setLayout(container);
    mainLayout->addWidget(w);
    setLayout(mainLayout);

    setWindowTitle(tr("Hello GL"));
}


void MapVisualizer::keyPressEvent(QKeyEvent *e) {
    if (e->key() == Qt::Key_Escape) {
        close();
    } else if (e->key() == Qt::Key_Up) {
        mapContent->translate(0.0f, -1.0f, 0.0f);
    } else if (e->key() == Qt::Key_Right) {
        mapContent->translate(-1.0f, 0.0f, 0.0f);
    } else if (e->key() == Qt::Key_Down) {
        mapContent->translate(0.0f, 1.0f, 0.0f);
    } else if (e->key() == Qt::Key_Left) {
        mapContent->translate(1.0f, 0.0f, 0.0f);
    } else {
        QWidget::keyPressEvent(e);
    }
}

void MapVisualizer::closeEvent(QCloseEvent *event) {
	closeAction();
	event->accept();
}

void MapVisualizer::setCheckpoints(vector<vector<float>> checkPoints) {
	mapContent->setCheckPoints(checkPoints);
}
