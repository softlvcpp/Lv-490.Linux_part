cmake_minimum_required(VERSION 3.16)
project(SoftwareGenius)
set(CMAKE_CXX_COMPILER, "/usr/bin/g++-8")
set(CMAKE_CXX_STANDARD 17)


add_subdirectory("Server")
if (NOT TARGET "LoggerLibrary" AND NOT TARGET "LoggerLibrary-d")
	add_subdirectory("Utility/Logger/")
endif()
