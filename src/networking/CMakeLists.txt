set(SOURCE
   ${SOURCE}
   ${CMAKE_CURRENT_SOURCE_DIR}/TcpSocket.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/BufferedSocketReader.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/TcpReceiver.cpp
   PARENT_SCOPE
)

#ADD_EXECUTABLE(socket-test SocketTest.cpp TcpSocket.cpp BufferedSocketReader.cpp TcpReceiver.cpp)
#SET_TARGET_PROPERTIES(socket-test PROPERTIES COMPILE_FLAGS "-std=c++11 -O2 -fno-inline-functions -Wall -Wextra -Wno-unused-parameter")
#TARGET_LINK_LIBRARIES(socket-test pthread)