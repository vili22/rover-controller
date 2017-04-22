ADD_LIBRARY(map ${CMAKE_CURRENT_SOURCE_DIR}/glwidget.cpp ${CMAKE_CURRENT_SOURCE_DIR}/logo.cpp ${CMAKE_CURRENT_SOURCE_DIR}/window.cpp ${CMAKE_CURRENT_SOURCE_DIR}/shader.cpp)

SET_TARGET_PROPERTIES(map PROPERTIES COMPILE_FLAGS "-std=c++11 -O2 -fno-inline-functions -Wall -Wextra -Wno-unused-parameter -fPIC")
#TARGET_LINK_LIBRARIES(map ${OPENGL_LIBRARY})
