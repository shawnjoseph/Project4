#pragma once
#include <iostream>
#include "AdjacencyListNode.h"

using namespace std;

class minHeapNode {
private:
    AdjacencyListNode *node;
    int index;
    double weight;

public:
    minHeapNode(AdjacencyListNode *node, int index, double weight) {
        this->node = node;
        this->index = index;
    }


    AdjacencyListNode *getNode() const { return node; }

    double getWeight() { return weight; }

    int getIndex() { return index; }
};
