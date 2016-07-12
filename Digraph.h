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

template<class Type>
class Digraph {
private:
    HashTable<Type> *digraph;
    static int numEdges = 0;
    AdjacencyList<Type> *arr;

public:
    //Call to digraph constructor creates HashTable and AdjacencyList
    Digraph<Type>() {
        digraph = new HashTable<Type>();
        arr = new AdjacencyList<Type>[MIN];
        // Set all values to NULL as default
        for (int i = 0; i < MIN; i++) {
            arr[i].head = new Vertex<Type>();
            cout << i << " ";
        }
    }

    ~Digraph<Type>() {
        digraph->~HashTable();
        delete[] arr;
    }

    bool empty() {
        if (digraph->numOfEntries == 0) {
            cout << "Graph is empty." << endl;
        }
        else {
            cout << "Graph is not empty." << endl;
        }
        return digraph->numOfEntries == 0;
    }

    void buildGraph() {
        ifstream file;
        string name, name2, line;
        double data;
        int i = 0;
        file.open("AttackMap.txt");
        if (file.is_open()) {
            cout << "File Opened." << endl;
        } else {
            cerr << "File could not be opened." << endl;
        }

        while (file >> name >> data) {
            digraph->insertValue(name, data); //insertion into HashTable
            arr[i].head->setName(name); //insertion into AdjacencyList
            arr[i].head->setData(data); //insertion into AdjacencyList
                cout << "ID: " << arr[i].head->getID() << " Name: " << arr[i].head->getName()
                        << " Data: " << arr[i].head->getData() << endl;
            i++;
        }
        file.close();
        file.open("AttackMapEdges.txt");
        if (file.is_open()) {
            cout << "File Opened." << endl;
        }
        else {
            cerr << "File could not be opened." << endl;
        }
        while (file >> name >> name2 >> data) {
            cout << name << " " << name2 << " " << data << endl;
            //Add edge
            insert(name, name2, data);
        }
    }

    void insert(string u, string v, double w) {
        if(w > 0 && w == numeric_limits<double>::infinity()) {
            cerr << "Weight is invalid." << endl;
        } else if(w == 0) {
            Vertex<Data> *U;
            Vertex<Data> *V;
            U = digraph->search(u);
            V = digraph->search(v);
            Edge(U, V, w);
            numEdges++;
        }
    }

    void clear() {

    }

    void reset() {

    }

    void del(string v) {

    }

    int indegree(string v) {
        return 0;
    }

    int outdegree(string v) {
        return 0;
    }

    int edgeCount() {
        return 0;
    }

    double adjacent(string u, string v) {
        return 0;
    }

    void depthFirstSearch(string v) {

    }

    void breadthFirstSearch(string v) {

    }

    void shortPath(string u, string v) {

    }

    double distance(string u, string v) {
        return 0;
    }
};
