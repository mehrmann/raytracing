cmake_minimum_required(VERSION 3.0)

project(raytracing)

set(SOURCE main.cpp)

set(CMAKE_CXX_FLAGS "-stdlib=libc++ -std=gnu++11")

add_executable(${PROJECT_NAME} ${SOURCE})