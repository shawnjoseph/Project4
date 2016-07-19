#pragma once
#include <iostream>
#include <cmath>
#include <fstream>
#include "MinHeapNode.h"

#define PARENT(i)  (i/2)
#define LEFT(i) (2*i)

using namespace std;
const int INITIAL_CAP = 9999;

class MinHeap {
private:
//    MinHeapNode *node;
    int numElements;
    int capacity;

public:
    MinHeapNode **array;
    MinHeap() {
        array = new MinHeapNode *[INITIAL_CAP];
        numElements = 0;
        capacity = INITIAL_CAP;
        for (int i = 0; i < capacity; i++) {
            array[i] = new MinHeapNode(NULL, 0);
        }
    }

    MinHeap(int size) {
        array = new MinHeapNode *[size];
        numElements = 0;
        capacity = size;
//        for (int i = 0; i < capacity; i++) {
//            array[i] = new MinHeapNode(NULL, 0);
//        }
    }

    ~MinHeap() {
        delete[] array;
    }

    MinHeapNode *getMin() { return array[1]; }

    int getSize() { return numElements; }

    int getHeight() {
        double height = (log(numElements) / log(2));
        return (int) height;
    }

    bool empty() { return numElements == 0; }

    int leaves() {
        int count = 0;
        for (int i = 1; i <= numElements; i++) {
            if (array[LEFT(i)] == NULL) {
                count++;
            }
        }
        return count;
    }

    void clear() {
        for (int i = 1; i <= numElements; i++) {
            array[i] = new MinHeapNode(NULL, 0);
        }
        numElements = 0;
    }

//    void doubleSize() {
//        capacity = capacity * 2;
//        MinHeapNode **tmp = new MinHeapNode *[capacity];
//        for (int i = 0; i < capacity; i++) {
//            tmp[i] = new MinHeapNode(NULL, 0);
//        }
//        for (int i = 0; i < numElements; i++) {
//            tmp[i] = array[i];
//        }
//        *array = *tmp;
//        delete[] tmp;
//    }

//    void halfSize() {
//        capacity = capacity / 2;
//        MinHeapNode **tmp = new MinHeapNode *[capacity];
//        for (int i = 0; i < capacity; i++) {
//            tmp[i] = new MinHeapNode(NULL, 0);
//        }
//        for (int i = 0; i < numElements; i++) {
//            tmp[i] = array[i];
//        }
//        *array = *tmp;
//        delete[] tmp;
//    }


    /* Made 2 inserts, one with the weight, one without
     I realize this isn't the best practice for it
     (if statement would probably be best, and initializing weight to 0/NULL)
     but gimme a break, this is due today */
    void insert(AdjacencyListNode *adjNode, int index) {
        if (numElements == capacity - 1) {
//            doubleSize();
        }
        MinHeapNode *node = new MinHeapNode(adjNode, index);
        numElements++;
        array[numElements] = node;
//        cout << "Sorting about to start" << endl;
        Heapify(numElements); //Sorts to Max Heap
//        cout << "Sorting finished" << endl;

    }

    void insert(AdjacencyListNode *adjNode, int index, double weight) {
//        if (numElements == capacity - 1) {
//            cout << "going into double size" << endl;
////            doubleSize();
//        }
        MinHeapNode *node = new MinHeapNode(adjNode, index, weight);
        numElements++;
        array[numElements] = node;
//        cout << "Sorting about to start" << endl;
        Heapify(numElements); //Sorts to Max Heap
//        cout << "Sorting finished" << endl;

    }

    bool isHere(MinHeapNode *node) {
//        cout << "is here started, num elements is: " << numElements << endl;
        for(int i = 1; i < numElements-1; i++) {
//            cout << "array name is: ";
//            cout << array[i]->getNode()->getVertex()->getName() << endl;
//            cout << "node name is: ";
//            cout << node->getNode()->getVertex()->getName() << endl;

            if(array[i]->getNode()->getVertex()->getName() == node->getNode()->getVertex()->getName()) {
//                cout << "Is here" << endl;
                return true;
            }
        }
//        cout << "Is NOT here " << endl;
        return false;
    }

    MinHeapNode *getNode(string nodeName) {
        for (int i = 1; i < numElements; i++) {
//            cout << "i is: " << i << endl;
//            cout << "array at this elements name is: " << array[i]->getNode()->getVertex()->getName() << endl;
//            cout << "node name is: " << nodeName << endl;
//            cout << "i is " << i << endl;
            if(array[i]->getNode()) {
                if (array[i]->getNode()->getVertex()->getName() == nodeName) {
                    cout << "if statement activated" << endl;
                    return array[i];
                }
            }

//            cout << "if statement passed" << endl;
        }
        cout << "returning NULL" << endl;
        return NULL;
    }

    void Heapify(int nodeIndex) {
        int i = PARENT(nodeIndex);
        int l = nodeIndex - 1;
        int r = nodeIndex + 1;
        if (nodeIndex > 1) {
            if (nodeIndex % 2 == 0) { //Inside Left Tree
                if (array[nodeIndex]->getWeight() < array[i]->getWeight()) {
                    //If Left < Parent, Swap
                    MinHeapNode *tmp = array[i];
                    array[i] = array[nodeIndex];
                    array[nodeIndex] = tmp;
                }
            }
            if (nodeIndex % 2 != 0) { //Inside Right Tree
                if (array[nodeIndex]->getWeight() < array[i]->getWeight()) {
                    //If Right < Parent, Swap
                    MinHeapNode *tmp = array[i];
                    array[i] = array[nodeIndex];
                    array[nodeIndex] = tmp;
                }   //If Left > Right, Swap
                if (array[l] != NULL) {
                    if (array[l]->getWeight() > array[nodeIndex]->getWeight()) {
                        MinHeapNode *tmp = array[l];
                        array[l] = array[nodeIndex];
                        array[nodeIndex] = tmp;
                    }
                }
            }
        }

        if (i > 1) {
            //Recursion
            Heapify(i);
        }
    }

    MinHeapNode *delMin() {
//        if (numElements == capacity / 4) {
//            halfSize();
//        }
        MinHeapNode *topNode = array[1];
//        for(int i=1; i < numElements; i++) {
//            cout << array[i]->getNode()->getVertex()->getName() << endl;
//        }
        array[1] = array[numElements]; //Replaces first element with last
        int counter = numElements;
        while (counter > 0) {
            Heapify(counter); //Return to max heap
            counter--;
        }
        numElements--; //Get rid of last element
//        cout << "num elements goes to " << numElements << endl;


        return topNode;
    }

    void display() {
        if (empty()) {
            cerr << "Heap is Empty." << endl;
            return;
        }
        for (int i = 1; i <= numElements; i++) {
            cout << array[i]->getNode()->getVertex()->getName() << ":" << array[i]->getWeight() << "   ";
        }
        cout << "\n";
    }
};
