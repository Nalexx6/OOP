//
// Created by Win10Pro on 29.09.2020.
//

#include "Matrix_graph.h"
#include "List_graph.h"
#include "../Objects/Circle.h"
#include "../Objects/Line.h"

#include "../doctest.h"

namespace test_graph_functions{

    void test_matrix_graph(){

        auto *matrixGraph = new Matrix_graph<int, int>(false, false);

        matrixGraph->add_vertex(0);
        matrixGraph->add_vertex(1);
        matrixGraph->add_vertex(2);
        matrixGraph->add_vertex(3);
        matrixGraph->add_vertex(4);
        matrixGraph->add_vertex(5);

        CHECK(matrixGraph->_vertices().size() == 6);

        matrixGraph->add_edge(0, 2, 0);
        matrixGraph->add_edge(1, 2, 0);
        matrixGraph->add_edge(1, 3, 0);
        matrixGraph->add_edge(1, 4, 0);

        //checking that graph has 2 connectivity components, by using dfs algorithm
        CHECK(matrixGraph->dfs() == 2);

        matrixGraph->add_edge(4, 5, 0);

        //checking that graph has 1 connectivity component, by using bfs algorithm
        CHECK(matrixGraph->bfs() == 1);

        CHECK(matrixGraph->acyclicity() == 0);
        matrixGraph->add_edge(0, 1, 0);
        matrixGraph->add_edge(0, 3, 0);

        //checking amount of cycles
        CHECK(matrixGraph->acyclicity() == 2);

        CHECK(matrixGraph->_edges() == 7);
        matrixGraph->delete_vertex(3);

        //check change of amount of edges after deleting vertex
        CHECK(matrixGraph->_edges() == 5);

        std::vector<int> res = matrixGraph->dijkstra_distance(0, 3);

        //check the dijkstra path for correctness
        CHECK(res.size() == 2);
        CHECK(res[0] == 0);
        CHECK(res[1] == 1);

    }

    void test_list_graph(){

        auto *listGraph = new List_graph<int, int>(false, false);

        listGraph->add_vertex(0);
        listGraph->add_vertex(1);
        listGraph->add_vertex(2);
        listGraph->add_vertex(3);
        listGraph->add_vertex(4);
        listGraph->add_vertex(5);

        CHECK(listGraph->_vertices().size() == 6);

        listGraph->add_edge(0, 2, 0);
        listGraph->add_edge(1, 2, 0);
        listGraph->add_edge(1, 3, 0);
        listGraph->add_edge(1, 4, 0);

        //checking that graph has 2 connectivity components, by using dfs algorithm
        CHECK(listGraph->dfs() == 2);

        listGraph->add_edge(4, 5, 0);

        //checking that graph has 1 connectivity component, by using bfs algorithm
        CHECK(listGraph->bfs() == 1);

        CHECK(listGraph->acyclicity() == 0);
        listGraph->add_edge(0, 1, 0);
        listGraph->add_edge(0, 3, 0);

        //checking amount of cycles
        CHECK(listGraph->acyclicity() == 2);

        CHECK(listGraph->_edges() == 7);
        listGraph->delete_vertex(3);

        //check change of amount of edges after deleting vertex
        CHECK(listGraph->_edges() == 5);

        std::vector<int> res = listGraph->dijkstra_distance(0, 3);

        //check the dijkstra path for correctness
        CHECK(res.size() == 2);
        CHECK(res[0] == 0);
        CHECK(res[1] == 1);

    }




}

TEST_CASE("[graphs] - checking all functions"){

    test_graph_functions::test_matrix_graph();
    test_graph_functions::test_list_graph();

}