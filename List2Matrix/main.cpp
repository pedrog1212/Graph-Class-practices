#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
using namespace std;

struct vnode {
    int vertex;
    vnode* next;
};

typedef vnode* vnodeptr;

vnodeptr b;

bool adjacent_to(vector<vnodeptr> adj, int i, int j)
{
    int n = adj.size();
    vnode *cursor; 
    
    for(cursor = adj[i]; cursor != nullptr; cursor = cursor->next){
        if(cursor->vertex == j)
            return true;
    }
    
    return false;
}

vector<vector<int> > list2matrix(vector<vnode *> adjlist) 
{ 
    int n  = adjlist.size(); 
    int i;  
    vector<vector<int> > M(n,vector<int>(n,0)); // all entries set to 0 
    vnode *q; // for traversing individual adjacency lists (the "cursor") 
        
    for (int i = 0; i < n; i++) {
        vnode *q = adjlist[i]; 
        
        while (q != nullptr) {
            M[i][q->vertex] = 1; 
            q = q->next; 
        }
    }
    
    return M;  
}

vector<vnode *> matrix2list(vector<vector<int>> M) {
    int n = M.size();
    vector<vnode *> alist(n, nullptr);
    
    for (int i = 0; i < n; i++) {
        vnode *tail = nullptr;

        for (int j = 0; j < n; j++) {
            if (M[i][j] == 1) {
                vnode *newNode = new vnode{j, nullptr};

                if (alist[i] == nullptr)
                    alist[i] = newNode;
                else
                    tail->next = newNode;

                tail = newNode;
            }
        }
    }
    return alist;
}

void BFSWithQueue(vector<vnode *> &adjlist, int start) {
    int n = adjlist.size();
    vector<bool> visited(n, false);
    queue<int> q;

    q.push(start);
    visited[start] = true;
    
    int v;
    while (!q.empty()) {
        v = q.front();
        cout << v << " ";
        q.pop();

        vnode *cursor = adjlist[v];
        while (cursor != nullptr) {
            if (!visited[cursor->vertex]) {
                visited[cursor->vertex] = true;
                q.push(cursor->vertex);
            }
            cursor = cursor->next;
        }
    }
    cout << endl;
}

void DFSWithStack(vector<vnode *> &adjlist, int start) {
    int n = adjlist.size();
    vector<bool> visited(n, false);
    stack<int> s;

    s.push(start);
    visited[start] = true;
    
    int v;
    while (!s.empty()) {
        v = s.top();
        cout << v << " ";
        s.pop();

        vnode *cursor = adjlist[v];
        while (cursor != nullptr) {
            if (!visited[cursor->vertex]) {
                visited[cursor->vertex] = true;
                s.push(cursor->vertex);
            }
            cursor = cursor->next;
        }
    }
    cout << endl;
}

int main() {
    list<vnode> vNodes0;        //Node 0
    vnode node0{1, nullptr};
    vNodes0.push_front(node0);

    list<vnode> vNodes1;        //Node 1
    vnode node1{3, nullptr};
    vNodes1.push_front(node1);

    vnode node2{2, &node1};
    vNodes1.push_front(node2);

    list<vnode> vNodes2;        //Node 2        
    vnode node3{5, nullptr};
    vNodes2.push_front(node3);

    vnode node4{3, &node3};
    vNodes2.push_front(node4);

    list<vnode> vNodes3;        //Node 3
    vnode node5{6, nullptr};
    vNodes3.push_front(node5);

    vnode node6{4, &node5};
    vNodes3.push_front(node6);
    
    vnode node7{2, &node6};
    vNodes3.push_front(node7);
    
    list<vnode> vNodes4;        //Node 4       
    vnode node8{3, nullptr};
    vNodes4.push_front(node8);

    list<vnode> vNodes5;        //Node 5       
    vnode node9{2, nullptr};
    vNodes5.push_front(node9);
    
    list<vnode> vNodes6;        //Node 6       
    vnode node10{3, nullptr};
    vNodes6.push_front(node10);
    
    vector<vnodeptr> adj(7);
    adj[0] = &vNodes0.front();
    adj[1] = &vNodes1.front();
    adj[2] = &vNodes2.front();
    adj[3] = &vNodes3.front();
    adj[4] = &vNodes4.front();
    adj[5] = &vNodes5.front();
    adj[6] = &vNodes6.front();


    if (adjacent_to(adj, 1, 2))
        cout << "1 is adjacent to 2" << endl;
    else
        cout << "1 is NOT adjacent to 2" << endl;

    if (adjacent_to(adj, 1, 3))
        cout << "1 is adjacent to 3" << endl;
    else
        cout << "1 is NOT adjacent to 3" << endl;

    vector<vector<int>> matrix = list2matrix(adj);
    cout << "\nAdjacency Matrix:" << endl;
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    vector<vnode*> adjlist = matrix2list(matrix);
    cout << "\nConverted Back to Adjacency List:" << endl;
    for (int i = 0; i < adjlist.size(); i++) {
        cout << "Vertex " << i << ":";
        vnode *current = adjlist[i];
        while (current != nullptr) {
            cout << " -> " << current->vertex;
            current = current->next;
        }
        cout << endl;
    }
    
    cout << "Traversal BFS: ";
    BFSWithQueue(adj, 0);
    
    cout << "Traversal DFS: ";
    DFSWithStack(adj, 0);
    return 0;
}