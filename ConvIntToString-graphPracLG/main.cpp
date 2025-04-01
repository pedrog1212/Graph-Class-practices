#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <tuple>
#include <unordered_set>
using namespace std;

class Graph {
    int vertices;
    vector<vector<int>> adjList;
    vector<tuple<int, int, unsigned long>> edges;

public:
    Graph(vector<int>& vertexLabels, vector<tuple<int, int, unsigned long>>& edgeTuples) {
        vertices = vertexLabels.size();
        adjList.resize(vertices);

        for (int vertex : vertexLabels)
            addVertex(vertex);

        for (const auto& [from, to, weight] : edgeTuples)
            addEdge(from, to, weight);
    }

    ~Graph() {
        adjList.clear();
        edges.clear();
    }

	void eraseEdge(int u, int v) {
		auto it = find(adjList[u].begin(), adjList[u].end(), v);
		if (it != adjList[u].end())
			adjList[u].erase(it);

		it = find(adjList[v].begin(), adjList[v].end(), u);
		if (it != adjList[v].end())
			adjList[v].erase(it);
	}

	void BFS(int start) {
		vector<bool> visited(vertices, false);
		queue<int> q;

		visited[start] = true;
		q.push(start);

		while (!q.empty()) {
			int current = q.front();
			q.pop();
			cout << current << " ";

			for (int neighbor : adjList[current]) {
				if (!visited[neighbor]) {
					visited[neighbor] = true;
					q.push(neighbor);
				}
			}
		}
		cout << endl;
	}

	void DFS(int start) {
		vector<bool> visited(vertices, false);
		stack<int> s;

		s.push(start);

		while (!s.empty()) {
			int current = s.top();
			s.pop();

			if (!visited[current]) {
				visited[current] = true;
				cout << current << " ";

				for (auto it = adjList[current].rbegin(); it != adjList[current].rend(); ++it) {
					if (!visited[*it]) {
						s.push(*it);
					}
				}
			}
		}
		cout << endl;
	}
	
    // Function to perform DFS
    void dfs1(int start, const vector<vector<int>>& adjList) {
        stack<int> s; // Stack for DFS
        unordered_set<int> visited; // To keep track of visited nodes
        vector<int> traversalOrder; // To store the DFS traversal order
    
        // Push the starting node onto the stack and mark it as visited
        s.push(start);
        visited.insert(start);
    
        while (!s.empty()) {
            // Pop the top node from the stack
            int current = s.top();
            s.pop();
    
            // Process the current node (e.g., add to traversal order)
            traversalOrder.push_back(current);
    
            // Add all unvisited neighbors to the stack in reverse order
            // to maintain the correct DFS behavior
            for (auto it = adjList[current].rbegin(); it != adjList[current].rend(); ++it) {
                if (visited.find(*it) == visited.end()) {
                    s.push(*it);
                    visited.insert(*it);
                }
            }
        }
    
        // Print the traversal order
        cout << "DFS Traversal Order: ";
        for (int node : traversalOrder) {
            cout << node << " ";
        }
        cout << endl;
    }

	vector<vector<int>> matrix2List(const vector<vector<int>>& matrix) {
		int V = matrix.size();
		vector<vector<int>> newAdjList(V);

		for (int i = 0; i < V; ++i) {
			for (int j = 0; j < V; ++j) {
				if (matrix[i][j] == 1) {
					newAdjList[i].push_back(j);
				}
			}
		}

		return newAdjList;
	}

	vector<vector<int>> list2Matrix() {
		vector<vector<int>> matrix(vertices, vector<int>(vertices, 0));

		for (int i = 0; i < vertices; ++i) {
			for (int neighbor : adjList[i]) {
				matrix[i][neighbor] = 1;
			}
		}

		return matrix;
	}

	void setAdjList(const vector<vector<int>>& newAdjList) {
		adjList = newAdjList;
	}

	void addVertex(int label) {
		vertices++;
		adjList.push_back(vector<int>());
	}

	void addEdge(int label1, int  label2, int weight) {
		adjList[label1].push_back(label2);
		adjList[label2].push_back(label1);
	}

	void removeEdge(int  label1, int label2) {
		for (auto it = adjList[label1].begin(); it != adjList[label1].end(); ) {
			if (*it == label2)
				it = adjList[label1].erase(it);
			else
				++it;
		}

		for (auto it = adjList[label2].begin(); it != adjList[label2].end(); ) {
			if (*it == label1)
				it = adjList[label2].erase(it);
			else
				++it;
		}
	}

	void removeVertex(int label) {
		if (label >= vertices)
			return;

		while (!adjList[label].empty())
			removeEdge(label, adjList[label].back());

		for (int i = label; i < vertices - 1; ++i)
			adjList[i] = adjList[i + 1];

		adjList.pop_back();

		for (int i = 0; i < adjList.size(); ++i) {
			for (int& neighbor : adjList[i]) {
				if (neighbor > label)
					--neighbor;
			}
		}
		--vertices;
	}

	void printAdjList() {
		for (int i = 0; i < vertices; ++i) {
			cout << i << ": ";
			for (int neighbor : adjList[i]) {
				cout << neighbor << " ";
			}
			cout << endl;
		}
	}
};



int main() {
    
    std::vector<int> vertices1 = {1, 2, 3, 4, 5, 6};
    
    vector<tuple<int, int, unsigned long>> edgeTuples = 
    {{1, 2, 7}, {1, 3, 9}, {1, 6, 14}, {2, 3,10}, {2, 4, 15}, {3, 4, 11}, {3, 6, 2}, {4, 5, 6}, {5, 6, 9}};
    
	Graph g(vertices1, edgeTuples);
    
	g.printAdjList();

	cout << "\nBFS from vertex 0:" << endl;
	g.BFS(0);

	cout << "\nDFS from vertex 0:" << endl;
	g.DFS(0);

	cout << "\nRemoving edge (1, 4):" << endl;
	g.removeEdge(1, 4);
	g.printAdjList();

	cout << "\nConverting adjacency list to adjacency matrix:" << endl;
	auto matrix = g.list2Matrix();
	for (const auto& row : matrix) {
		for (int val : row) {
			cout << val << " ";
		}
		cout << endl;
	}

/*	cout << "\nConverting adjacency matrix back to adjacency list:" << endl;
	Graph g2(matrix.size());
	g2.setAdjList(g2.matrix2List(matrix));
	g2.printAdjList();

	cout << "\nAdding a new vertex and connecting it to existing vertices:" << endl;
	g2.addVertex(5);
	g2.addEdge(5, 0);
	g2.addEdge(5, 3);
	g2.printAdjList();

	cout << "\nRemoving vertex 2:" << endl;
	g2.removeVertex(2);
	g2.printAdjList();
*/
	return 0;
}
