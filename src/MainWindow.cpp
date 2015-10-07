/****************************************************************************
* This file is part of RoverControl
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

MainWindow::MainWindow() : serverIp("192.168.1.69"), port(5555) {

	this->setContents();
}

void MainWindow::setContents(){
  
	this->setWindowTitle("Rover Controller");
	this->resize(400, 200);

	this->menubar = new QMenuBar(this);
	this->menubar->setGeometry(QRect(0, 0, this->width(), 23));
	this->setMenuBar(this->menubar);

	this->connectRover = new QAction(tr("&connect"),this);
    connect(this->connectRover,SIGNAL(triggered()),this,SLOT(connectToRover()));
    this->startStream = new QAction(tr("&start stream"),this);
    connect(this->startStream,SIGNAL(triggered()),this,SLOT(startVideoStream()));

    this->menuSystem = menuBar()->addMenu(tr("&System"));
    this->menuRover = this->menuBar()->addMenu(tr("&Rover"));
    this->menuRover->addAction(this->connectRover);

    this->contents=new QWidget(this);
    this->contents->setMinimumSize(200,200);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    QPushButton *playButton = new QPushButton("play",contents);
    buttonLayout->addWidget(playButton);
    connect(playButton, SIGNAL(clicked()), this, SLOT(startVideoStream()));

    contents->setLayout(buttonLayout);
    this->setCentralWidget(contents);
}

void MainWindow::connectToRover() {

	try{
		this->socket = std::make_shared<Networking::TcpSocket>(this->serverIp,this->port);
	}catch(std::exception const& e) {
		std::cout << e.what() << "\n";
		return;
	}

	this->tcpReceiver = std::make_shared<Networking::TcpReceiver>(std::make_shared<Networking::BufferedSocketReader>(this->socket->getSocket()));
	this->tcpThread = this->tcpReceiver->start();
}

void MainWindow::startVideoStream() {

	gstVideoWidget = new GstVideo::GstVideoWidget(600,400, NULL);
	gstVideoWidget->show();
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
