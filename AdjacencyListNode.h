#pragma once

#include "AdjacencyList.h"
#include "Vertex.h"

using namespace std;

class AdjacencyListNode {
private:
    Vertex<Data> *vertex;

public:
    AdjacencyListNode *next;

    AdjacencyListNode(Vertex<Data> *vertex, AdjacencyListNode *next) {
        this->vertex = vertex;
        this->next = next;
    }

    ~AdjacencyListNode() {
//        while(this->next != NULL){
//            AdjacencyListNode * tmp = this->next;
//            this = tmp;
//            delete tmp;
//        }
//        delete this;
    }

    Vertex<Data> *getVertex() const {
        return vertex;
    }

    AdjacencyListNode *getNext() const { return next; };

};
