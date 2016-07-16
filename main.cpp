#include <iostream>
#include "Graph.h"
#include "Digraph.h"

using namespace std;

int main() {

    cout << "This is diGraph start" << endl;
//    Digraph<double> *diGraph = new Digraph<double>(); //HashTable and AdjacencyList is built with type double
//    diGraph->buildGraph(); //Fill HashTable and AdjacencyList with Nodes and their data
//    diGraph->display();
//    double adjacent = diGraph->adjacent("China", "Singapore");
//    cout << adjacent << endl;

//    int indegree = diGraph->indegree("United_States");
//    cout << "indegree: " << indegree << endl;

//    cout << endl << "WHAT DAT BOOTY DO DOE MARK?????" << endl;
//    cout << endl;
//    diGraph->DFS("United_States");





//    cout << "This is graph start" << endl;

    Graph<double> *graph = new Graph<double>(); //HashTable and AdjacencyList is built with type double
    graph->buildGraph(); //Fill HashTable and AdjacencyList with Nodes and their data
//    graph->display();
//    cout << graph->edgeCount();
    graph->clear();
    graph->display();
    return 0;
}