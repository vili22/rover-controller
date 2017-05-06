#ifndef WINDOW_H
#define WINDOW_H

#include <functional>
#include <QWidget>

class QSlider;
class QPushButton;

class MapContent;

class MapVisualizer : public QWidget
{
    Q_OBJECT

public:
	MapVisualizer(std::function<void()> f);

protected:
    void keyPressEvent(QKeyEvent *event) override;
	void closeEvent(QCloseEvent *event);


private:

	std::function<void()> closeAction;
    MapContent *glWidget;
};

#endif
