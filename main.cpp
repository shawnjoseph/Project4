#include <iostream>
#include "Graph.h"
using namespace std;

int main() {

    Graph<double> * graph = new Graph<double>(); //HashTable and AdjacencyList is built with type double
    graph->buildGraph(); //Fill HashTable and AdjacencyList with Nodes and their data
    graph->empty();
//    cout << "Let's Get Down To Business" << endl;
    return 0;
}