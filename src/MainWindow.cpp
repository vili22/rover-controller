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
#include <QMessageBox>

#include <iostream>
#include <fstream>

#include "MainWindow.h"
#include "Configuration.h"

using namespace configuration;

MainWindow::MainWindow() : serverIp("192.168.1.69"), port(5550), connected(false), gstVideoWidget(NULL){

	this->setContents();
	Configuration::initializeConfiguration();
}

void MainWindow::setContents(){

	this->setWindowTitle("Rover Controller");
	this->resize(400, 200);

	this->menubar = new QMenuBar(this);
	this->menubar->setGeometry(QRect(0, 0, this->width(), 23));
	this->setMenuBar(this->menubar);

    this->menuSystem = this->menuBar()->addMenu(tr("&System"));

    this->connectRover = new QAction(tr("&connect"),this);
    connect(this->connectRover,SIGNAL(triggered()),this,SLOT(connectToRover()));
    this->startStream = new QAction(tr("&start stream"),this);
    connect(this->startStream,SIGNAL(triggered()),this,SLOT(startVideoStream()));
    this->menuRover = this->menuBar()->addMenu(tr("&Rover"));
    this->menuRover->addAction(this->connectRover);
    this->menuRover->addAction(this->startStream);
    this->startStream->setDisabled(true);


    this->openConfiguration = new QAction(tr("&configuration"), this);
    connect(this->openConfiguration, SIGNAL(triggered()), this, SLOT(openConfigurationDialog()));
    this->menuSettings = this->menuBar()->addMenu(tr("&Settings"));
    this->menuSettings->addAction(this->openConfiguration);

    this->contents=new QWidget(this);
    this->contents->setMinimumSize(200,200);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    QWidget *controlWidget = new QWidget();
    controlWidget->setMinimumSize(100,100);
    QHBoxLayout *controlLayout = new QHBoxLayout();
    controlLayout->setAlignment(Qt::AlignVCenter);
    controlWidget->setLayout(controlLayout);

    this->messageWindow = new QListWidget();

    mainLayout->addWidget(controlWidget);
    mainLayout->addWidget(messageWindow);

    contents->setLayout(mainLayout);
    this->setCentralWidget(contents);
}

void MainWindow::connectToRover() {

	try{
		this->socket = std::make_shared<Networking::TcpSocket>(this->serverIp,this->port);
		this->connected = true;
	}catch(std::exception const& e) {
		this->connected = false;
		QMessageBox msgBox;
		std::string messageString = "Unable to connect to rover (" + std::string(e.what()) + ")";
		msgBox.setText(messageString.c_str());
		msgBox.exec();
		return;
	}

	this->tcpReceiver = std::make_shared<Networking::TcpReceiver>(std::make_shared<Networking::BufferedSocketReader>(this->socket->getSocket()), this->messageHandler);
	this->messageHandlerThread = this->messageHandler.start();
	this->tcpThread = this->tcpReceiver->start();
	this->connectRover->setDisabled(true);
	this->startStream->setDisabled(false);
}

void MainWindow::startVideoStream() {


	if(this->socket->writeLine("start\n") < 0 ) {
		this->startStream->setDisabled(true);
		this->connectRover->setDisabled(false);
		this->closeTcpConnection();
		QMessageBox msgBox;
		std::string messageString = "Connection problem";
		msgBox.setText(messageString.c_str());
		msgBox.exec();
		return;
	}
	gstVideoWidget = new GstVideo::GstVideoWidget(600,400, NULL);
	gstVideoWidget->show();
	GstVideo::PipelineContainer *pipeline = GstVideo::buildH264UdpPipe(5001, gstVideoWidget->getWinId());
	if (!pipeline) {
		QMessageBox msgBox;
		std::string messageString = "Unable to create pipeline";
		msgBox.setText(messageString.c_str());
		msgBox.exec();
		return;
	}
	gstVideoWidget->setPipeline(pipeline);
	gstVideoWidget->startPipeline();
	this->startStream->setDisabled(true);
}

void MainWindow::openConfigurationDialog() {

    ConfigurationWidget *configurationWidget = new ConfigurationWidget(this);
    configurationWidget->show();
}

void MainWindow::closeTcpConnection() {

	this->connected = false;
	this->socket->writeLine("exit\n");
	this->tcpReceiver->abort();
	this->messageHandler.abort();
	this->tcpThread.join();
	this->messageHandlerThread.join();
}
void MainWindow::closeEvent(QCloseEvent *event) {

    if(this->connected) {
        this->closeTcpConnection();
    }
	if(this->gstVideoWidget) {
		this->gstVideoWidget->close();
	}
	gst_deinit();
	event->accept();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {

	if(!this->connected) {
		return;
	}
	if(event->key() == Qt::Key_Up){
		this->socket->writeLine("df");
		event->accept();
	}else if(event->key()==Qt::Key_Down){
		this->socket->writeLine("db");
		event->accept();
	}else if(event->key()==Qt::Key_Left){
		this->socket->writeLine("dl");
		event->accept();
	}else if(event->key() == Qt::Key_Right){
		this->socket->writeLine("dr");
		event->accept();
	}else if(event->key() == Qt::Key_S){
		this->socket->writeLine("ds");
		event->accept();
	}
}

int main(int argc, char* argv[]) {

	QApplication app(argc, argv);
	MainWindow window;
	gst_init (&argc, &argv);
	window.show();
	return app.exec();
}
