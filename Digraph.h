#pragma once

#include <iostream>
#include <limits>
#include <fstream>
#include "Vertex.h"
#include "Edge.h"
#include "HashTable.h"
#include "AdjacencyList.h"

#define MIN 20

using namespace std;


template<class Type>
class Digraph {
private:
    HashTable<Type> *graph;
    AdjacencyList *arr;
    int numEdges = 0;
    int numNodes = 0;

public:
    //Call to graph constructor creates HashTable and AdjacencyList
    Digraph<Type>() {
        graph = new HashTable<Type>();
        arr = new AdjacencyList[MIN];
        // Set all values to NULL as default
        for (int i = 0; i < MIN; i++) {
            arr[i].head = new AdjacencyListNode(nullptr, nullptr);
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
        // Uncomment this when Shawn is working on it.
        //file.open("/home/randomguy/ClionProjects/Project4/AttackMap.txt");
        file.open("AttackMap.txt");

        if (file.is_open()) {
            cout << "File Opened." << endl;
        }
        else {
            cerr << "File could not be opened." << endl;
        }

        while (file >> name >> data) {
            Vertex<Data> *v = new Vertex<Data>(name, data);
            graph->insertValue(name, data); //insertion into HashTable
            arr[i].head = new AdjacencyListNode(v, NULL); //insertion into AdjacencyList
            i++;
            numNodes++;
        }
        file.close();


        // Uncomment this when Shawn is working on it.
        //file.open("/home/randomguy/ClionProjects/Project4/AttackMapEdges.txt");
        file.open("AttackMapEdges.txt");

        if (file.is_open()) {
            cout << "File Opened." << endl;
        }
        else {
            cerr << "File could not be opened." << endl;
        }
        while (file >> name >> name2 >> data) {
//            cout << "Name: " << name << endl;
//            cout << "Name 2: " << name2 << endl;
//            cout << "Data: " << data << endl;
            insert(name, name2, data);            //Add edge and creates AdjacencyList
        }
        file.close();
    }

    void insert(string u, string v, double w) {
        if (w <= 0 || w == numeric_limits<double>::infinity()) {
            cerr << "Weight is invalid." << endl;
        }
        else if (w > 0) {
            int i = 0;
            int j = 0;
            while (arr[i].head->getVertex()->getName() != u) { //retrieves location of u in AdjacencyList
                i++;
            }
            while (arr[j].head->getVertex()->getName() != v) { //retrieves location of v in AdjacencyList
                j++;
            }
            if (arr[i].head != NULL) {
                AdjacencyListNode *ptr = arr[i].head->next;
                if (ptr == NULL) {
                    arr[i].head->next = new AdjacencyListNode(arr[j].head->getVertex(), nullptr); //creates first nodes
                }
                else {
                    while (ptr != NULL) {
                        ptr = ptr->next;
                    }
                    ptr = new AdjacencyListNode(arr[j].head->getVertex(), nullptr); //creates all other nodes
                }
                numEdges++;
            } else {
                cout << "arr[i].head is NULL, error" << endl;
            }
        }
    }


    int indegree(string name) {
        int degree = 0;
        // Change MIN to actual amount in the list later
        for (int i = 0; i < MIN; i++) {
            if (arr[i].head != NULL) {
                if (arr[i].head->getVertex()->getName() == name) {
                    AdjacencyListNode *ptr = arr[i].head;

                    // Not sure if while loop should terminate @ ptr = null or ptr->next = null
                    // need to wait on insertion function correct implementation to find out
                    while (ptr != NULL) {
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

//    double adjacent(string u, string v) {
//        for (int i = 0; i < numNodes; i++) {
//            if (arr[i].head != NULL) {
//                if (arr[i].head->getVertex()->getName() == u) {
//                    Vertex<Data> *vertex = arr[i].head->getVertex();
//                    if (vertex->getEdges() != NULL) {
//                        for (int j = 0; j < vertex->getNumEdges(); j++) {
//                            if (vertex->getEdges()[i]->getEnd()->getName() == v) {
//                                return vertex->getEdges()[i]->getWeight();
//                            }
//                        }
//                    }
//                }
//            }
//        }
//        cout << "Edge could not be found for the two edges specified" << endl;
//        return 0;
//    }

    double adjacent(string u, string v) {
        int i = 0;
        while (arr[i].head->getVertex()->getName() != u) {
            if (!arr[i].head) {
                cout << "String u could NOT be found" << endl;
                return 0;
            }
            cout << "Searching for string u" << endl;
            cout << arr[i].head->getVertex()->getName() << endl;
            i++;
        }

        cout << "I is: " << i << endl;

        cout << "Found string u" << endl;
        Edge **edges = arr[i].head->getVertex()->getEdges();

        int j = 0;
        cout << "edges part: " << endl;
        cout << edges[j]->getEnd() << endl;
        while (edges[j]->getEnd()->getName() != v) {
            if (edges[j] == NULL) {
                cout << "String v could NOT be found" << endl;
                return 0;
            }
            cout << "Searching for string v" << endl;
            j++;
        }
        return edges[j]->getWeight();

        cout << "Edge with these two criteria could not be found " << endl;
    }

    void display() {
        for (int i = 0; i < numNodes; i++) {
            cout << "Adjacency List for vertex " << i << endl;
            AdjacencyListNode *ptr = arr[i].head;
            while (ptr) {
                cout << ptr->getVertex()->getName() << " -> ";
                ptr = ptr->next;
            }
            cout << " end" << endl;
        }
    }
};
