#pragma once

#include <iostream>
#include <limits>
#include <fstream>
#include "Vertex.h"
#include "Edge.h"
#include "HashTable.h"
#include "AdjacencyList.h"
#include "AdjacencyListNode.h"

using namespace std;

const int MIN = 20;

template<class Type>
class Digraph {
private:
    HashTable<Type> *graph;
    AdjacencyList *arr;
    int numEdges = 0;

public:
    //Call to graph constructor creates HashTable and AdjacencyList
    Digraph<Type>() {
        graph = new HashTable<Type>();
        arr = new AdjacencyList[MIN];
        // Set all values to NULL as default
        for (int i = 0; i < MIN; i++) {
            arr[i].head = new AdjacencyListNode(" ", nullptr);
        }
    }


    ~Digraph<Type>() {
        graph->~HashTable();
        delete[] arr;
    }


    bool empty() {
        if (graph->numOfEntries == 0) {
            cout << "Graph is empty." << endl;
        } else {
            cout << "Graph is not empty." << endl;
        }
        return graph->numOfEntries == 0;
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
            graph->insertValue(name, data); //insertion into HashTable
            arr[i].head->setName(name); //insertion into AdjacencyList
            arr[i].head->setData(data); //insertion into AdjacencyList
            i++;
        }

        file.close();
        file.open("AttackMapEdges.txt");

        if (file.is_open()) {
            cout << "File Opened." << endl;
        } else {
            cerr << "File could not be opened." << endl;
        }

        while (file >> name >> name2 >> data) {
            insert(name, name2, data);            //Add edge and creates AdjacencyList
        }
        file.close();
    }

    //Add edge and creates AdjacencyList
    void insert(string u, string v, double w) {
        Vertex<Data> *vertex1;
        Vertex<Data> *vertex2;
        if (w <= 0 || w == numeric_limits<double>::infinity()) {
            cerr << "Weight is invalid." << endl;
        } else if (w > 0) {
            int i = 0;
            int j = 0;
            while (arr[i].head->getName() != u) {
                //retrieves location of u in AdjacencyList
                i++;
            }
            while (arr[j].head->getName() != v) {
                //retrieves location of v in AdjacencyList
                j++;
            }
            AdjacencyListNode *ptr = arr[i].head->next;
            if (ptr == NULL) {
                arr[i].head->next = new AdjacencyListNode(arr[j].head->getName(), nullptr); //creates first nodes
            } else {
                while (ptr != NULL) {
                    ptr = ptr->next;
                }
                ptr = new AdjacencyListNode(arr[j].head->getName(), nullptr); //creates all other nodes
            }
//            vertex1 = new Vertex(arr[i].head->getName(), arr[i].head->getData());
//            vertex2 = new Vertex(arr[j].head->getName(), arr[j].head->getData());
//            Edge(vertex1, vertex2, w);
            numEdges++;
        }
    }

    int indegree(string name) {
        int degree = 0;
        // Change MIN to actual amount in the list later
        for(int i=0; i < MIN; i++) {
            if(arr[i] != NULL) {
                if(arr[i].head->getName() == name) {
                    AdjacencyListNode *ptr = arr[i].head;
                    while(ptr != NULL) {
                        degree++;
                        ptr = ptr->next;
                    }
                    return degree;
                }
            }
        }
        cout << "Could not find Vertex you specified" << endl;
        return 0;
    }

    double adjacent(string u, string v) {
        for(int i=0; i < MIN; i++) {
            if(arr[i] != NULL) {
                if(arr[i].head->getName() == u) {
                    if(arr[i].head->getVertex()->getEdges() != NULL) {
                        for(int j=0; j < arr[i].head->getVertex()->getNumEdges(); j++) {
                            
                        }
                    }
                }
            }
        }
    }
};
