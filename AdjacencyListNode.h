#pragma once

#include "AdjacencyList.h"
#include "Vertex.h"

using namespace std;

class AdjacencyListNode {
private:
    string name;

public:
    AdjacencyListNode *next;

    AdjacencyListNode(string name, AdjacencyListNode *next) {
        this->name = name;
        this->next = next;
    }

    string getName() const { return name; }

    void setName(string name) { this->name = name; }

    AdjacencyListNode *getNext() const { return next; };

};
