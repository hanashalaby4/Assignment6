#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

std::vector<std::vector<int>> read_csv(const std::string& file_name) {
    std::ifstream file_stream(file_name);
    std::vector<std::vector<int>> adjacency_matrix;

    if (file_stream.is_open()) {
        std::string line;
        while (std::getline(file_stream, line)) {
            std::istringstream line_stream(line);
            std::vector<int> row;
            int value;

            while (line_stream >> value) {
                row.push_back(value);
                if (line_stream.peek() == ',')
                    line_stream.ignore();
            }

            adjacency_matrix.push_back(row);
        }
        file_stream.close();
    }

    return adjacency_matrix;
}

int main() {
    std::vector<std::vector<int>> test_graph_matrix = read_csv("TestG.txt");
    std::vector<std::vector<int>> cities_graph_matrix = read_csv("CitiesG.txt");

    std::vector<Edge> test_graph_edges;
    std::vector<Edge> cities_graph_edges;

    for (int i = 0; i < test_graph_matrix.size(); ++i) {
        for (int j = 0; j < test_graph_matrix[i].size(); ++j) {
            if (test_graph_matrix[i][j] != 0) {
                test_graph_edges.push_back(Edge(i, j, test_graph_matrix[i][j]));
            }
        }
    }

    for (int i = 0; i < cities_graph_matrix.size(); ++i) {
        for (int j = 0; j < cities_graph_matrix[i].size(); ++j) {
            if (cities_graph_matrix[i][j] != 0) {
                cities_graph_edges.push_back(Edge(i, j, cities_graph_matrix[i][j]));
            }
        }
    }

    Graph test_graph(test_graph_edges, test_graph_matrix.size(), { "A", "B", "C", "D", "E", "F", "G" });
    Graph cities_graph(cities_graph_edges, cities_graph_matrix.size(),
        { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N" });

    test_graph.dfs(0);
    std::cout << std::endl;
    test_graph.dijkstra(0);
    std::cout << std::endl;

    cities_graph.dfs(0);
    std::cout << std::endl;
    cities_graph.dijkstra(0);
    std::cout << std::endl;

    return 0;
}
