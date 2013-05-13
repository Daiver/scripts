cmake_minimum_required (VERSION 2.6)
project (main)

add_library(Test test.cpp)

add_executable(main main.cpp)
target_link_libraries (main Test)

