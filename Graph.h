#pragma once
#include <iostream>
#include <limits>
#include <fstream>
#include "Vertex.h"
#include "Edge.h"
#include "HashTable.h"
#include "AdjacencyList.h"
#include "AdjacencyListNode.h"
#define MIN 20

using namespace std;


template<class Type>
class Graph {
private:
    HashTable<Type> * graph;
    AdjacencyList *arr;
    int numEdges;
    int numNodes;

public:
    //Call to graph constructor creates HashTable and AdjacencyList
    Graph<Type>() {
        graph = new HashTable<Type>();
        arr = new AdjacencyList[MIN]();
        // Set all values to NULL as default
        for(int i = 0; i < MIN; i++){
            arr[i].head = new AdjacencyListNode(NULL, NULL);
        }
    }

    //Call to graph constructor deletes HashTable and AdjacencyList
    ~Graph<Type>() {
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
        // Uncomment this when Shawn is working on it.
        //file.open("/home/randomguy/ClionProjects/Project4/AttackMap.txt");
        file.open("AttackMap.txt");

        if (file.is_open()) {
            cout << "File Opened." << endl;
        }
        else {
            cerr << "File could not be opened." << endl;
        }

        while(file >> name >> data){
            Vertex<Data> *v = new Vertex<Data>(name, data);
            graph->insertValue(name,data); //insertion into HashTable
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
        while(file >> name >> name2 >> data){
            insert(name, name2, data);            //Add edge and creates AdjacencyList
        }
        file.close();
    }

    //Add edge and creates AdjacencyList
    void insert(string u, string v, double w){
        if(w <= 0 || w == numeric_limits<double>::infinity()){
            cerr << "Weight is invalid." << endl;
        }
        else if ( w > 0){
            int i = 0;
            int j = 0;
            while (arr[i].head->getVertex()->getName() != u) { //retrieves location of u in AdjacencyList
                i++;
            }
            while (arr[j].head->getVertex()->getName() != v) { //retrieves location of v in AdjacencyList
                j++;
            }
            if(arr[i].head != NULL) {
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

    double adjacent(string u, string v) {
        int i = 0;
        int j = 0;
        while (arr[i].head->getVertex()->getName() != u) { //retrieves location of u in AdjacencyList
            i++;
        }
        while (arr[j].head->getVertex()->getName() != v) { //retrieves location of v in AdjacencyList
            j++;
        }

    }

    int edgeCount() { return numEdges; }

    bool isConnected() {
        for (int i = 0; i < numNodes; i++) {
            if (arr[i].head->getNext() == NULL) {
                return false;
            }
        }
        return true;
    }

    int degree(string v) {
        int degree = 0;
        int i = 0;
        while (arr[i].head->getVertex()->getName() != v) { //retrieves location of u in AdjacencyList
            i++;
        }
        AdjacencyListNode *ptr = arr[i].head->getNext();
        while (ptr != NULL) {
            degree++;
            ptr = ptr->next;
        }
        return degree;
    }

    void clear() {
        graph->~HashTable();
        delete[] arr;

        graph = new HashTable<Type>();
        arr = new AdjacencyList[MIN];
        // Set all values to NULL as default
        for (int i = 0; i < MIN; i++) {
            arr[i].head = new AdjacencyListNode(NULL, nullptr);
        }
    }

    void reset() { }

    void del(string v) {
//        int i = 0;
//        while (arr[i].head->getVertex()->getName() != v) { //retrieves location of u in AdjacencyList
//            i++;
//        }
//        arr[i].head->~AdjacencyListNode();
        //fix adjacencylist
    }
};
