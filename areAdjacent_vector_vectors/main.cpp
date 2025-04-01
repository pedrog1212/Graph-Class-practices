#include <iostream>
#include <vector>
#include <algorithm>  // For std::find

bool areAdjacent(int u, int v, const std::vector<std::vector<int>>& adjList) {
    // Check if v is in the adjacency list of u
    auto it = std::find(adjList[u].begin(), adjList[u].end(), v);
    return it != adjList[u].end();
}

int main() {
    // Example graph with 4 vertices
    std::vector<std::vector<int>> adjList = {
        {1, 2},    // Neighbors of vertex 0
        {0, 2},    // Neighbors of vertex 1
        {0, 1, 3}, // Neighbors of vertex 2
        {2}        // Neighbors of vertex 3
    };

    int u = 3, v = 2;
    
    if (areAdjacent(u, v, adjList)) {
        std::cout << "Vertices " << u << " and " << v << " are adjacent.\n";
    } else {
        std::cout << "Vertices " << u << " and " << v << " are not adjacent.\n";
    }

    return 0;
}
