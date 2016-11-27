ADD_EXECUTABLE(utils-test StringUtilsTest.cpp ${PROJECT_SOURCE_DIR}/utils/StringUtils.cpp)
TARGET_LINK_LIBRARIES(utils-test gtest gtest_main)
SET_TARGET_PROPERTIES(utils-test PROPERTIES COMPILE_FLAGS "-std=c++11 -O2 -fno-inline-functions -Wall -Wextra -Wno-unused-parameter")

ADD_EXECUTABLE(wheelencoder-test WheelEncoderTest.cpp ${PROJECT_SOURCE_DIR}/utils/FileUtils.cpp)
TARGET_LINK_LIBRARIES(wheelencoder-test gtest gtest_main)
SET_TARGET_PROPERTIES(wheelencoder-test PROPERTIES COMPILE_FLAGS "-std=c++11 -O2 -fno-inline-functions -Wall -Wextra -Wno-unused-parameter")
ADD_TEST(test-wheelencoder wheelencoder-test)

