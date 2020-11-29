cmake_minimum_required(VERSION 3.17)
project(opencv_project)

set(CMAKE_CXX_STANDARD 20)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
message(STATUS ${OpenCV_INCLUDE_DIRS})

add_executable(opencv_project main.cpp)

target_link_libraries( opencv_project ${OpenCV_LIBS} )
