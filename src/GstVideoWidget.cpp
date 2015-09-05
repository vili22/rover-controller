/*
 * GstVideoWidget.cpp
 *
 *  Created on: Sep 5, 2015
 *      Author: vvirkkal
 */
#include "GstVideoWidget.h"


GstVideo::GstVideoWidget::GstVideoWidget(int w, int h, GstElement *pipeline) {

	this->width = w;
	this->height = h;
	this->pipeline = pipeline;
	createGstVideoWidget();
}

void GstVideo::GstVideoWidget::setPipeline(GstElement *pipeline) {

	this->pipeline = pipeline;
	addWidgetHandleToPipeline();
}

void GstVideo::GstVideoWidget::startPipeline() {

	gst_element_set_state (pipeline, GST_STATE_PLAYING);

}

void GstVideo::GstVideoWidget::createGstVideoWidget() {

	setMinimumSize(this->width, this->height);
	setStyleSheet("background-color:black");
	setAttribute(Qt::WA_NativeWindow, true);
}

void GstVideo::GstVideoWidget::addWidgetHandleToPipeline() {

	if(pipeline != NULL) {
		gst_video_overlay_set_window_handle (GST_VIDEO_OVERLAY(pipeline), winId());
	}
}



