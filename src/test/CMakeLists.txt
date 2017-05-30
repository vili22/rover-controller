ADD_EXECUTABLE(utils-test StringUtilsTest.cpp ${PROJECT_SOURCE_DIR}/utils/StringUtils.cpp)
TARGET_LINK_LIBRARIES(utils-test gtest gtest_main)
SET_TARGET_PROPERTIES(utils-test PROPERTIES COMPILE_FLAGS "-std=c++11 -O2 -fno-inline-functions -Wall -Wextra -Wno-unused-parameter")

ADD_EXECUTABLE(wheelencoder-test WheelEncoderTest.cpp ${PROJECT_SOURCE_DIR}/utils/FileUtils.cpp ${PROJECT_SOURCE_DIR}/utils/StringUtils.cpp
${PROJECT_SOURCE_DIR}/rovercontrol/SensorProcessor.cpp ${PROJECT_SOURCE_DIR}/rovercontrol/WheelEncoder.cpp
${PROJECT_SOURCE_DIR}/rovercontrol/BasicSensor.cpp ${PROJECT_SOURCE_DIR}/quaternions/Quaternions.cpp)
SET_TARGET_PROPERTIES(wheelencoder-test PROPERTIES COMPILE_FLAGS "-std=c++11 -O0 -g -fno-inline-functions -Wall -Wextra -Wno-unused-parameter")
TARGET_LINK_LIBRARIES(wheelencoder-test gtest gtest_main configuration map)
ADD_TEST(test-wheelencoder wheelencoder-test)

ADD_EXECUTABLE(map-visualizer-test MapVisualizerTest.cpp)
TARGET_LINK_LIBRARIES(map-visualizer-test configuration map)
SET_TARGET_PROPERTIES(map-visualizer-test PROPERTIES COMPILE_FLAGS "-std=c++11 -O0 -g -fno-inline-functions -Wall -Wextra -Wno-unused-parameter")

