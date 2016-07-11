#pragma once
#include <iostream>
#include <limits>
#include <fstream>
#include "Vertex.h"
#include "Edge.h"
#include "HashTable.h"
#include "AdjacencyList.h"
using namespace std;

const int MIN = 20;

template <class Type> class Graph {
private:
    HashTable<Type> * graph;
    int numEdges = 0;
    AdjacencyList<Type> * arr;

public:
    Graph<Type>(){
        graph = new HashTable<Type>();
        arr = new AdjacencyList<Type>[MIN];
        // Set all values to NULL as default
        for(int i = 0; i < MIN; i++){
            arr[i].head = NULL;
        }
    }
    ~Graph<Type>(){
        graph->~HashTable();
        delete [] arr;
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
        Graph<double>();
        ifstream file;
        string name;
        double data;
        int i = 0;
        file.open("/home/randomguy/ClionProjects/Project4/AttackMap.txt");
        if (file.is_open()) {
            cout << "File Opened." << endl;
        }
        else {
            cerr << "File could not be opened." << endl;
        }

        while(file){
            if(file.eof()){ break; }
            else{
                file >> name >> data;
                graph->insertValue(name,data); //insertion into HashTable
                arr[i].head = new Vertex<Type>(name,data); //insertion  into Adjacency List
                cout << "ID: " << arr[i].head->getID() << " Name: " << arr[i].head->getName()
                        << " Data: " << arr[i].head->getData() << endl;
                i++;
            }

        }
    }
//    void insert(string u, string v, double w){
//        if(w > 0 || w == numeric_limits<double>::infinity()){
//            cerr << "Weight is invalid." << endl;
//        }
//        else if ( w == 0){
//            Vertex<Data> * U;
//            Vertex<Data> * V;
////            U = graph->search(u);
////            V = graph->search(v);
//        }
//    }
};
