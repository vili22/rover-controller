/****************************************************************************
* This file is part of positive images
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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <string>
#include <thread>


#include <QWidget>
#include <QMainWindow>
#include <QAction>
#include <QMenuBar>
#include <QMenu>

#include <gst/gst.h>
#include <gst/video/videooverlay.h>

#include "GstVideoWidget.h"
#include "GstPipelineBuilder.h"
#include "TcpReceiver.h"
#include "TcpSocket.h"

class MainWindow : public QMainWindow{

	Q_OBJECT

public:

	MainWindow();
protected:

	void closeEvent(QCloseEvent *event);

private slots:

	void connectToRover();
	void startVideoStream();

private:

	void setContents();

	QWidget *contents;
	QMenuBar *menubar;
	QMenu *menuSystem, *menuRover;
	QAction *connectRover, *startStream, *exit;

	std::shared_ptr<Networking::TcpSocket> socket;
	std::shared_ptr<Networking::TcpReceiver> tcpReceiver;
	const std::string serverIp;
	const int port;
	std::thread tcpThread;

	GstVideo::GstVideoWidget *gstVideoWidget;

};

#endif

