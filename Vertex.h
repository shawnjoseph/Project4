#pragma once
#include <iostream>
#include <string>
#include "Edge.h"
using namespace std;

const int MAX_ID = 1000;

template <class Name, class Data> class Vertex {
private:
    Name name;
    Data data;
public:
    int id = 0;
    Vertex *next;
    Vertex()
    {
        id = ++id;
        next = nullptr;
    }

    Vertex(Name key, Data value){
        this->name = key;
        this->data = value;
        id = ++id;
        next = nullptr;
    }

    int getID(){
        return id;
    }

    void setName(string name){
        this->name = name;
    }
    string getName(){
        return this->name;
    }

    void setData(Data & data){
        this->data = data;
    }
    Data & getData(){
        return this->data;
    }

    void addEdge(Vertex &v, Vertex &u){
    }
};