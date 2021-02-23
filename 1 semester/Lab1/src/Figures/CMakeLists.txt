cmake_minimum_required(VERSION 3.17)
project(Figures)

set(CMAKE_CXX_STANDARD 14)

add_library(Figures STATIC include/Figures/Point.h include/Figures/Point.cpp
        include/Figures/Circle.h include/Figures/Circle.cpp
        include/Figures/Line.h include/Figures/Line.cpp
        include/Figures/Functions.h include/Figures/Functions.cpp)

target_include_directories(Figures PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(Figures PROPERTIES LINKER_LANGUAGE CXX)