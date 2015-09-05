/*
 * GstVideoWidget.h
 *
 *  Created on: Sep 5, 2015
 *      Author: vvirkkal
 */

#ifndef GSTVIDEOWIDGET_H_
#define GSTVIDEOWIDGET_H_

#include <QApplication>
#include <QWidget>

#include <gst/gst.h>
#include <gst/video/videooverlay.h>

namespace GstVideo {

	class GstVideoWidget : public QWidget {

		Q_OBJECT

		public:
			GstVideoWidget(int w, int h, GstElement *pipeline);
			void setPipeline(GstElement *pipeline);
			void startPipeline();

		private:
			void createGstVideoWidget();
			void addWidgetHandleToPipeline();

			int width, height;
			GstElement *pipeline;
	};
}
#endif /* GSTVIDEOWIDGET_H_ */
