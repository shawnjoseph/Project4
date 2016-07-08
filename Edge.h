#pragma once
#include "Vertex.h"

template <class Name, class Data> class Vertex;

class Edge  {
private:
    double weight;
    Vertex<class Name, class Data> *begin;
    Vertex<class Name, class Data> *end;

public:
    Edge(Vertex<class Name, class Data> *begin, Vertex<class Name, class Data> *end, int weight){
        this->begin = begin;
        this->end = end;
        this->weight = weight;
    }

    Edge(Vertex <Name, Data> *begin, Vertex<Name, Data> *end){
        this->begin = begin;
        this->end = end;
    }

    ~Edge(){
        this->begin = nullptr;
        this->end = nullptr;
        this->weight = 0;
    }

    Vertex<class Name, class Data> * getBeginning(){
        return this->begin;
    }

    Vertex<class Name, class Data>* getEnd(){
        return this->end;
    }

    double getWeight(){
        return this->weight;
    }

    void  setWeight(double weight){
        this->weight = weight;
    }
};
