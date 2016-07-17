#include "TreeNode.h"
#include <cmath>
#include <fstream>

#define PARENT(i)  (i/2)
#define LEFT(i) (2*i)

const int INITIAL_CAP = 8;


template <class Type> class Heap {
private:
    TreeNode<Type> * node;
    TreeNode<Type> ** array;
    int numElements;
    int capacity;

public:
    Heap(){
        array = new TreeNode<Type>*[INITIAL_CAP];
        numElements = 0;
        capacity = INITIAL_CAP;
        for(int i=0; i < capacity; i++){
            array[i] = new TreeNode<Type>("Heap", 0, "");
        }
    }

    ~Heap(){
        delete [] array;
    }

    TreeNode<Type>* getMax(){ return array[1]; }
    int getSize(){ return numElements; }

    int getHeight() {
        double height = (log(numElements) / log(2));
        return (int) height;
    }
    bool empty(){ return numElements == 0; }

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
            array[i] = new TreeNode<Type>("Heap", 0, "");
        }
        numElements = 0;
    }

    void doubleSize() {
        capacity = capacity*2;
        TreeNode<Type> **tmp = new TreeNode<Type>*[capacity];
        for(int i=0; i < capacity; i++){
            tmp[i] = new TreeNode<Type>("Heap", 0, "");
        }
        for(int i = 0; i < numElements; i++){
            tmp[i] = array[i];
        }
        *array = *tmp;
        delete [] tmp;
    }

    void halfSize() {
        capacity = capacity / 2;
        TreeNode<Type> **tmp = new TreeNode<Type> *[capacity];
        for (int i = 0; i < capacity; i++) {
            tmp[i] = new TreeNode<Type>("Heap", 0, "");
        }
        for (int i = 0; i < numElements; i++) {
            tmp[i] = array[i];
        }
        *array = *tmp;
        delete[] tmp;
    }

    void insert(int key, Type & data) {
        if(numElements == capacity - 1){
            doubleSize();
        }
        node = new TreeNode<Type>("Heap", key, data);
        numElements++;
        array[numElements] = node;
        Heapify(numElements); //Sorts to Max Heap
    }

    void Heapify(int nodeIndex){
        int i = PARENT(nodeIndex);
        int l = nodeIndex - 1;
        int r = nodeIndex + 1;
        if (nodeIndex > 1) {
            if (nodeIndex % 2 == 0) { //Inside Left Tree
                if (array[nodeIndex]->getKey() > array[i]->getKey()) {
                    //If Left > Parent, Swap
                    TreeNode<Type> *tmp = array[i];
                    array[i] = array[nodeIndex];
                    array[nodeIndex] = tmp;
                }
            }
            if (nodeIndex % 2 != 0) { //Inside Right Tree
                if (array[nodeIndex]->getKey() > array[i]->getKey()) {
                    //If Right > Parent, Swap
                    TreeNode<Type> *tmp = array[i];
                    array[i] = array[nodeIndex];
                    array[nodeIndex] = tmp;
                }   //If Left < Right, Swap
                if (array[l] != NULL) {
                    if (array[l]->getKey() < array[nodeIndex]->getKey()) {
                        TreeNode<Type> *tmp = array[l];
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
    void Display() {
        if (empty()) {
            cerr << "Heap is Empty." << endl;
            return;
        }
        for(int i = 1; i <= numElements; i++){
            cout << array[i]->getKey() << ":" << array[i]->getValue() << "   ";
        }
        cout << "\n";
    }
};