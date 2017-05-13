#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

#include <vector>
#include <functional>

class QSlider;
class QPushButton;

class MapContent;

class MapVisualizer : public QWidget
{
    Q_OBJECT

public:
	MapVisualizer(std::function<void()> f);
	void setCheckpoints(std::vector<std::vector<float>> checkPoints);

protected:
    void keyPressEvent(QKeyEvent *event) override;
	void closeEvent(QCloseEvent *event);

private:

	std::function<void()> closeAction;
	MapContent *mapContent;
};

#endif
