cmake_minimum_required(VERSION 3.15)
project(Server)

set(CMAKE_CXX_STANDARD 20)

add_executable(Server src/main.cpp src/TCPServer.cpp src/TCPServer.h src/PIDController.cpp src/PIDController.h src/IDaemon.h src/ConnectionAcceptor.cpp src/ConnectionAcceptor.h
        src/EventHandler.cpp src/EventHandler.h src/EventHandlerPtr.h src/EventType.h src/ReactorInterface.cpp src/ReactorInterface.h src/ReactorSelectImpl.cpp src/ReactorSelectImpl.h
        src/select.cpp src/select.h)

SET(CMAKE_CXX_FLAGS -pthread)

