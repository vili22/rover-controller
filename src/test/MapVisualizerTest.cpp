#include <iostream>

#include <QApplication>
#include <QSurfaceFormat>

#include "Mapper.h"

int main(int argc, char* argv[]) {

	QApplication app(argc, argv);
	QSurfaceFormat fmt;
	fmt.setVersion(3, 3);
	fmt.setProfile(QSurfaceFormat::CoreProfile);
	QSurfaceFormat::setDefaultFormat(fmt);
	Mapper::getInstance()->viewMap();
	return app.exec();
}



