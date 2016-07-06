#include "Vertex.h"

class Edge {
private:
    int weight;
    Vertex *begin;
    Vertex *end;

public:
    Edge(Vertex *begin, Vertex *end, int weight){
        this->begin = begin;
        this->end = end;
        this->weight = weight;
    }

    Edge(Vertex *begin, Vertex *end){
        this->begin = begin;
        this->end = end;
    }

    Vertex * getBeginning(){
        return this->begin;
    }

    Vertex * getEnd(){
        return this->end;
    }

    int getWeight(){
        return this->weight;
    }

    void  setWeight(int weight){
        this->weight = weight;
    }
};
