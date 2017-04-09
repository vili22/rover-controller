/****************************************************************************
* This file is part of rover-control
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
#include <thread>

#include <QWidget>
#include <QMainWindow>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QListWidget>

#include <gst/gst.h>
#include <gst/video/videooverlay.h>

#include "GstVideoWidget.h"
#include "GstPipelineBuilder.h"
#include "TcpSocket.h"

#include "ConfigurationWidget.h"

class MainWindow : public QMainWindow{

	Q_OBJECT

public:

	MainWindow();
protected:

	void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    bool eventFilter(QObject *object, QEvent *e);

private slots:

	void connectToRover();
	void startVideoStream();

	void openConfigurationDialog();
	void openMapView();

private:

	void setContents();
	void closeTcpConnection();

	QWidget *contents;
	QMenuBar *menubar;
	QMenu *menuSystem, *menuRover, *menuSettings, *menuMap;
	QAction *connectRover, *startStream, *exit, *openConfiguration, *mapView;
	QListWidget *messageWindow;

	std::shared_ptr<networking::TcpSocket> socket;
	std::thread tcpThread;
	bool connected;

	GstVideo::GstVideoWidget *gstVideoWidget;

	std::thread messageHandlerThread;

};

#endif

