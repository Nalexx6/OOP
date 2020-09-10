#include <iostream>

#include "src/Data structures/Matrix_graph.h"

int main() {
    Matrix_graph<int, int> graph(false, false);

    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);
    graph.add_vertex(4);
    graph.add_vertex(5);
//    std::cout<<"fdfd"<<std::endl;
    graph.add_edge(0, 3, 2);
    graph.add_edge(3, 4, 2);
    graph.add_edge(0, 2, 2);

    graph.print();

    std::vector<int> path = graph.dijkstra_distance(0, 4);

    std::cout<<path.size()<<std::endl;
    for(auto i: path){
        std::cout<< i << " -> ";
    }




}