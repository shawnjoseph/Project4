#pragma once
#include <iostream>
#include <string>
#include "Edge.h"
#include "AdjacencyListNode.h"

using namespace std;

const int MAX_ID = 1000;

template <class Data> class Vertex {
private:
    string name;
    Data data;
    int id = 0;
public:
    Vertex *next;
    Vertex<Data>()
    {
        if(id >= MAX_ID){
            cerr << "Max ID reached." << endl;
        }
        else{
            id = generateID();
            next = nullptr;
        }
    }

    Vertex<Data>(string name, Data data)
    {
        if(id >= MAX_ID){
            cerr << "Max ID reached." << endl;
        }
        else {
            id = generateID();
            this->name = name;
            this->data = data;
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

    void setData(Data data){
        this->data = data;
    }

    Data & getData(){
        return this->data;
    }

    int generateID(){
        static int newID = 0;

        return newID = ++newID;
    }
};