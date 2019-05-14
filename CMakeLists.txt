cmake_minimum_required(VERSION 3.0)

project(raytracing)

find_package(FLTK REQUIRED)

set(SOURCE main.cpp)

set(CMAKE_CXX_FLAGS "-std=gnu++11")

add_executable(${PROJECT_NAME} ${SOURCE})
include_directories(${FLTK_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE ${FLTK_LIBRARIES} pthread)