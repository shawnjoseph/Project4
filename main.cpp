#include <iostream>
#include "Graph.h"
using namespace std;

int main() {

    Digraph<double> * graph = new Digraph<double>(); //HashTable and AdjacencyList is built with type double
    graph->buildGraph(); //Fill HashTable and AdjacencyList with Nodes and their data

    return 0;
}