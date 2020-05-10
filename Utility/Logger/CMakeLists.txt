cmake_minimum_required(VERSION 3.16)
project(LoggerLibrary)

set(CMAKE_CXX_STANDARD 17)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(OutputFile LoggerLibrary-d)
    message("Debug filename: " "${OutputFile}")
else()
    set(OutputFile LoggerLibrary)
    message("Default filename: " "${OutputFile}")
endif ()

add_library("${OutputFile}" SHARED
        LoggerSHARED.h

        src/ExportConfig.h
        src/ILogger.h
        src/LoggerImplementation.h
        src/StaticLogging.h
        src/LoggerLibrary.h

        src/LibraryImplementation/Essentials/LogFundamentals.h
        src/LibraryImplementation/Filelogger/filelogger.h
        src/LibraryImplementation/Filelogger/filelogger_Messages.h
        src/LibraryImplementation/Filelogger/filelogger_StreamModes.h

        src/LibraryImplementation/Filelogger/Lv490XMLServer/XMLParserConfigConverter.h
        src/LibraryImplementation/Filelogger/Utility/ConcQueue.h

        src/LibraryImplementation/Essentials/LogFundamentals.cpp
        src/LibraryImplementation/Filelogger/filelogger.cpp
        src/LibraryImplementation/Filelogger/filelogger_FileManager.cpp
        src/LibraryImplementation/Filelogger/filelogger_Messages.cpp
        src/LibraryImplementation/Filelogger/filelogger_StreamModes.cpp
        src/LibraryImplementation/Filelogger/StaticFilelogger.cpp)

target_link_libraries("${OutputFile}"
        PUBLIC stdc++fs
        PUBLIC -pthread)
