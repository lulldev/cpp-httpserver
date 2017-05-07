cmake_minimum_required(VERSION 3.6)
project(cpp-httpserver)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)
add_executable(cpp-httpserver ${SOURCE_FILES})

project(cpp-httpserver_testing)

set(SOURCE_FILES testing.cpp)
add_executable(cpp-httpserver_testing ${SOURCE_FILES})