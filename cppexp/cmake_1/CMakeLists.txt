cmake_minimum_required (VERSION 2.6)
project (main)
SET (CMAKE_CXX_COMPILER  "/usr/bin/clang++")
SET (CMAKE_CXX_FLAGS "-Wall -std=c++11")

add_library(Test test.cpp)

add_executable(main main.cpp)
target_link_libraries (main Test)

