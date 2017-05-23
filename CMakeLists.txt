cmake_minimum_required(VERSION 3.6)
project(rest-fileserver)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp HttpServer/HttpServer.h HttpServer/HttpServer.cpp HttpServer/Handlers/HttpHandler.h HttpServer/Handlers/RestHandler.h FileServer/MyRestHandler.h FileServer/FileHelper/FileHelper.cpp FileServer/FileHelper/FileHelper.h)
add_executable(rest-fileserver ${SOURCE_FILES})

project(rest-fileserver_testing)

set(SOURCE_FILES testing.cpp HttpServer/HttpServer.h HttpServer/HttpServer.cpp HttpServer/Handlers/HttpHandler.h HttpServer/Handlers/RestHandler.h FileServer/MyRestHandler.h FileServer/FileHelper/FileHelper.cpp FileServer/FileHelper/FileHelper.h)
add_executable(rest-fileserver_testing ${SOURCE_FILES})