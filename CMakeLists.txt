cmake_minimum_required(VERSION 3.4)
project(ffmpeg_test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -v")
set(CMAKE_EXE_LINKER_FLAGS "-std=c++11 -Wl -v")

set(CMAKE_EXE_LINKER_FLAGS "-v")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

find_package(FFMPEG REQUIRED)
include_directories(SYSTEM ${FFMPEG_INCLUDE_DIR}) # use SYSTEM to suppress FFMPEG compile warnings

set(
        SOURCE_FILES
        main.cpp
        src/AVFormat/Context.cpp
        src/AVFormat/Context.h
        src/AVCodec/Codec.cpp
        src/AVCodec/Codec.h
        src/FFmpeg.h
        src/CFFmpeg.h)

add_executable(ffmpeg_test ${SOURCE_FILES})

MESSAGE(${FFMPEG_LIBRARIES})
target_link_libraries(ffmpeg_test ${FFMPEG_LIBRARIES})
