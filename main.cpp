#include <iostream>
#include "Graph.h"
using namespace std;

int main() {

    Graph<double> * graph = new Graph<double>();
    graph->empty();
    graph->buildGraph();
    cout << "Let's Get Down To Business" << endl;
    return 0;
}