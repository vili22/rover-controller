PROJECT(rover-controller-system)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
#INCLUDE(FindGStreamer.cmake)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")

FIND_PACKAGE(Qt5Gui REQUIRED)
FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(GStreamer REQUIRED)

INCLUDE_DIRECTORIES(${Qt5Gui_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${Qt5Core_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${Qt5Widgets_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${GStreamer_INCLUDE_DIRS}$)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/gstvideo)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/networking)

SET(CMAKE_AUTOMOC TRUE)

SET(SOURCE ${PROJECT_SOURCE_DIR}/MainWindow.cpp ${PROJECT_SOURCE_DIR}/MessageHandler.cpp)
ADD_SUBDIRECTORY("${PROJECT_SOURCE_DIR}/gstvideo")
ADD_SUBDIRECTORY("${PROJECT_SOURCE_DIR}/networking")
ADD_SUBDIRECTORY("${PROJECT_SOURCE_DIR}/rovercontrol")

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/rovercontrol")

ADD_EXECUTABLE(rover-controller ${SOURCE})
SET_TARGET_PROPERTIES(rover-controller PROPERTIES COMPILE_FLAGS "-std=c++11 -O2 -fno-inline-functions -Wall -Wextra -Wno-unused-parameter -fPIE")
TARGET_LINK_LIBRARIES(rover-controller ${Qt5Gui_LIBRARIES} ${Qt5Core_LIBRARIES}
${Qt5Widgets_LIBRARIES} ${GStreamer_LIBRARIES} pthread)
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") 






