#include <iostream>
#include "Vertex.h"
#include "Edge.h"
#include "HashTable.h"
using namespace std;

const int MIN = 20;

template <class Type> class Graph {
private:
    HashTable<string, Type> * graph;
    int numEdges = 0;
public:
    Graph(){
        graph = new HashTable<string, Type>();
    }
    ~Graph(){
        graph->~HashTable();
    }
    bool empty(){ graph->numOfEntries == 0 ? cout << "Graph is empty." : "Graph is not empty."; }
    int degree(string v){
        graph->search(v);
    }
};
