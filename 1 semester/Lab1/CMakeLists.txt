cmake_minimum_required(VERSION 3.15)
project(Lab1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab1 main.cpp "src/Data structures/Graph.h" "src/Data structures/Matrix_graph.h" "src/Data structures/List_graph.h" src/Objects/Figure.cpp src/Objects/Figure.h src/Objects/Functions.cpp src/Objects/Functions.h src/Objects/Circle.h src/Objects/Line.h src/doctest.h src/Objects/Circle.cpp src/Objects/Line.cpp)