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

	/* Create the elements */
	this->playbin = gst_element_factory_make ("playbin", "playbin");

	if (!this->playbin) {
		g_printerr ("Not all elements could be created.\n");
	} else {
	   /* Set the URI to play */
		g_object_set (this->playbin, "uri", "file:///home/vvirkkal/Documents/video.h264", NULL);
	}

   this->setContents();
}

void MainWindow::setContents(){
  
  this->setWindowTitle("Positives");
  this->resize(600, 400);
  
  QVBoxLayout *videoLayout = new QVBoxLayout();
  this->videoWidget = new QWidget(contents);
  this->videoWidget->setMinimumSize(400,300);
  this->videoWidget->setStyleSheet("background-color:black");
  this->videoWidget->setAttribute(Qt::WA_NativeWindow, true);
  gst_video_overlay_set_window_handle (GST_VIDEO_OVERLAY (this->playbin), this->videoWidget->winId());
  videoLayout->addWidget(this->videoWidget);

  QHBoxLayout *buttonLayout = new QHBoxLayout;
  
  QPushButton *playButton = new QPushButton("play",contents);
  buttonLayout->addWidget(playButton);
  connect(playButton, SIGNAL(clicked()), this, SLOT(play()));

  /* mainLayout */
  videoLayout->addLayout(buttonLayout);
  contents->setLayout(videoLayout);
  setCentralWidget(contents);
}

void MainWindow::play() {
	gst_element_set_state (this->playbin, GST_STATE_PLAYING);
}
  

int main(int argc, char* argv[]) {

	QApplication app(argc, argv);
	gst_init (&argc, &argv);
	MainWindow window;
	window.show();

  return app.exec();
}
