cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project( predator )

SET (CMAKE_CXX_COMPILER  "/usr/bin/clang++")
SET (CMAKE_CXX_FLAGS "-Wall --std=c++11")

set(OpenCV_DIR "/opt/opencv244/share/OpenCV/")

find_package( OpenCV REQUIRED )

add_library(tracker lktracker.cpp)
target_link_libraries( tracker ${OpenCV_LIBS}) 

add_executable( lk lkdemo.cpp )
target_link_libraries( lk tracker ${OpenCV_LIBS}) 

add_executable( main main.cpp )
target_link_libraries( main ${OpenCV_LIBS}) 

