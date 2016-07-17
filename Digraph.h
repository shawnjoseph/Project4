#pragma once

#include <iostream>
#include <limits>
#include <fstream>
#include <vector>
#include "Vertex.h"
#include "Edge.h"
#include "HashTable.h"
#include "AdjacencyList.h"
#include "Stack.h"
#include "Queue.h"

#define MIN 20

using namespace std;


template<class Type>
class Digraph {
private:
    HashTable<Type> *graph;
    AdjacencyList *arr;
    int numEdges = 0;
    int numNodes = 0;
    bool* visited = new bool[numNodes]();

public:
    //Call to graph constructor creates HashTable and AdjacencyList
    Digraph<Type>() {
        graph = new HashTable<Type>();
        arr = new AdjacencyList[MIN];
        // Set all values to NULL as default
        for (int i = 0; i < MIN; i++) {
            arr[i].head = new AdjacencyListNode(nullptr, nullptr);
        }
        reset();
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
//        file.open("/home/randomguy/ClionProjects/Project4/AttackMap.txt");
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
//        file.open("/home/randomguy/ClionProjects/Project4/AttackMapEdges.txt");
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
            AdjacencyListNode *ptr = arr[i].head;
            while (arr[j].head->getVertex()->getName() != v) { //retrieves location of v in AdjacencyList
                j++;
            }
            if (arr[i].head != NULL) {
                if (ptr->next == NULL) {
                    arr[i].head->next = new AdjacencyListNode(arr[j].head->getVertex(), nullptr); //creates first nodes
                    arr[i].head->getVertex()->addEdge(arr[i].head->getVertex(), arr[j].head->getVertex(),
                                                      w); //undirected edge
                }
                else {
                    while (ptr->next != NULL) {
                        ptr = ptr->next;
                    }
                    ptr->next = new AdjacencyListNode(arr[j].head->getVertex(), nullptr); //creates all other nodes
                    arr[i].head->getVertex()->addEdge(arr[i].head->getVertex(), arr[j].head->getVertex(), w);
                    numEdges++;
                }
            } else {
                cout << "arr[i].head is NULL, error" << endl;
            }
        }
    }

    int indegree(string v) {
        int degree = 0;
        for (int i = 0; i < numNodes; i++) {
            if (arr[i].head != NULL) {
                // starting at next because we don't want to count the actual
                // node as an indegree itself
                AdjacencyListNode *ptr = arr[i].head->getNext();
                if(ptr) {
                    while(ptr->next) {
                        if(ptr->getVertex()->getName() == v) {
                            degree++;
                        }
                        ptr = ptr->next;
                    }
                }
            }
        }
        if(degree == 0) {
            cout << "Could not find Vertex you specified" << endl;
            return 0;
        } else {
            cout << "Indegree of " << v << " is: " << degree << endl;
            return degree;
        }
    }

    int outdegree(string v) {
        int degree = 0;
        int i=0;
        while((arr[i].head->getVertex()->getName()) != v && (i <= numNodes)) {
            i++;
        }
        if(i > numNodes) {
            cout << "Node specified could not be found. Terminating." << endl;
            return 0;
        }
        AdjacencyListNode *ptr = arr[i].head;
        while(ptr->next) {
            degree++;
            ptr = ptr->next;
        }
        cout << "Outdegree of " << arr[i].head->getVertex()->getName() << " is: " << degree << endl;

        return 0;
    }

    AdjacencyListNode *findNode(string v) {
        int i = 0;
        while (arr[i].head->getVertex()->getName() != v && i <= numNodes) {
            i++;
        }
        if(i > numNodes)
            return NULL;
        AdjacencyListNode *node = arr[i].head;
        return node;
    }

    int findNodeIndex(string v) {
        int i = 0;
        while (arr[i].head->getVertex()->getName() != v && i <= numNodes) {
            i++;
        }
        if(i > numNodes)
            return -1;
        else
            return i;
    }

    double adjacent(string u, string v) {
        int i = 0;
        while (arr[i].head->getVertex()->getName() != u) {
            if (!arr[i].head) {
                cout << "String u could NOT be found" << endl;
                return 0;
            }
            cout << arr[i].head->getVertex()->getName() << endl;
            i++;
        }

        Edge *edges = arr[i].head->getVertex()->getEdges();

        int j = 0;
        while ((edges[j].getEnd()->getName() != v) && j < arr[i].head->getVertex()->getNumEdges()) {
            cout << "Searching for string v" << endl;
            j++;
        }
        if (j > arr[i].head->getVertex()->getNumEdges()) {
            cout << "String v could NOT be found" << endl;
            return 0;
        } else {
            cout << "Weight between the vertexes " << u << " and " << v << " is: " << edges[j].getWeight() << endl;
            return edges[j].getWeight();
        }
    }

    void DFS(string v) {
        AdjacencyListNode *node = NULL;
        int start = 0;
        for(int i=0; i < numNodes; i++) {
            if(arr[i].head->getVertex()->getName() == v) {
                node = arr[i].head;
                break;
            }
        }
        if(!node) {
            cout << "Vertex with name specified not found. Terminating. " << endl;
            return;
        }

        Stack< AdjacencyListNode *> *stack = new Stack<AdjacencyListNode*>(numNodes);
        stack->push(node);
        cout << "DFS: ";
        visited[node->getVertex()->getID() - 1] = true;
        while(!stack->isEmpty()) {
            AdjacencyListNode *top = stack->top();
            cout << top->getVertex()->getName() << " -> ";
            stack->pop();
            visited[top->getVertex()->getID() - 1] = true;
            AdjacencyListNode *ptr = arr[top->getVertex()->getID() - 1].head;
            while(ptr) {
                if (!visited[ptr->getVertex()->getID() - 1]) {
                    visited[ptr->getVertex()->getID() - 1] = true;
                    stack->push(ptr);
                }
                ptr = ptr->next;
            }
        }
        cout << "end" << endl;
    }

    void reset() {
        for(int i=0; i < numNodes; i++) {
            visited[i] = false;
        }
    }

    void clear() {
        for(int i=0; i < numNodes; i++) {
            AdjacencyListNode *ptr = arr[i].head;
            arr[i] = NULL;
            while(ptr->next) {
                AdjacencyListNode *temp = ptr;
                ptr = ptr->next;
                delete temp;
            }
        }
    }

    int edgeCount() { return numEdges; }

    void del(string v) {
        // find node in adjacency list
        int index = findNodeIndex(v);
        if(index == -1) {
            cout << "Node with specified criteria was not found. Terminating" << endl;
        }
        for(int i = index; i < numNodes; i++) {
            arr[i] = arr[i+1];
        }
        // decrement numNodes
        numNodes--;
        // find every instance of it in other nodes lists and delete it
        AdjacencyListNode *prev = NULL;
        AdjacencyListNode *cur = NULL;
        for(int i = 0; i < numNodes; i++) {
            prev = arr[i].head;
            cur = prev->next;
            while(cur) {
                if(cur->getVertex()->getName() == v) {
                    // Node found in other nodes list
                    prev->next = cur->next;
                    AdjacencyListNode temp = *cur;
                }
                prev = cur;
                cur = cur->next;
            }
        }

        cout << "LIST AFTER DELETION" << endl;
        display();
    }

    void display() {
        for (int i = 0; i < numNodes; i++) {
//            cout << "Adjacency List for vertex " << i << endl;
            AdjacencyListNode *ptr = arr[i].head;
            while (ptr) {
                cout << ptr->getVertex()->getName() << " -> ";
                ptr = ptr->next;
            }
            cout << " end" << endl;
        }
    }
};
