################################################################
Приклад додавання вже зкомпільованого логера до проекту CMake
################################################################

add_[executable, library](my[Exec/Lib])

...

set(LoggerLibFiles [відносний шлях]/Logger/LibraryFiles)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(LoggerLibFolder "${LoggerLibFiles}/Debug")
    set(LoggerLib "libLoggerLibrary-d.so")
else()
    set(LoggerLibFolder "${LoggerLibFiles}")
    set(LoggerLib "libLoggerLibrary.so")
endif ()

...

target_include_directories(my[Exec/Lib]
	...
        PUBLIC "${LoggerLibFiles}/include")

target_link_directories(my[Exec/Lib]
	...
        PUBLIC ${LoggerLibFolder})

target_link_libraries(my[Exec/Lib]
	...
        PUBLIC "${LoggerLib}")

################################################################
В коді
#################################################################
#include "[відносний шлях]/Logger/LibraryFiles]/LoggerSHARED.h"

