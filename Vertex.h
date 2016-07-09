#pragma once
#include <iostream>
#include <string>
#include "Edge.h"
using namespace std;

const int MAX_ID = 1000;

template <class Data> class Vertex {
private:
    string name;
    Data data;
public:
    int id = 0;
    Vertex *next;
    Vertex()
    {
        if(id >= MAX_ID){
            cerr << "Max ID reached." << endl;
        }
        else{
            id = ++id;
            next = nullptr;
        }
    }

    Vertex(string name, Data data){
        if(id >= MAX_ID){
            cerr << "Max ID reached." << endl;
        }
        else {
            this->name = name;
            this->data = data;
            id = ++id;
            next = nullptr;
        }
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