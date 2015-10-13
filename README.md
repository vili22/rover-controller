Rover-controller
====================================
Rover-controller is a program that is able
to communicate with a server running on 
Rasbperry Pi and stream a h264 video-stream
from Rasbicam. In future it is also suppose to
control Rover that is connected to RasberryPi
through serial port(see repository robot)

Dependencies
------------
- g++ std=c++11, make
- cmake
- Qt >= 5
- Gstreamer-1.0 development libraries

Installation
------------------------------------
In linux environment install QT5 and Gstreamer-1.0
development libraries. If the Gstreamer is installed
through package-manager the provided FindGStreamer.cmake
should find it. If installed in otherway modify the 
FindGStreamer.cmake file.
 
Create eclipse-cmake project 
https://cmake.org/Wiki/Eclipse_CDT4_Generator
and import the provided CMakeLists.txt in src folder
to eclipse.
