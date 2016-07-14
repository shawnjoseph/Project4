#pragma once

#include "AdjacencyList.h"
#include "Vertex.h"

using namespace std;

class AdjacencyListNode {
private:
    string name;
    double data;
    Vertex<Data> *vertex;

public:
    AdjacencyListNode *next;

    AdjacencyListNode(string name, Vertex<Data> *vertex, AdjacencyListNode *next) {
        this->name = name;
        this->vertex = vertex;
        this->next = next;

    }

    string getName() const { return name; }


    Vertex<Data> *getVertex() const {
        return vertex;
    }

    double getData() const { return data; }

    void setName(string name) { this->name = name; }

    void setData(double data) { this->data = data; }

    AdjacencyListNode *getNext() const { return next; };

};
