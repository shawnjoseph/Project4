#include <iostream>
#include <limits>
#include <fstream>
#include "Vertex.h"
#include "Edge.h"
#include "HashTable.h"
#include "AdjacencyList.h"
#include "Queue.h"
#include "Stack.h"
#include "MinHeap.h"

#define MIN 20

using namespace std;

template<class Type>
class Graph {
private:
    HashTable<Type> * graph;
    AdjacencyList *arr;     //arr of adjacency list heads
    int numEdges = 0;
    int numNodes = 0;
    bool *visited = new bool[numNodes]();

public:
    //Call to graph constructor creates HashTable and AdjacencyList
    Graph<Type>() {
        graph = new HashTable<Type>();      //HashTable stores Vertices and their values
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
//        file.open("/home/randomguy/ClionProjects/Project4/AttackMap.txt");
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
//        file.open("/home/randomguy/ClionProjects/Project4/AttackMapEdges.txt");
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
            bool inList = false;

            while (arr[i].head->getVertex()->getName() != u) { //retrieves location of u in AdjacencyList
                i++;
            }
            AdjacencyListNode *ptr = arr[i].head; //pointer to u

            while (arr[j].head->getVertex()->getName() != v) { //retrieves location of v in AdjacencyList
                j++;
            }
            AdjacencyListNode *ptr2 = arr[j].head; //pointer to v

            if (arr[i].head != NULL && arr[j].head != NULL) {
                //Create first node in adjacency list of vertex u
                if (ptr->next == NULL) {
                    arr[i].head->next = new AdjacencyListNode(arr[j].head->getVertex(), nullptr);
                    arr[i].head->getVertex()->addEdge(arr[i].head->getVertex(), arr[j].head->getVertex(),
                                                      w); //undirected edge
                    numEdges++;

                    if (arr[j].head->next == NULL) {
                        arr[j].head->next = new AdjacencyListNode(arr[i].head->getVertex(),
                                                                  nullptr);//creates first node
                        arr[j].head->getVertex()->addEdge(arr[j].head->getVertex(), arr[i].head->getVertex(),
                                                          w);//undirected edge
                        numEdges++;
                    }
                        //if pointer v != NULL
                    else {
                        //runs if vertex v already has nodes in AdjacencyList
                        while (ptr2->next != NULL) {
                            ptr2 = ptr2->next;
                        }
                        ptr2->next = new AdjacencyListNode(arr[i].head->getVertex(), nullptr); //creates next nodes
                        arr[j].head->getVertex()->addEdge(arr[j].head->getVertex(), arr[i].head->getVertex(),
                                                          w); //undirected edge
                        numEdges++;
                    }
                }
                else {
                    while (ptr->next != NULL) {
                        if (ptr->next->getVertex()->getName() == arr[j].head->getVertex()->getName()) {
                            inList = true;
                        }
                        ptr = ptr->next;
                    }

                    if (!inList) {
                        ptr->next = new AdjacencyListNode(arr[j].head->getVertex(), nullptr); //creates all other nodes
                    }
                    arr[i].head->getVertex()->addEdge(arr[i].head->getVertex(), arr[j].head->getVertex(), w);
                    numEdges++;

                    if (arr[j].head->next == NULL) {
                        arr[j].head->next = new AdjacencyListNode(arr[i].head->getVertex(),
                                                                  nullptr);//creates first node
                        arr[j].head->getVertex()->addEdge(arr[j].head->getVertex(), arr[i].head->getVertex(),
                                                          w);//undirected edge
                        numEdges++;
                    }
                    else {
                        inList = false;
                        while (ptr2->next != NULL) {
                            if (ptr2->next->getVertex()->getName() == arr[i].head->getVertex()->getName()) {
                                inList = true;
                            }
                            ptr2 = ptr2->next;
                        }
                        if (!inList) {
                            ptr2->next = new AdjacencyListNode(arr[i].head->getVertex(), nullptr); //creates next nodes
                        }
                        arr[j].head->getVertex()->addEdge(arr[j].head->getVertex(), arr[i].head->getVertex(),
                                                          w); //undirected edge
                        numEdges++;
                    }
                    }
            } else {
                cerr << "One or more vertices do not exist." << endl;
            }
        }
    }

    //Checks if two nodes are adjacent and returns the weight of their shared edge if true
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
            return 0;       //returns 0 if both strings are same vertex
        }
        else if (arr[i].head == NULL || arr[j].head == NULL) {
            cerr << "One or more vertices may not exist." << endl;
        }
        else {
            Edge *e = arr[i].head->getVertex()->getEdges();
            int pos = 0;
            while (e[pos].getEnd() != arr[j].head->getVertex()) {       //finds corresponding vertex
                pos++;
            }
            return e[pos].getWeight();
        }
    }

    //return number of edges
    int edgeCount() { return numEdges; }

    //Checks if graph is connected
    bool isConnected() {
//        DFS(arr[0].head->getVertex()->getName());

//        for (int i = 0; i < numNodes; i++) {
//            if (arr[i].head->getNext() == NULL) {
//                return false;
//            }
//        }
        return true;
    }

    //Finds the number of edges attached to vertex v
    int degree(string v) {
        int degree = 0;
        int i = 0;
        while (arr[i].head->getVertex()->getName() != v) { //retrieves location of v in AdjacencyList
            i++;
        }
        AdjacencyListNode *ptr = arr[i].head->getNext();
        while (ptr != NULL) {       //traverses adjacency list of node, incrementing degree
            degree++;
            ptr = ptr->next;
        }
        return degree;
    }

    //Clears graph
    void clear() {
        graph->~HashTable();
        while (numNodes > 0) {
            del(arr[numNodes - 1].head->getVertex()->getName());
        }
        cout << "List has been cleared" << endl;

        graph = new HashTable<Type>();
        arr = new AdjacencyList[MIN];
        // Set all values to NULL as default
        for (int i = 0; i < MIN; i++) {
            arr[i].head = new AdjacencyListNode(NULL, nullptr);
        }
    }

    //resets all vertex visited to false
    void reset() {
        for (int i = 0; i < numNodes; i++) {
            visited[i] = false;
        }
    }

    //deletes a vertex and adjusts graph and adjacencylist
    void del(string v) {
        // find node in adjacency list
        int i = 0;
        while (arr[i].head->getVertex()->getName() != v && i <= numNodes) {
            i++;
        }
        int index = i;

        for (int i = index; i < numNodes; i++) {
            arr[i] = arr[i + 1];
        }
        // decrement numNodes
        numNodes--;
        // find every instance of it in other nodes lists and delete it
        AdjacencyListNode *prev = NULL;
        AdjacencyListNode *cur = NULL;
        for (int i = 0; i < numNodes; i++) {
            prev = arr[i].head;
            cur = prev->next;
            while (cur) {
                if (cur->getVertex()->getName() == v) {
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

    //prints out graph using adjacency list
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

    //prints out graph using Breadth-First Search
    void BFS(string v) {
        reset();
        AdjacencyListNode *node = NULL;

        int start = 0;
        for (int i = 0; i < numNodes; i++) {
            if (arr[i].head->getVertex()->getName() == v) {
                node = arr[i].head;
                break;
            }
        }
        if (!node) {
            cout << "Vertex with name specified not found. Terminating. " << endl;
            return;
        }

        Queue<AdjacencyListNode *> *queue = new Queue<AdjacencyListNode *>(numNodes);
        queue->enqueue(node);

        cout << "BFS: ";
        visited[node->getVertex()->getID() - 1] = true;

        while (!queue->empty()) {
            AdjacencyListNode *front = queue->front();
            cout << front->getVertex()->getName() << " -> ";
            queue->dequeue();
            visited[front->getVertex()->getID() - 1] = true;

            AdjacencyListNode *ptr = arr[front->getVertex()->getID() - 1].head;
            while (ptr) {
                if (!visited[ptr->getVertex()->getID() - 1]) {
                    visited[ptr->getVertex()->getID() - 1] = true;
                    queue->enqueue(ptr);
                }
                ptr = ptr->next;
            }
        }
        cout << "end" << endl;
        reset();
    }

    //prints out graph using Depth-First Search
    void DFS(string v) {
        reset();
        AdjacencyListNode *node = NULL;
        int start = 0;
        for (int i = 0; i < numNodes; i++) {
            if (arr[i].head->getVertex()->getName() == v) {
                node = arr[i].head;
                break;
            }
        }
        if (!node) {
            cout << "Vertex with name specified not found. Terminating. " << endl;
            return;
        }

        Stack<AdjacencyListNode *> *stack = new Stack<AdjacencyListNode *>(numNodes);
        stack->push(node);
        cout << "DFS: ";
        visited[node->getVertex()->getID() - 1] = true;
        while (!stack->isEmpty()) {
            AdjacencyListNode *top = stack->top();
            cout << top->getVertex()->getName() << " -> ";
            stack->pop();
            visited[top->getVertex()->getID() - 1] = true;
            AdjacencyListNode *ptr = arr[top->getVertex()->getID() - 1].head;
            while (ptr) {
                if (!visited[ptr->getVertex()->getID() - 1]) {
                    visited[ptr->getVertex()->getID() - 1] = true;
                    stack->push(ptr);
                }
                ptr = ptr->next;
            }
        }
        cout << "end" << endl;
    }

    void MST(string v) {
        int i = 0;
        while (arr[i].head->getVertex()->getName() != v) {
            i++;
        }
        MinHeap *heap = new MinHeap[numNodes];

        for (int j = 1; j < numNodes; i++) {
            heap->array[j] = new MinHeapNode(nullptr, 0);
            heap->array[j]->setWeight(numeric_limits<double>::infinity());
        }
        heap->array[0] = new MinHeapNode(arr[i].head, 0);
        heap->insert(arr[i].head, 0);

        while (!heap->empty()) {
            MinHeapNode *minNode = heap->delMin();
            int u = minNode->getIndex();

            AdjacencyListNode *ptr = arr[u].head;
            while (ptr != NULL) {
                int destination;
            }
        }
    }
};
