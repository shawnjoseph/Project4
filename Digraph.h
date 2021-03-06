#include <iostream>
#include <limits>
#include <fstream>
#include <vector>
#include <set>
#include <climits>
#include "Vertex.h"
#include "Edge.h"
#include "HashTable.h"
#include "AdjacencyList.h"
#include "Stack.h"
#include "Queue.h"
#include "MinHeap.h"

#define MIN 20

using namespace std;


template<class Type>
class Digraph {
private:
    HashTable<Type> *graph;
    AdjacencyList *arr;
    int numEdges = 0;
    int numNodes = 0;
    bool *visited = new bool[numNodes]();

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
                if (ptr) {
                    while (ptr->next) {
                        if (ptr->getVertex()->getName() == v) {
                            degree++;
                        }
                        ptr = ptr->next;
                    }
                }
            }
        }
        if (degree == 0) {
            cout << "Could not find Vertex you specified" << endl;
            return 0;
        } else {
            return degree;
        }
    }

    int outdegree(string v) {
        int degree = 0;
        int i = 0;
        while ((arr[i].head->getVertex()->getName()) != v && (i <= numNodes)) {
            i++;
        }
        if (i > numNodes) {
            cout << "Node specified could not be found. Terminating." << endl;
            return 0;
        }
        AdjacencyListNode *ptr = arr[i].head;
        while (ptr->next) {
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
        if (i > numNodes)
            return NULL;
        AdjacencyListNode *node = arr[i].head;
        return node;
    }

    int findNodeIndex(string v) {
        int i = 0;
        while (arr[i].head->getVertex()->getName() != v && i <= numNodes) {
            i++;
        }
        if (i > numNodes)
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
//            cout << arr[i].head->getVertex()->getName() << endl;
            i++;
//            cout << "i is (after): " << i << endl;

        }

        Edge *edges = arr[i].head->getVertex()->getEdges();

        int j = 0;
        while ((edges[j].getEnd()->getName() != v) && j <= arr[i].head->getVertex()->getNumEdges()) {
//            cout << "Searching for string v" << endl;
            j++;
        }
        if (j > arr[i].head->getVertex()->getNumEdges()) {
//            cout << "String v could NOT be found" << endl;
            return 0;
        } else {
            cout << "Weight between the vertexes " << u << " and " << v << " is: " << edges[j].getWeight() << endl;
            return edges[j].getWeight();
        }
    }

    void DFS(string v) {
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

    int minDistance(double dist[], bool sptSet[]) {
        // Initialize min value
        double min = numeric_limits<double>::infinity();
        // Setting it to high number so it doesn't give me that stupid warning
        int min_index = -1;

        for (int v = 0; v < numNodes; v++)
            if (!sptSet[v] && dist[v] <= min) {
                min = dist[v], min_index = v;
            }
        if (min_index > -1) {
            return min_index;
        } else {
            cout << "min distance was not able to be calculated" << endl;
            return -1;
        }
    }


    bool isEdge(int src, int dest) {
        if (!arr[src].head) {
            cout << "Could not find string u in isEdge function" << endl;
            return false;
        }
        AdjacencyListNode *ptr = arr[src].head;
        while (ptr) {
            if (ptr->getVertex()->getName() == arr[dest].head->getVertex()->getName()) {
                return true;
            }
            ptr = ptr->next;
        }
        return false;
    }

    void shortPath(string u, string v) {
        // creating minHeap
        MinHeap *minHeap = new MinHeap(numNodes);

        // creating visited nodes array to loop over
        MinHeapNode **visitedNodes = new MinHeapNode *[numNodes]();
        int keepTrack = 0;

        // initialize by making source vertex distance 0
        // all other vertices dist are infinity
        minHeap->insert(findNode(u), findNodeIndex(u), 0);
//        cout << "done with insertion on top" << endl;
        int srcIndex = findNodeIndex(u);
        for (int i = 0; i < numNodes; i++) {
            if (i == srcIndex)
                continue;
            minHeap->insert(arr[i].head, i, numeric_limits<double>::infinity());
        }
        while (!minHeap->empty()) {
            // extract top node from min heap
            MinHeapNode *node = minHeap->delMin();
            // traverse adjacency list of vertex
            AdjacencyListNode *ptr = arr[node->getIndex()].head;
            if(!ptr) {
//                cout << "ptr is null " << endl;
            } else {
//                cout << "get node done" << endl;
//                cout << "ptr vertex name" << endl;
//                cout << minHeap->getNode(ptr->getVertex()->getName())->getNode()->getVertex()->getName() << endl;
                MinHeapNode *minHeapPtr = minHeap->getNode(ptr->getVertex()->getName());
                // for every vertex (ptr) in adjacency list:
                // u = node; v = ptr in this case
//                cout << "While loop before" << endl;
                while (ptr->next) {
                    if (minHeap->isHere(node)) {
//                        cout << "min heap node is here" << endl;
                        double tempWeight = adjacent(node->getNode()->getVertex()->getName(), ptr->getVertex()->getName());
//                        cout << "temp weight is:" << tempWeight << endl;
                        if (node->getWeight() > tempWeight) {
                            minHeapPtr->setWeight(tempWeight);
                        }
                        visitedNodes[keepTrack++] = minHeapPtr;
                    }
//                    cout << "bout to do ptr next" << endl;
                    ptr = ptr->next;
//                    cout << "ptr is now: " << ptr->getVertex()->getName() << endl;
                }

            }
        }
        // find whichever node we want
        cout << "keep track is " << keepTrack << endl;
        for (int i = 0; i < keepTrack; i++) {
            // printing all to debug
            cout << "printing to debug" << endl;
            cout << visitedNodes[i]->getNode()->getVertex()->getName() << endl;
        }

    }

    double distance(string u, string v) {
        return 0;
    }

    void reset() {
        for (int i = 0; i < numNodes; i++) {
            visited[i] = false;
        }
    }

    void clear() {
        while (numNodes > 0) {
            del(arr[numNodes - 1].head->getVertex()->getName());
        }
        cout << "List has been cleared" << endl;
    }

    int edgeCount() { return numEdges; }

    void del(string v) {
        // find node in adjacency list
        int index = findNodeIndex(v);
        if (index == -1) {
            cout << "Node with specified criteria was not found. Terminating" << endl;
        }
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
