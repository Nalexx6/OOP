cmake_minimum_required(VERSION 3.15)
project(Lab1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab1 main.cpp "src/Data structures/Graph.h" "src/Data structures/Matrix_graph.h" "src/Data structures/List_graph.h"
        src/doctest.h src/UnitTests/Graphs_tests.cpp src/UnitTests/FiguresTests.cpp)

add_subdirectory("src/Figures")

target_link_libraries(Lab1 Figures)