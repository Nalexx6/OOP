cmake_minimum_required(VERSION 3.15)
project(Lab1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab1 main.cpp "src/Data structures/Graph.h" "src/Data structures/Matrix_graph.h" "src/Data structures/List_graph.h"
        src/Figures/Functions.cpp src/Figures/Functions.h src/Figures/Circle.h src/Figures/Line.h
        src/Figures/Circle.cpp src/Figures/Line.cpp src/Figures/Point.cpp src/Figures/Point.h
        src/doctest.h UnitTests/Graphs_tests.cpp UnitTests/FiguresTests.cpp)