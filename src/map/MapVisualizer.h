#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

#include <glm/glm.hpp>

#include <vector>
#include <functional>
#include <memory>

class QSlider;
class QPushButton;

class MapContent;

class MapVisualizer: public QWidget {
    Q_OBJECT

public:
	MapVisualizer(std::function<void()> f);
	void setCheckpoints(std::vector<std::vector<float>> checkPoints);
	void setPathPoints(std::vector<glm::vec3> pathPoints);

protected:
    void keyPressEvent(QKeyEvent *event) override;
	void closeEvent(QCloseEvent *event);

public slots:
	void addVisualizedPoint(glm::vec3 point);

private:

	void runSimulation();
	MapContent *mapContent;
	std::function<void()> closeAction;
	glm::vec3 prevPosition;
};

#endif
