/*
 * GstPipelineBuilder.h
 *
 *  Created on: Sep 6, 2015
 *      Author: vvirkkal
 */

#ifndef GSTPIPELINEBUILDER_H_
#define GSTPIPELINEBUILDER_H_

#include <string>

#include <gst/gst.h>
#include <gst/video/videooverlay.h>


namespace GstVideo {

	typedef struct {
		GstElement *pipeline,*udpsrc, *rtpjitterbuffer, *rtph264depay, *avdec_h264, *autovideosink;
	} PipelineContainer;

	PipelineContainer* buildH264UdpPipe(int port, guintptr windowHandle);
	GstBusSyncReply bus_sync_handler(GstBus *bus, GstMessage *message, gpointer data);
	void freePipeline(PipelineContainer *pipeline);
}

#endif /* GSTPIPELINEBUILDER_H_ */
