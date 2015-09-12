/****************************************************************************
* This file is part of Positive images
* Copyright (C) 2014 Ville Virkkala
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published
* by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QBoxLayout>
#include <QPainter>
#include <QRect>
#include <QDebug>
#include <QTextStream>

#include <iostream>
#include <fstream>

#include "MainWindow.h"

MainWindow::MainWindow(){

	this->contents=new QWidget(this);
	this->contents->setMinimumSize(200,200);
	this->setContents();
}

void MainWindow::setContents(){
  
  this->setWindowTitle("Positives");
  this->resize(200, 200);

  QHBoxLayout *buttonLayout = new QHBoxLayout;
  QPushButton *playButton = new QPushButton("play",contents);
  buttonLayout->addWidget(playButton);
  connect(playButton, SIGNAL(clicked()), this, SLOT(play()));

  contents->setLayout(buttonLayout);
  setCentralWidget(contents);
}

void MainWindow::play() {

	gstVideoWidget = new GstVideo::GstVideoWidget(600,400, NULL);
	gstVideoWidget->show();
	std::cout << "window created winId " << gstVideoWidget->getWinId() << "\n";
	GstVideo::PipelineContainer *pipeline = GstVideo::buildH264UdpPipe(5001, gstVideoWidget->getWinId());
	if (!pipeline) {
		g_printerr ("Udp pipeline could not be created");
		return;
	}
	gstVideoWidget->setPipeline(pipeline);
	std::cout << "pipeline created\n";
	gstVideoWidget->startPipeline();
	std::cout << "pipeline started\n";
}

void MainWindow::closeEvent(QCloseEvent *event) {

	gst_deinit();
	event->accept();
}
  

int main(int argc, char* argv[]) {

	QApplication app(argc, argv);
	MainWindow window;
	gst_init (&argc, &argv);
	window.show();
	return app.exec();
}
