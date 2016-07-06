#include <iostream>
#include <string>
using namespace std;

const int MAX_ID = 1000;

template <class Type> class Vertex {
private:
    string key;
    Type value;
    int id = 0;

public:
    Vertex()
    {
        id = ++id;
    }

    Vertex(string key, Type value){
        this->key = key;
        this->value = value;
        id = ++id;
    }

    int getID(){
        return id;
    }

    void setKey(string key){
        this->key = key;
    }
    string getKey(){
        return this->key;
    }

    void setValue(Type & value){
        this->value = value;
    }
    Type & getValue(){
        return this->value;
    }

};

