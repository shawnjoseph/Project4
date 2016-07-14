#include <iostream>
#include "Graph.h"
#include "Digraph.h"

using namespace std;

int main() {

    cout << "This is diGraph start" << endl;
    Digraph<double> *diGraph = new Digraph<double>(); //HashTable and AdjacencyList is built with type double
    diGraph->buildGraph(); //Fill HashTable and AdjacencyList with Nodes and their data
    diGraph->display();

    cout << endl << "AWWWW YEAH EVERYBODY" << endl;
    for(int i = 0; i < 6; i++) {
        cout << endl;
    }

    cout << "This is graph start" << endl;

    Digraph<double> *graph = new Digraph<double>(); //HashTable and AdjacencyList is built with type double
    graph->buildGraph(); //Fill HashTable and AdjacencyList with Nodes and their data
    graph->display();


    return 0;
}