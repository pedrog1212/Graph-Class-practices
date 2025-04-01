#include <iostream>
#include <vector>
#include <list>
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


int main() {
    
    std::list<vnode> vNodes0;
    
    vnode node0;
    node0.vertex = 2;
    node0.next = nullptr;
    vNodes0.push_front(node0);
    
    vnode node1;
    node1.vertex = 1;
    node1.next = &node0;
    vNodes0.push_front(node1);
    
    
    std::list<vnode> vNodes1;
    
    vnode node2;
    node2.vertex = 2;
    node2.next = nullptr;
    vNodes1.push_front(node2);
    
    vnode node3;
    node3.vertex = 0;
    node3.next = &node2;
    vNodes1.push_front(node3);


    std::list<vnode> vNodes2;
    vnode node4;
    node4.vertex = 3;
    node4.next = nullptr;
    vNodes2.push_front(node4);
    
    vnode node5;
    node5.vertex = 1;
    node5.next = &node4;
    vNodes2.push_front(node5);
    
    vnode node6;
    node6.vertex = 0;
    node6.next = &node5;
    vNodes2.push_front(node6);

    vector<vnodeptr> adj(3);
    
    adj[0] = &vNodes0.front();
    std::cout << "list 0 head funt front(): " << &vNodes0.front() << std::endl;
    
    adj[1] = &vNodes1.front();
    adj[2] = &vNodes2.front();

    if(adjacent_to(adj, 1, 2))
        std::cout << "1 is adjacent to 2 "<< std::endl;
    else
        std::cout << "1 is NOT adjacent to 2 "<< std::endl;
    
    if(adjacent_to(adj, 1, 3))
        std::cout << "1 is adjacent to 3 "<< std::endl;
    else
        std::cout << "1 is NOT adjacent to 3 "<< std::endl;

    return 0;

}