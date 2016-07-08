#pragma once
#include <iostream>
#include <limits>
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
    bool empty(){
        if(graph->numOfEntries == 0){
            cout << "Graph is empty." << endl;
        }
        else{
            cout << "Graph is not empty." << endl;
        }
        return graph->numOfEntries == 0;
    }
    void buildGraph(){

    }
    void insert(string u, string v, double w){
        if(w > 0 || w == numeric_limits::infinity()){
            cerr << "Weight is invalid." << endl;
        }
        else if ( w == 0){
            Vertex<Name,Data> * U;
            Vertex<Name, Data> * V;
            U = graph->search(u);
            V = graph->search(v);


        }
    }
};
