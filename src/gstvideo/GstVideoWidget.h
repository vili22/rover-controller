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
#include <QCloseEvent>

#include <gst/gst.h>
#include <gst/video/videooverlay.h>

#include "GstPipelineBuilder.h"

namespace GstVideo {

	class GstVideoWidget : public QWidget {

		Q_OBJECT

		public:
			GstVideoWidget(int w, int h, PipelineContainer *pipeline);
			void setPipeline(PipelineContainer *pipeline);
			void startPipeline();
			WId getWinId();

		protected:
			void closeEvent(QCloseEvent *event);

		private:
			void createGstVideoWidget();
			void addWidgetHandleToPipeline();

			int width, height;
			PipelineContainer *pipeline;
	};
}
#endif /* GSTVIDEOWIDGET_H_ */
