#include <iostream>

#include "src/Data structures/Matrix_graph.h"
#include "src/Data structures/List_graph.h"
#include "src/Objects/Functions.h"



int main() {
//    List_graph<int, int> graph(false, false);
//
//    graph.add_vertex(1);
//    graph.add_vertex(2);
//    graph.add_vertex(3);
//    graph.add_vertex(4);
//    graph.add_vertex(5);
//    std::cout<<"fdfd"<<std::endl;
//    graph.add_edge(0, 3, 2);
//    graph.add_edge(3, 4, 2);
//    graph.add_edge(0, 2, 2);
//
//    graph.print();
//
//    graph.delete_edge(0, 3);
//    graph.delete_vertex(5);
//
//    graph.print();
//
//    int a = graph.acyclicity();
//    std::cout<<a<<std::endl;

    auto* circle1 = new Circle(0, 0, 1);
    Line* line1 = new Line(-2, 1, 0);
    Line* line2 = new Line(-3, 1, -1);
    auto* circle2 = new Circle(1, 0, 1);

//    std::vector<Functions::Point> res = Functions::intersection(*line1, *line2);
//
//    for(auto& i: res)
//        std::cout<< i.x << "\t" << i.y << std::endl;
//    std::cout<< "lol" << std::endl;
//
//    res = Functions::intersection(*line1, *circle1);
//
//    for(auto& i: res)
//        std::cout<< i.x << "\t" << i.y << std::endl;
//    std::cout<< "lol"<<std::endl;
//
    Line res = Functions::sym_display(*line1, *line2);

    std::cout<< "a: " << res._a() << "\tb: " << res._b() << "\tc: " << res._c() << std::endl;

    Circle res1 = Functions::sym_display(*line2, *circle1);

    std::cout<< "a: " << res1._a() << "\tb: " << res1._b() << "\tc: " << res1._c() << std::endl;



//    std::vector<int> path = graph.dijkstra_distance(0, 4);

//    std::cout<<path.size()<<std::endl;
//    for(auto i: path){
//        std::cout<< i << " -> ";
//    }




}