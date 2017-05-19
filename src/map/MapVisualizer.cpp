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
		closeAction(f), prevPosition(0, 0, 0) {
    setAttribute(Qt::WA_DeleteOnClose);
    mapContent = new MapContent;

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *container = new QHBoxLayout;
    container->addWidget(mapContent);

    QWidget *w = new QWidget;
    w->setLayout(container);
    mainLayout->addWidget(w);
    setLayout(mainLayout);

	setWindowTitle(tr("Map"));
	//mapContent->newPathPoint(prevPosition[0], prevPosition[1], prevPosition[2]);
}


void MapVisualizer::keyPressEvent(QKeyEvent *e) {
    if (e->key() == Qt::Key_Escape) {
        close();
    } else if (e->key() == Qt::Key_W) {
        mapContent->translate(0.0f, -1.0f, 0.0f);
    } else if (e->key() == Qt::Key_D) {
        mapContent->translate(-1.0f, 0.0f, 0.0f);
    } else if (e->key() == Qt::Key_S) {
        mapContent->translate(0.0f, 1.0f, 0.0f);
    } else if (e->key() == Qt::Key_A) {
        mapContent->translate(1.0f, 0.0f, 0.0f);
    } else if (e->key() == Qt::Key_Up) {
		prevPosition += glm::vec3(0, 1, 0);
		mapContent->newPathPoint(prevPosition[0], prevPosition[1],
				prevPosition[2]);
	} else if (e->key() == Qt::Key_Right) {
		prevPosition += glm::vec3(1, 0, 0);
		mapContent->newPathPoint(prevPosition[0], prevPosition[1],
				prevPosition[2]);
	} else if (e->key() == Qt::Key_Down) {
		prevPosition += glm::vec3(0, -1, 0);
		mapContent->newPathPoint(prevPosition[0], prevPosition[1],
				prevPosition[2]);
	} else if (e->key() == Qt::Key_Left) {
		prevPosition += glm::vec3(-1, 0, 0);
		mapContent->newPathPoint(prevPosition[0], prevPosition[1],
				prevPosition[2]);
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
