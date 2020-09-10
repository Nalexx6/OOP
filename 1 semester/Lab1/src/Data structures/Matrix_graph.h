//
// Created by Win10Pro on 08.09.2020.
//

#ifndef LAB1_MATRIX_GRAPH_H
#define LAB1_MATRIX_GRAPH_H

#include "Graph.h"

template <typename V, typename E>
class Matrix_graph : public Graph<V, E>{

private:

    //variables
    std::vector<V> vertices; //list of our vertices
    std::vector<std::vector<E*>> adj; //adjacency matrix
    int edges;
    bool directed;
    bool weighted;

    //private algorithms for corresponding methods
    void dfs(const int& v, bool* visited){

        if(visited[v] != 0)
            return;
        visited[v] = true;

        for(int i = 0; i < this->vertices.size(); i++){
            if(this->adj[v][i] != nullptr){
                dfs(i, visited);
            }
        }

    }
    void bfs(int& v, bool* visited){

        std::queue <int> queue;
        visited[v] = true;
        queue.push(v);

        while(!queue.empty()){

            v = queue.front();
            queue.pop();

            for(int i = 0; i < this->vertices.size(); i++){
                if(visited[i] == 0 && this->adj[v][i] != nullptr) {
                    visited[i] = true;
                    queue.push(i);
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

        for(int i = 0; i < this->vertices.size(); i++){
            if(this->adj[cur][i] != nullptr) {
                find_cycle(i, cur, prev, cycles, visited);
            }

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

            for (int i = 0; i < this->vertices.size(); i++) {
                if (this->adj[min][i] != nullptr){
                    if((costs[i] > costs[min] + 1) && !visited[i]) {

                        costs[i] = costs[min] + 1;//there "1" can be replaced by weight of corresponding edge(adj[min][i])

                        distances[i].clear();
                        for(auto j: distances[min])
                            distances[i].emplace_back(j);

                        distances[i].emplace_back(min);

                    }
                }
            }
        }

    }

public:

    //constructor, destructor
    Matrix_graph() : edges(0), directed(false), weighted(false) {};
    explicit Matrix_graph(const bool& directed, const bool& weighted) :  edges(0), directed(directed), weighted(weighted) {};

    ~Matrix_graph() = default;

    //getters
    bool empty() { return this->vertices.empty(); }
    std::vector<V> _vertices() { return this->vertices; }
    int _edges() { return this->edges; }
    bool _directed() { return directed; }
    bool _weighted() { return weighted; }

    //public methods
    void add_vertex(const V& vertex){

        this->vertices.emplace_back(vertex);

        for(int i = 0; i < this->adj.size(); i++){
            this->adj[i].push_back(nullptr);
        }

        this->adj.push_back(std::vector<E*>(vertices.size()));

    }
    void delete_vertex(const V& vertex){

    }
    void add_edge(const V& from, const V& to, E edge){

        E* _edge = &edge;

        this->adj[from][to] = _edge;

        if(!directed)
            this->adj[to][from] = _edge;

        this->edges++;

    }
    void delete_edge(const V& from, const V& to){

        this->adj[from][to] = nullptr;

        if(!directed)
            this->adj[to][from] = nullptr;

        this->edges--;
    }
    void clear(){

        this->vertices.clear();
        this->edges = 0;
        for(auto i: this->adj){
//            for(auto j: i){
//                delete i;
//            }
            i.clear();
        }
        this->adj.clear();

    }
    void print(){

        std::cout<<"   ";
        for(int i = 0; i < this->vertices.size(); i++){
            std::cout<<i<<" ";
        }
        std::cout<<"\n";
        for(int i = 0; i < this->vertices.size(); i++){
            std::cout<<i<<": ";
            for(int j = 0; j < this->vertices.size(); j++){
                if(adj[i][j] != nullptr)
                    std::cout<<"+ ";
                else
                    std::cout<<"N ";
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
    std::vector<int> dijkstra_distance(const V& from, const V& to){

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


#endif //LAB1_MATRIX_GRAPH_H
