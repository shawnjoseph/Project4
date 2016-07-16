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
        numEdges = 0;
    }

    //Call to graph constructor deletes HashTable and AdjacencyList
    ~Graph<Type>() {
        graph->~HashTable();
        delete [] arr;
        numEdges = 0;
    }

    //Checks if graph is empty
    bool empty(){
        if(graph->numOfEntries == 0){
            cout << "Graph is empty." << endl;
        }
        else{
            cout << "Graph is not empty." << endl;
        }
        return graph->numOfEntries == 0;
    }

    //Reads in two files: One to create Vertices and HashTable, another to create Adjacency List and Edges
    void buildGraph(){
        ifstream file;
        string name, name2, line;
        double data;
        int i = 0;
        // Uncomment this when Shawn is working on it.
        file.open("/home/randomguy/ClionProjects/Project4/AttackMap.txt");
//        file.open("AttackMap.txt");
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
        file.open("/home/randomguy/ClionProjects/Project4/AttackMapEdges.txt");
//        file.open("AttackMapEdges.txt");

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
            AdjacencyListNode *ptr = arr[i].head;
            while (arr[j].head->getVertex()->getName() != v) { //retrieves location of v in AdjacencyList
                j++;
            }
            if (arr[i].head != NULL && arr[j].head != NULL) {
                if (ptr->next == NULL) {
                    arr[i].head->next = new AdjacencyListNode(arr[j].head->getVertex(), nullptr); //creates first nodes
                    arr[i].head->getVertex()->addEdge(arr[i].head->getVertex(), arr[j].head->getVertex(),
                                                      w); //undirected edge
                    arr[j].head->getVertex()->addEdge(arr[j].head->getVertex(), arr[i].head->getVertex(),
                                                      w); //undirected edge
                    numEdges++;
                }
                else {
                    while (ptr->next != NULL) {
                        ptr = ptr->next;
                    }
                    ptr->next = new AdjacencyListNode(arr[j].head->getVertex(), nullptr); //creates all other nodes
                    arr[i].head->getVertex()->addEdge(arr[i].head->getVertex(), arr[j].head->getVertex(), w);
                    arr[j].head->getVertex()->addEdge(arr[j].head->getVertex(), arr[i].head->getVertex(), w);
                    numEdges++;
                }
            } else {
                cerr << "A vertex does not exist." << endl;
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
        if (arr[i].head->getVertex()->getName() == arr[j].head->getVertex()->getName()) {
            return 0;
        }
        else if (arr[i].head == NULL || arr[j].head == NULL) {
            cerr << "One or more vertices may not exist." << endl;
        }
        else {
            Edge *e = arr[i].head->getVertex()->getEdges();
            int pos = 0;
            while (e[pos].getEnd() != arr[j].head->getVertex()) {
                pos++;
            }
            return e[pos].getWeight();
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

    void display() {
        for (int i = 0; i < numNodes; i++) {
            AdjacencyListNode *ptr = arr[i].head;
            if (ptr->getVertex() == NULL) {
                cerr << "Error: Graph is Empty." << endl;
                break;
            }
            cout << "Adjacency List for vertex " << i << endl;
            while (ptr) {
                cout << ptr->getVertex()->getName() << " -> ";
                ptr = ptr->getNext();
            }
            cout << " end" << endl;
        }
    }
};
