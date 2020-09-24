//
// Created by Win10Pro on 08.09.2020.
//

#ifndef LAB1_GRAPH_H
#define LAB1_GRAPH_H

#include <iostream>
#include <vector>
#include <map>
#include <queue>



template <typename V, typename E>
class Graph {

private:

    //private algorithms for corresponding methods
    virtual void dfs(const int& v, bool* visited) = 0;
    virtual void bfs(int& v, bool* visited) = 0;
    virtual void find_cycle(const int& cur, const int& prev, const int& prev_prev, int& cycles, int* visited) = 0;
    virtual void find_distance(const int& from, std::vector<int>* distances, bool* visited, int* costs, int& sum_visited) = 0;


public:

    //constructor, destructor
    Graph() = default;
    virtual ~Graph() = default;

    //getters
    virtual bool empty() = 0;
    virtual std::vector<V> _vertices() = 0;
    virtual int _edges() = 0;
    virtual bool _directed() = 0;
    virtual bool _weighted() = 0;

    //public methods
    virtual void add_vertex(const V& vertex) = 0;
    virtual void delete_vertex(const V& vertex) = 0;
    virtual void add_edge(const V& from, const V& to, E edge) = 0;
    virtual void delete_edge(const V& from, const V& to) = 0;
    virtual void clear() = 0;
    virtual void print() = 0;

    virtual int dfs() = 0;
    virtual int bfs() = 0;
    virtual int acyclicity() = 0;
    virtual std::vector<int> dijkstra_distance(const V& from, const V& to) = 0;

}; //class Graph


#endif //LAB1_GRAPH_H
