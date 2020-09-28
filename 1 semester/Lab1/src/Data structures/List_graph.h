//
// Created by Win10Pro on 08.09.2020.
//

#ifndef LAB1_LIST_GRAPH_H
#define LAB1_LIST_GRAPH_H

#include "Graph.h"
#include <set>

template <typename V, typename E>
class List_graph : public Graph<V, E>{

    class Edge{
    public:
        int vertex{};
        E edge;

        Edge(const int& vertex, const E& edge){

            this->vertex = vertex;
            this->edge = edge;

        }

    };

    //variables
    std::vector<V> vertices; //list of our vertices
    std::vector<std::vector<Edge>> adj; //adjacency list
    int edges;
    bool directed;
    bool weighted;

    //private algorithms for corresponding methods
    void dfs(const int& v, bool* visited){

        if(visited[v])
            return;
        visited[v] = true;

        for(auto& i: adj[v]){

            dfs(i.vertex, visited);

        }

    }
    void bfs(int& v, bool* visited){

        std::queue <int> queue;
        visited[v] = true;
        queue.push(v);

        while(!queue.empty()){

            v = queue.front();
            queue.pop();

            for(auto& i: adj[v]){
                if(!visited[i.vertex]) {
                    visited[i.vertex] = true;
                    queue.push(i.vertex);
                }
            }

        }

    }
    void find_cycle(const int& cur, const int& prev, const int& prev_prev, int& cycles, int* visited){

        if(visited[cur] != 0){
            if(visited[cur] == 1) {
                if (directed || cur != prev_prev) {
                    cycles++;
                }
//            std::cout<< v <<"\t"<<prev<<"\t"<< cycles << "\n";
            }
            return;
        }

        visited[cur]++;

        for(auto& i: adj[cur]){

            find_cycle(i.vertex, cur, prev, cycles, visited);

        }

        visited[cur]++;

    }
    void find_distance(const int& from, std::vector<int>* distances, bool* visited, int* costs, int& sum_visited){

        int min = from;

        while(sum_visited < this->vertices.size()) {

            for(int i = 0; i < this->vertices.size(); i++){
                if(!visited[i]){
                    min = i;
                    break;
                }
            }

            for (int i = 0; i < this->vertices.size(); i++) {
                if ((costs[i] < costs[min] && !visited[i]) || (i == from && !visited[from])) {
                    min = i;
                }
            }
//            std::cout<<min<<"\n";
            visited[min] = true;
            sum_visited++;

            for (auto& i: adj[min]) {

                if((costs[i.vertex] > costs[min] + 1) && !visited[i.vertex]) {

                    costs[i.vertex] = costs[min] + 1;//there "1" can be replaced by weight of corresponding edge(adj[min][i])

                    distances[i.vertex].clear();
                    for(auto j: distances[min])
                        distances[i.vertex].emplace_back(j);

                    distances[i.vertex].emplace_back(min);

                }

            }
        }

    }


public:

    //constructor, destructor
    List_graph() : edges(0), directed(false), weighted(false) {};
    explicit List_graph(const bool& directed, const bool& weighted) :  edges(0), directed(directed), weighted(weighted) {};

    ~List_graph() = default;

    //getters
    bool empty() { return this->vertices.empty(); }
    std::vector<V> _vertices() { return this->vertices; }
    int _edges() { return this->edges; }
    bool _directed() { return this->directed; }
    bool _weighted() { return this->weighted; }

    //public methods
    void add_vertex(const V& vertex) {

        this->vertices.emplace_back(vertex);

        std::vector<Edge> new_vertex;
        this->adj.emplace_back(new_vertex);


    }
    void delete_vertex(const V& vertex){

        int index;
        for(std::size_t i = 0; i < vertices.size(); i++){

            if(vertices[i] == vertex){
                vertices.erase(vertices.begin() + i);
                index = i;
                break;

            }
        }

        adj.erase(adj.begin() + index);

        for(auto& j: adj){
            for(std::size_t i = 0; i < j.size(); i++){

                if(j[i].vertex == index){
                    j.erase(j.begin() + i);
                    break;
                }

            }
        }

    }
    void add_edge(const int& from, const int& to, E edge){


        this->adj[from].emplace_back(Edge(to, edge));

        if(!this->directed){

            this->adj[to].emplace_back(Edge(from, edge));

        }

        edges++;

    }
    void delete_edge(const int& from, const int& to){

        for(std::size_t i = 0; i < adj[from].size(); i++){

            if(adj[from][i].vertex == to)
                this->adj[from].erase(adj[from].begin() + i);


        }

        if(!this->directed){

            for(std::size_t i = 0; i < adj[to].size(); i++){

                if(adj[to][i].vertex == from)
                    this->adj[to].erase(adj[to].begin() + i);


            }

        }

    }
    void clear() {

        this->vertices.clear();
        this->edges = 0;
        for(auto i: this->adj){

            i.clear();
        }
        this->adj.clear();

    }
    void print() {

        for(int i = 0; i < this->vertices.size(); i++){
            std::cout<<"Vertex "<<i<<" adjacent with vertices:\t";
            for(int j = 0; j < adj[i].size(); j++){

                std::cout<< adj[i][j].vertex <<"\t";

            }
            std::cout<<"\n";

        }


    }

    int dfs(){

        bool* visited = new bool[vertices.size()];
        for(int i = 0; i < vertices.size(); i++){
            visited[i] = false;
        }

        int components = 0;
        for(int i = 0; i < vertices.size(); i++){
            if(!visited[i]) {
                dfs(i, visited);
                components++;
            }
        }

        delete[] visited;
        return components;

    }
    int bfs(){

        bool* visited = new bool[vertices.size()];
        for(int i = 0; i < vertices.size(); i++){
            visited[i] = false;
        }

        int components = 0;
        for(int i = 0; i < vertices.size(); i++){
            if(!visited[i]) {
                bfs(i, visited);
                components++;
            }
        }

        delete[] visited;
        return components;

    }
    int acyclicity(){

        int cycles = 0;
        int* visited = new int [this->vertices.size()];
        for(int i = 0; i < this->vertices.size(); i++){
            visited[i] = 0;
        }

        for(int i = 0; i < this->vertices.size(); i++){
            if(visited[i] == 0){
                find_cycle(i, -1, -1, cycles, visited);
            }
        }

        delete[] visited;
        return cycles;

    }
    std::vector<int> dijkstra_distance(const int& from, const int& to){

        auto* distances = new std::vector <int> [this->vertices.size()];

        bool* visited = new bool[this->vertices.size()];
        int* costs = new int [this->vertices.size()];
        int sum_visited = 0;

        for(int i = 0; i < this->vertices.size(); i++){
            visited[i] = false;
            costs[i] = -1;
        }

        dfs(from, visited);//defines set of vertices, which are in the same connectivity component as the vertex "from"

        for(int i = 0; i < this->vertices.size(); i++){
            if(!visited[i]){
                visited[i] = true;
                sum_visited++;

            }
            else{
                visited[i] = false;
                costs[i] = INT32_MAX;

            }
        }

        costs[from] = 0;
        if(costs[to] == -1)
            return distances[to];

        find_distance(from, distances, visited, costs, sum_visited);

        delete[] visited;
        delete[] costs;
        return distances[to];

    }

};


#endif //LAB1_LIST_GRAPH_H
