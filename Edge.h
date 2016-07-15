#pragma once
#include "Vertex.h"

template <class Data> class Vertex;

class Edge  {
private:
    double weight;
    Vertex<class Data> *origin;
    Vertex<class Data> *destination;

public:
    Edge(Vertex<Data> *begin, Vertex<Data> *end, double weight) {
        this->origin = begin;
        this->destination = end;
        this->weight = weight;
    }

    Edge(Vertex<Data> *begin, Vertex<Data> *end){
        this->origin = begin;
        this->destination = end;
    }

    Edge() {
        this->origin = nullptr;
        this->destination = nullptr;
        this->weight = 0;
    }

    ~Edge(){
        this->origin = nullptr;
        this->destination = nullptr;
        this->weight = 0;
    }

    Vertex<class Data> *getBeginning(){
        return this->origin;
    }

    Vertex<class Data> *getEnd(){
        return this->destination;
    }

    double getWeight(){
        return this->weight;
    }

    void setWeight(double weight){
        this->weight = weight;
    }
};
