SET(CMAKE_AUTOMOC TRUE)

ADD_LIBRARY(map ${CMAKE_CURRENT_SOURCE_DIR}/Mapper.cpp ${CMAKE_CURRENT_SOURCE_DIR}/MapContent.cpp
${CMAKE_CURRENT_SOURCE_DIR}/MapVisualizer.cpp
${CMAKE_CURRENT_SOURCE_DIR}/shader.cpp ${PROJECT_SOURCE_DIR}/utils/FileUtils.cpp
${PROJECT_SOURCE_DIR}/utils/StringUtils.cpp
${PROJECT_SOURCE_DIR}/rovercontrol/SensorProcessor.cpp ${PROJECT_SOURCE_DIR}/rovercontrol/WheelEncoder.cpp
${PROJECT_SOURCE_DIR}/rovercontrol/BasicSensor.cpp ${PROJECT_SOURCE_DIR}/quaternions/Quaternions.cpp)

SET_TARGET_PROPERTIES(map PROPERTIES COMPILE_FLAGS "-std=c++11 -O2 -fno-inline-functions -Wall -Wextra -Wno-unused-parameter -fPIC")
TARGET_LINK_LIBRARIES(map  ${Qt5Gui_LIBRARIES} ${Qt5Core_LIBRARIES} ${Qt5Widgets_LIBRARIES} ${GStreamer_LIBRARIES}
${OPENGL_LIBRARY} GLEW configuration)
