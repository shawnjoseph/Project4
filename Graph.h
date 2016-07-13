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
    AdjacencyList<Type> * arr;

public:
    //Call to graph constructor creates HashTable and AdjacencyList
    Graph<Type>(){
        graph = new HashTable<Type>();
        arr = new AdjacencyList<Type>[MIN];
        // Set all values to NULL as default
        for(int i = 0; i < MIN; i++){
            arr[i].head = new Vertex<Type>();
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
//            cout << name << " " << name2 << " " << data << endl;
            //Add edge
            insert(name, name2, data);
        }
    }
    void insert(string u, string v, double w){
        static int numEdges = 0;
        if(w <= 0 || w == numeric_limits<double>::infinity()){
            cerr << "Weight is invalid." << endl;
        }
        else if ( w > 0){
            int i = 0;
            int j = 0;
            while(arr[i].head->getName() != u){
                i++;
            }
            while(arr[j].head->getName() != v){
                j++;
            }
            while (arr[i].head->next != NULL) {
                arr[i].head->next = arr[i].head->next->next;
            }
            arr[i].head->next = arr[j].head;
            cout << arr[i].head->getName() << " " << arr[i].head->next->getName() << endl;
//            Edge(arr[i].head, arr[j].head, w);
//            Vertex<Data> * U;
//            Vertex<Data> * V;
//            U = graph->search(u);
//            V = graph->search(v);
//            Edge(U,V,w);
            numEdges++;
        }
    }
};
