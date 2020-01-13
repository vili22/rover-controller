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

-qt5:
sudo apt-get install qt5-default

- gstreamer-libraries: 
sudo apt-get install libgstreamer1.0-0 gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-doc gstreamer1.0-tools gstreamer1.0-x gstreamer1.0-alsa gstreamer1.0-gl gstreamer1.0-gtk3 gstreamer1.0-qt5 gstreamer1.0-pulseaudio
sudo apt-get install libgstreamer1.0-0-dev
sudo apt-get install libfontconfig1-dev libfreetype6-dev libpng-dev
sudo apt-get install libcairo2-dev libjpeg-dev libgif-dev
sudo apt-get install libgstreamer-plugins-base1.0-dev

-opengl:
sudo apt-get install libglm-dev

-eigen:
download sources and make symlink
sudo ln -s /usr/local/include/ /home/vvirkkal/Libraries/eigen-eigen-323c052e1731



 
Create eclipse-cmake project 
https://cmake.org/Wiki/Eclipse_CDT4_Generator
and import the provided CMakeLists.txt in src folder
to eclipse.
