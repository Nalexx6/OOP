#include <iostream>

#include "src/Data structures/Matrix_graph.h"
#include "src/Data structures/List_graph.h"


int main() {
    List_graph<int, int> graph(false, false);

    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);
    graph.add_vertex(4);
    graph.add_vertex(5);
    std::cout<<"fdfd"<<std::endl;
    graph.add_edge(0, 3, 2);
    graph.add_edge(3, 4, 2);
    graph.add_edge(0, 2, 2);

    graph.print();

    graph.delete_edge(0, 3);
    graph.delete_vertex(5);

    graph.print();

    int a = graph.acyclicity();
    std::cout<<a<<std::endl;

//    std::vector<int> path = graph.dijkstra_distance(0, 4);

//    std::cout<<path.size()<<std::endl;
//    for(auto i: path){
//        std::cout<< i << " -> ";
//    }




}