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
    static int numEdges = 0;
    AdjacencyList<Type> * arr;

public:
    //Call to graph constructor creates HashTable and AdjacencyList
    Graph<Type>(){
        graph = new HashTable<Type>();
        arr = new AdjacencyList<Type>[MIN];
        // Set all values to NULL as default
        for(int i = 0; i < MIN; i++){
            arr[i].head = new Vertex<Type>();
            cout << i << " ";
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
    // Maybe take in 2 files: one for nodes and their data
    // another for their edges and weights
    void buildGraph(){
        ifstream file;
        string name, name2, line;
        double data;
        int i = 0;
        file.open("/home/randomguy/ClionProjects/Project4/AttackMap.txt");
        if (file.is_open()) {
            cout << "File Opened." << endl;
        }
        else {
            cerr << "File could not be opened." << endl;
        }

        while(file >> name >> data){
                graph->insertValue(name,data); //insertion into HashTable
                arr[i].head->setName(name); //insertion into AdjacencyList
                arr[i].head->setData(data); //insertion into AdjacencyList
//                cout << "ID: " << arr[i].head->getID() << " Name: " << arr[i].head->getName()
//                        << " Data: " << arr[i].head->getData() << endl;
                i++;
        }
        file.close();
        file.open("/home/randomguy/ClionProjects/Project4/AttackMapEdges.txt");
        if (file.is_open()) {
            cout << "File Opened." << endl;
        }
        else {
            cerr << "File could not be opened." << endl;
        }
        while(file >> name >> name2 >> data){
            cout << name << " " << name2 << " " << data << endl;
            //Add edge
            insert(name, name2, data);
        }
    }
    void insert(string u, string v, double w){
        if(w > 0 && w == numeric_limits<double>::infinity()){
            cerr << "Weight is invalid." << endl;
        }
        else if ( w == 0){
            Vertex<Data> * U;
            Vertex<Data> * V;
            U = graph->search(u);
            V = graph->search(v);
            Edge(U,V,w);
            numEdges++;
        }
    }
};
