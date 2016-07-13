#pragma once
#include "Vertex.h"

template <class Data> class Vertex;

class Edge  {
private:
    double weight;
    Vertex<class Data> *begin;
    Vertex<class Data> *end;

public:
    Edge(Vertex<Data> *begin, Vertex<Data> *end, double weight) {
        this->begin = begin;
        this->end = end;
        this->weight = weight;
    }

    Edge(Vertex<Data> *begin, Vertex<Data> *end){
        this->begin = begin;
        this->end = end;
    }

    ~Edge(){
        this->begin = nullptr;
        this->end = nullptr;
        this->weight = 0;
    }

    Vertex<class Data> * getBeginning(){
        return this->begin;
    }

    Vertex<class Data>* getEnd(){
        return this->end;
    }

    double getWeight(){
        return this->weight;
    }

    void setWeight(double weight){
        this->weight = weight;
    }
};
