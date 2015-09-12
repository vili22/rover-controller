EXECUTE_PROCESS(COMMAND pkg-config --cflags gstreamer-1.0
                OUTPUT_VARIABLE GStreamer_INCLUDE_DIRS)
STRING(REPLACE "\n" "" GSTREAMER_INCLUDE_DIRS ${GStreamer_INCLUDE_DIRS})
STRING(REPLACE "-pthread -I" "" GStreamer_INCLUDE_DIRS ${GStreamer_INCLUDE_DIRS})
STRING(REPLACE " -I" ";" GStreamer_INCLUDE_DIRS ${GStreamer_INCLUDE_DIRS}) 
set(GStreamer_LIBRARIES gstreamer-1.0 gobject-2.0 glib-2.0 gstvideo-1.0 gstapp-1.0 pthread) 
