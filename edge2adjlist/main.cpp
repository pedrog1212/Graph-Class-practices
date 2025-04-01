#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> EdgeList2AdjList(int numNodes, const vector<pair<int, int>>& edgeList) {
    vector<vector<int>> adjList(numNodes);
    
    for(const auto& edge : edgeList) {
        int u = edge.first;
        int v = edge.second;
        
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
    
    return adjList;
}

int main() {
    vector<pair<int, int>> edgeList = {{0, 1}, {1, 2}, {1, 3}, {2, 3}, {2, 5}, {3, 4}, {3, 6}};
    int numNodes = 7; 

    vector<vector<int>> adjList = EdgeList2AdjList(numNodes, edgeList);

    cout << "Traversal:\n";
    for (int i = 0; i < adjList.size(); i++) {
        cout << "Node " << i << ": ";
        for (int neighbor : adjList[i]) {
            cout << neighbor << " ";
        }
        cout << endl;
    }

    return 0;
}
