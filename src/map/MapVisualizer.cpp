#include <MapContent.h>
#include <MapVisualizer.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>

#include <iostream>

#include "Configuration.h"
#include "FileUtils.h"
#include "SensorProcessor.h"
#include "Mapper.h"

using namespace std;
using namespace configuration;

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
	} else if (e->key() == Qt::Key_H) {
		runSimulation();
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

void MapVisualizer::setPathPoints(vector<glm::vec3> points) {
	mapContent->setPathPoints(points);
}

void MapVisualizer::addVisualizedPoint(glm::vec3 newPoint) {

	prevPosition = newPoint;
	mapContent->newPathPoint(prevPosition[0], prevPosition[1], prevPosition[2]);
}

void MapVisualizer::runSimulation() {

	cout << "running simulation  <<<\n";
	Configuration::initializeConfiguration();
	string filename =
			"/home/vvirkkal/Documents/development/rover-controller/sensor-data/data_kaannos1.txt";
	vector<vector<double>> doubleArray = utils::read_float_type_array<double>(
			filename);
	sort(doubleArray.begin(), doubleArray.end(), [](const vector<double> &a,
			const vector<double> &b) {return a[1] < b[1];});

	for (vector<vector<double>>::iterator it = doubleArray.begin();
			it < doubleArray.end(); it++) {
		SensorProcessor::getInstance()->newSensorReading(*it);
		vector<double> state = SensorProcessor::getInstance()->getState();
		Mapper::getInstance()->addPathPoint(float(state[0]), float(state[1]),
				float(state[2]), 0.0f);
		for (size_t ind = 0; ind < state.size(); ind++) {
			if (ind == 3) {
				cout << state[ind] * 180 / M_PI << " ";
			} else {
				cout << state[ind] << " ";
			}
		}
		cout << "\n";
	}
}

