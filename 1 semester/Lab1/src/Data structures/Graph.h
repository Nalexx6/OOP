//
// Created by Win10Pro on 08.09.2020.
//

#ifndef LAB1_GRAPH_H
#define LAB1_GRAPH_H

#include <iostream>
#include <vector>


template <typename V, typename E>
class Graph {

private:

    //

    //private algorithms for corresponding methods
    virtual void dfs(const V& v) = 0;
    virtual void bfs(const V& v) = 0;
    virtual void find_cycle(const V& cur, const V& prev, const V& prev_prev, int& cycles) = 0;


public:

    //constructor, destructor
    Graph() = default;
    virtual ~Graph() = default;

    //public methods
    virtual void add_vertex(const V& vertex) = 0;
    virtual void delete_vertex(const V& vertex) = 0;
    virtual void add_edge(const V& from, const V& to, const E& edge) = 0;
    virtual void delete_edge(const V& from, const V& to) = 0;

    virtual int dfs() = 0;
    virtual int bfs() = 0;
    virtual int acyclicity() = 0;
   // virtual std::vector<V> dijkstra_distance(const V& from, const V& to) = 0;

};


#endif //LAB1_GRAPH_H
