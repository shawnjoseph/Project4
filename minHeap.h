#include <iostream>
#include <cmath>
#include <fstream>
#include "minHeapNode.h"

#define PARENT(i)  (i/2)
#define LEFT(i) (2*i)

using namespace std;
const int INITIAL_CAP = 20;

class minHeap {
private:
    minHeapNode *node;
    minHeapNode **array;
    int numElements;
    int capacity;

public:
    minHeap() {
        array = new minHeapNode *[INITIAL_CAP];
        numElements = 0;
        capacity = INITIAL_CAP;
        for (int i = 0; i < capacity; i++) {
            array[i] = new minHeapNode(NULL, 0, 0);
        }
    }

    ~Heap() {
        delete[] array;
    }

    minHeapNode *getMax() { return array[1]; }

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
            array[i] = new minHeapNode(NULL, 0, 0);
        }
        numElements = 0;
    }

    void doubleSize() {
        capacity = capacity * 2;
        minHeapNode **tmp = new minHeapNode *[capacity];
        for (int i = 0; i < capacity; i++) {
            tmp[i] = new minHeapNode(NULL, 0, 0);
        }
        for (int i = 0; i < numElements; i++) {
            tmp[i] = array[i];
        }
        *array = *tmp;
        delete[] tmp;
    }

    void halfSize() {
        capacity = capacity / 2;
        minHeapNode **tmp = new minHeapNode *[capacity];
        for (int i = 0; i < capacity; i++) {
            tmp[i] = new minHeapNode(NULL, 0, 0);
        }
        for (int i = 0; i < numElements; i++) {
            tmp[i] = array[i];
        }
        *array = *tmp;
        delete[] tmp;
    }

    void insert(AdjacencyListNode *adjNode, int index, double weight) {
        if (numElements == capacity - 1) {
            doubleSize();
        }
        node = new minHeapNode(adjNode, index, weight);
        numElements++;
        array[numElements] = node;
        Heapify(numElements); //Sorts to Max Heap
    }

    void Heapify(int nodeIndex) {
        int i = PARENT(nodeIndex);
        int l = nodeIndex - 1;
        int r = nodeIndex + 1;
        if (nodeIndex > 1) {
            if (nodeIndex % 2 == 0) { //Inside Left Tree
                if (array[nodeIndex]->getWeight() < array[i]->getWeight()) {
                    //If Left < Parent, Swap
                    minHeapNode *tmp = array[i];
                    array[i] = array[nodeIndex];
                    array[nodeIndex] = tmp;
                }
            }
            if (nodeIndex % 2 != 0) { //Inside Right Tree
                if (array[nodeIndex]->getWeight() < array[i]->getWeight()) {
                    //If Right < Parent, Swap
                    minHeapNode *tmp = array[i];
                    array[i] = array[nodeIndex];
                    array[nodeIndex] = tmp;
                }   //If Left > Right, Swap
                if (array[l] != NULL) {
                    if (array[l]->getWeight() > array[nodeIndex]->getWeight()) {
                        minHeapNode *tmp = array[l];
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

    void delMax() {
        if (numElements == capacity / 4) {
            halfSize();
        }
        array[1] = array[numElements]; //Replaces first element with last
        int counter = numElements;
        while (counter > 0) {
            Heapify(counter); //Return to max heap
            counter--;
        }
        numElements--; //Get rid of last element

    }
};
