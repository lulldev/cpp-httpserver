cmake_minimum_required(VERSION 3.6)
project(cpp-httpserver)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp HttpServer/HttpServer.h HttpServer/HttpServer.cpp HttpServer/HttpHandler.h HttpServer/HttpRestHandler.h)
add_executable(cpp-httpserver ${SOURCE_FILES})

project(cpp-httpserver_testing)

set(SOURCE_FILES testing.cpp HttpServer/HttpServer.h HttpServer/HttpServer.cpp HttpServer/HttpHandler.h HttpServer/HttpRestHandler.h)
add_executable(cpp-httpserver_testing ${SOURCE_FILES})