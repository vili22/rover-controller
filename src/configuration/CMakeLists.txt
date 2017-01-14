#set(SOURCE
#   ${SOURCE}
#   ${CMAKE_CURRENT_SOURCE_DIR}/Configuration.cpp
#   ${CMAKE_CURRENT_SOURCE_DIR}/ConfigurationEntry.cpp
#   PARENT_SCOPE
#)
ADD_LIBRARY(configuration ${CMAKE_CURRENT_SOURCE_DIR}/Configuration.cpp ${CMAKE_CURRENT_SOURCE_DIR}/ConfigurationEntry.cpp)

SET_TARGET_PROPERTIES(configuration PROPERTIES COMPILE_FLAGS "-std=c++11 -O2 -fno-inline-functions -Wall -Wextra -Wno-unused-parameter -fPIE")
