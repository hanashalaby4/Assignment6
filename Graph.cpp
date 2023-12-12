#include "Graph.h"
#include <iostream>
#include <climits>
#include <vector>
#include <stack>

Graph::Graph(const std::vector<Edge>& edges, int num_vertices, const std::vector<std::string>& city_names)
    : edges(edges), city_names(city_names) {

    adjacency_matrix.resize(v_max, std::vector<int>(v_max, 0));

    for (const Edge& edge : edges) {
        adjacency_matrix[edge.u][edge.v] = edge.w;
        adjacency_matrix[edge.v][edge.u] = edge.w; 
    }
}

void Graph::dfs_helper(int city_index, std::vector<bool>& visited) const {
    visited[city_index] = true;
    std::cout << city_names[city_index] << " ";

    for (int i = 0; i < v_max; ++i) {
        if (adjacency_matrix[city_index][i] && !visited[i]) {
            dfs_helper(i, visited);
        }
    }
}

void Graph::dfs(int start_city_index) const {
    std::vector<bool> visited(v_max, false);
    std::cout << "DFS traversal starting from city " << city_names[start_city_index] << ":\n";
    dfs_helper(start_city_index, visited);
    std::cout << "\n";
}

void Graph::dijkstra(int start_city_index) const {
    int num_cities = city_names.size();

    std::vector<int> distances(num_cities, INT_MAX);
    std::vector<bool> visited(num_cities, false);
    std::vector<int> parents(num_cities, -1);

    distances[start_city_index] = 0;

    for (int i = 0; i < num_cities - 1; ++i) {
        int min_distance_index = get_min_distance(distances, visited);
        visited[min_distance_index] = true;

        for (int j = 0; j < num_cities; ++j) {
            if (!visited[j] && adjacency_matrix[min_distance_index][j] &&
                distances[min_distance_index] != INT_MAX &&
                distances[min_distance_index] + adjacency_matrix[min_distance_index][j] < distances[j]) {
                distances[j] = distances[min_distance_index] + adjacency_matrix[min_distance_index][j];
                parents[j] = min_distance_index;
            }
        }
    }

    std::cout << "\nShortest Paths from Node " << city_names[start_city_index] << "\n";
    for (int i = 0; i < num_cities; ++i) {
        std::cout << "" << distances[i] << " " << city_names[start_city_index];
        print_path(parents, i);
        std::cout << "\n";
    }
}

int Graph::get_min_distance(const std::vector<int>& distances, const std::vector<bool>& visited) const {
    int min_distance = INT_MAX, min_distance_index = -1;
    int num_cities = distances.size();

    for (int i = 0; i < num_cities; ++i) {
        if (!visited[i] && distances[i] <= min_distance) {
            min_distance = distances[i];
            min_distance_index = i;
        }
    }

    return min_distance_index;
}

void Graph::print_path(const std::vector<int>& parents, int current_city_index) const {
    if (parents[current_city_index] == -1) {
        return;
    }

    print_path(parents, parents[current_city_index]);
    std::cout << "" << city_names[current_city_index];
}
