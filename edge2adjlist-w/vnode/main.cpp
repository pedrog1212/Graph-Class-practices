#include <iostream>
#include <vector>
#include <list>
using namespace std;

struct vnode {
    int vertex;
    vnode* next;
};

typedef vnode* vnodeptr;

vector<vnodeptr> EdgeList2AdjList(int numNodes, const vector<pair<int, int>>& edgeList) {
    vector<vnodeptr> adjList(numNodes, nullptr); 

    for (const auto& edge : edgeList) {
        int u = edge.first;
        int v = edge.second;

        vnodeptr newNodeU = new vnode{v, adjList[u]};
        adjList[u] = newNodeU;

        vnodeptr newNodeV = new vnode{u, adjList[v]};
        adjList[v] = newNodeV;
    }

    return adjList;
}

int main() {
    vector<pair<int, int>> edgeList = {{0, 1}, {1, 2}, {1, 3}, {2, 3}, {2, 5}, {3, 4}, {3, 6}};
    int numNodes = 7;

    vector<vnodeptr> adjList = EdgeList2AdjList(numNodes, edgeList);

    cout << "Traversal:\n";
    for (int i = 0; i < adjList.size(); i++) {
        cout << "Node " << i << ": ";
        
        vnodeptr temp = adjList[i];
        
        while (temp != nullptr) {
            cout << temp->vertex << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    return 0;
}
