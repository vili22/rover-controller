/*
 * GstVideoWidget.cpp
 *
 *  Created on: Sep 5, 2015
 *      Author: vvirkkal
 */
#include "GstVideoWidget.h"


GstVideo::GstVideoWidget::GstVideoWidget(int w, int h, PipelineContainer *pipeline) {

    setAttribute(Qt::WA_DeleteOnClose);
	this->width = w;
	this->height = h;
	this->pipeline = pipeline;
	createGstVideoWidget();
}

void GstVideo::GstVideoWidget::closeEvent(QCloseEvent *event) {

	gst_element_set_state (pipeline->pipeline, GST_STATE_NULL);
	freePipeline(pipeline);
	event->accept();
}

void GstVideo::GstVideoWidget::setPipeline(PipelineContainer *pipeline) {

	this->pipeline = pipeline;
}

void GstVideo::GstVideoWidget::startPipeline() {

	gst_element_set_state (pipeline->pipeline, GST_STATE_PLAYING);

}

void GstVideo::GstVideoWidget::createGstVideoWidget() {

	setMinimumSize(this->width, this->height);
	setStyleSheet("background-color:black");
	setAttribute(Qt::WA_NativeWindow, true);
}

WId GstVideo::GstVideoWidget::getWinId() {

	return winId();
}

void GstVideo::GstVideoWidget::addWidgetHandleToPipeline() {

	if(pipeline != NULL) {
		gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(pipeline->autovideosink), winId());
	}
}




