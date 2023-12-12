#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

const int v_max = 50;
const int e_max = v_max * (v_max - 1) / 2;

class Edge {
public:
    int u, v, w;

    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
};

class Graph {
public:
    Graph(const std::vector<Edge>& edges, int vertices, const std::vector<std::string>& city_names);

    void dfs(int start_city_index) const;
    void dijkstra(int start_city_index) const;

private:
    std::vector<std::vector<int>> adjacency_matrix;
    std::vector<Edge> edges;
    std::vector<std::string> city_names;

    void dfs_helper(int city_index, std::vector<bool>& visited) const;
    int get_min_distance(const std::vector<int>& distances, const std::vector<bool>& visited) const;
    void print_path(const std::vector<int>& parents, int current_city_index) const;
};

#endif // GRAPH_H
