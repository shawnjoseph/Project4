#pragma once

#include "AdjacencyList.h"
#include "Vertex.h"

using namespace std;

class AdjacencyListNode {
private:
    string name;
    double data;

public:
    AdjacencyListNode *next;

    AdjacencyListNode(string name, AdjacencyListNode *next) {
        this->name = name;
        this->next = next;
    }

    string getName() const { return name; }

    double getData() const { return data; }

    void setName(string name) { this->name = name; }

    void setData(double data) { this->data = data; }

    AdjacencyListNode *getNext() const { return next; };

};
