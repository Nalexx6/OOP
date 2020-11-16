cmake_minimum_required(VERSION 3.17)
project(opencv_test)

set(CMAKE_CXX_STANDARD 20)


find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
message(STATUS ${OpenCV_INCLUDE_DIRS})

add_executable(opencv_test main.cpp)

## add libs you need
#set(OpenCV_LIBS -opencv_core -opencv_imgproc -opencv_highgui -opencv_imgcodecs)

target_link_libraries( opencv_test ${OpenCV_LIBS} )
