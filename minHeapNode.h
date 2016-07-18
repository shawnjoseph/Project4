#pragma once
#include <iostream>
#include "AdjacencyListNode.h"

using namespace std;

class MinHeapNode {
private:
    AdjacencyListNode *node;
    int index;
    double weight;

public:
    MinHeapNode() {};
    MinHeapNode(AdjacencyListNode *node, int index) {
        this->node = node;
        this->index = index;
    }

    MinHeapNode(AdjacencyListNode *node, int index, double weight) {
        this->node = node;
        this->index = index;
        this->weight = weight;
    }

    AdjacencyListNode *getNode() const { return node; }

    double getWeight() { return weight; }

    void setWeight(double weight) {
        MinHeapNode::weight = weight;
    }

    int getIndex() { return index; }
};
