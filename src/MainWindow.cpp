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

	GstElement *pipeline = gst_element_factory_make ("playbin", "playbin");
	if (!pipeline) {
		g_printerr ("Not all elements could be created.\n");
		return;
	} else {
		g_object_set (pipeline, "uri", "file:///home/vvirkkal/Documents/video.h264", NULL);
	}

	gstVideoWidget = new GstVideo::GstVideoWidget(600,400, NULL);
	gstVideoWidget->show();
	gstVideoWidget->setPipeline(pipeline);
	gstVideoWidget->startPipeline();
}
  

int main(int argc, char* argv[]) {

	QApplication app(argc, argv);
	gst_init (&argc, &argv);
	MainWindow window;
	window.show();

  return app.exec();
}
