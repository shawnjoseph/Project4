#include <iostream>
#include <string>
using namespace std;

const int MAX_ID = 1000;

template <class Key, class Value> class Vertex {
private:
    Key key;
    Value value;
public:
    int id = 0;
    Vertex *next;
    Vertex()
    {
        id = ++id;
        next = nullptr;
    }

    Vertex(Key key, Value value){
        this->key = key;
        this->value = value;
        id = ++id;
        next = nullptr;
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

    void setValue(Value & value){
        this->value = value;
    }
    Value & getValue(){
        return this->value;
    }
};

