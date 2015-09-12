/*
 * GstPipelineBuilder.cpp
 *
 *  Created on: Sep 6, 2015
 *      Author: vvirkkal
 */
#include <iostream>
#include "GstPipelineBuilder.h"

GstVideo::PipelineContainer* GstVideo::buildH264UdpPipe(int port, guintptr windowHandle) {

	/* Create the elements */
	PipelineContainer *container = new PipelineContainer();
	GstElement *pipeline, *udpsrc, *rtpjitterbuffer, *rtph264depay, *avdec_h264, *autovideosink;
	GstCaps *udpSrcCaps;

	udpSrcCaps = gst_caps_new_simple("application/x-rtp","payload", G_TYPE_INT, 96, NULL);
	udpsrc = gst_element_factory_make("udpsrc", "udpsrc");
	g_object_set(udpsrc, "caps", udpSrcCaps, NULL);
	g_object_set (udpsrc, "port", port, NULL);
	gst_caps_unref(udpSrcCaps);


	rtpjitterbuffer = gst_element_factory_make("rtpjitterbuffer","rtpjitterbuffer");
	rtph264depay = gst_element_factory_make("rtph264depay","rtph264depay");
	avdec_h264 = gst_element_factory_make("avdec_h264","avdec_h264");
	autovideosink = gst_element_factory_make("autovideosink","autovideosink");
	g_object_set(autovideosink, "sync", false, NULL);

	pipeline = gst_pipeline_new ("pipeline");
	if (!pipeline || !udpsrc || !rtpjitterbuffer || !rtph264depay || !avdec_h264 || !autovideosink) {
		g_printerr ("Not all elements could be created.\n");
	    return NULL;
	}

	gst_bin_add_many (GST_BIN (pipeline), udpsrc, rtpjitterbuffer, rtph264depay, avdec_h264, autovideosink, NULL);
	if (gst_element_link_many(udpsrc, rtpjitterbuffer, rtph264depay, avdec_h264, autovideosink, NULL) != TRUE){
		g_printerr("Elements could not be linked.\n");
		gst_object_unref(pipeline);
		return NULL;
	}

	std::cout << "win Id" << windowHandle <<" address " << &windowHandle<< "\n";
	GstBus *bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
	gst_bus_set_sync_handler (bus, (GstBusSyncHandler) GstVideo::bus_sync_handler, (gpointer)windowHandle, NULL);
	//globalHandle = windowHandle;
	//gst_bus_set_sync_handler (bus, (GstBusSyncHandler) GstVideo::bus_sync_handler, NULL, NULL);

	container->pipeline = pipeline;
	container->udpsrc = udpsrc;
	container->rtpjitterbuffer = rtpjitterbuffer;
	container->rtph264depay = rtph264depay;
	container->avdec_h264 = avdec_h264;
	container->autovideosink = autovideosink;
	return container;
}

void GstVideo::freePipeline(PipelineContainer *pipeline) {

	if(!pipeline) {
		return;
	}

	gst_object_unref(pipeline->pipeline);
	delete pipeline;
}

GstBusSyncReply GstVideo::bus_sync_handler(GstBus *bus, GstMessage *message, gpointer data) {

	if(GST_MESSAGE_TYPE (message) == GST_MESSAGE_ERROR) {
		GError *err;
		gchar *debug_info;
		gst_message_parse_error (message, &err, &debug_info);
	    g_printerr ("Error received from element %s: %s\n", GST_OBJECT_NAME (message->src), err->message);
	    g_printerr ("Debugging information: %s\n", debug_info ? debug_info : "none");
	    g_clear_error (&err);
	    g_free (debug_info);
	    return GST_BUS_PASS;
	}else if(gst_is_video_overlay_prepare_window_handle_message (message)) {
		GstVideoOverlay *overlay = GST_VIDEO_OVERLAY (GST_MESSAGE_SRC (message));
		gst_video_overlay_set_window_handle (overlay, (guintptr)data);
		gst_message_unref (message);
		return GST_BUS_DROP;
	}else {
		return GST_BUS_PASS;
	}
}


