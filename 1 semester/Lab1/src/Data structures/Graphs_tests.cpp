//
// Created by Win10Pro on 29.09.2020.
//

#include "Matrix_graph.h"
#include "List_graph.h"

#include "../doctest.h"

namespace test_graph_functions{

    void fillGraphCheck(Graph<int, int>* graph){

        graph->add_vertex(0);
        graph->add_vertex(1);
        graph->add_vertex(2);
        graph->add_vertex(3);
        graph->add_vertex(4);
        graph->add_vertex(5);

        CHECK(graph->_vertices().size() == 6);

        graph->add_edge(0, 2, 0);
        graph->add_edge(1, 2, 0);
        graph->add_edge(1, 3, 0);
        graph->add_edge(1, 4, 0);

        CHECK(graph->_edges() == 4);

    }

    void dfsBfsCheck(Graph<int, int>* graph){

        //checking that graph has 2 connectivity components, by using dfs algorithm
        CHECK(graph->dfs() == 2);

        graph->add_edge(4, 5, 0);

        //checking that graph has 1 connectivity component, by using bfs algorithm
        CHECK(graph->bfs() == 1);

    }

    void acyclicityCheck(Graph<int, int>* graph){

        CHECK(graph->acyclicity() == 0);
        graph->add_edge(0, 1, 0);
        graph->add_edge(0, 3, 0);

        //checking amount of cycles
        CHECK(graph->acyclicity() == 2);

    }

    void deletionCheck(Graph<int, int>* graph){

        CHECK(graph->_edges() == 7);
        graph->delete_vertex(3);

        //check change of amount of edges after deleting vertex
        CHECK(graph->_edges() == 5);

    }

    void dijkstraCheck(Graph<int, int>* graph){

        std::vector<int> res = graph->dijkstra_distance(0, 3);

        //check the dijkstra path for correctness
        CHECK(res.size() == 2);
        CHECK(res[0] == 0);
        CHECK(res[1] == 1);

    }

    void testMatrixGraph(){

        auto *matrixGraph = new Matrix_graph<int, int>(false, false);

        fillGraphCheck(matrixGraph);
        dfsBfsCheck(matrixGraph);
        acyclicityCheck(matrixGraph);
        deletionCheck(matrixGraph);
        dijkstraCheck(matrixGraph);

    }

    void testListGraph(){

        auto *listGraph = new List_graph<int, int>(false, false);

        fillGraphCheck(listGraph);
        dfsBfsCheck(listGraph);
        acyclicityCheck(listGraph);
        deletionCheck(listGraph);
        dijkstraCheck(listGraph);


    }

}

TEST_CASE("[graphs] - checking all functions"){

    test_graph_functions::testMatrixGraph();
    test_graph_functions::testListGraph();

}