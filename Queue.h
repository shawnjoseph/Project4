#pragma once
#include <iostream>

using namespace std;

template<class Type>
class Queue {
private:
    Type *array;
    int ihead;
    int itail;
    int count;
    int initialSize;
    int arraySize;

public:
    Queue() :
            initialSize(20), count(0), arraySize(initialSize), ihead(-1), itail(-1) {
        array = new Type[initialSize];
    }

    Queue(int initialSize)
            : count(0), ihead(-1), itail(-1) {
        this->initialSize = initialSize;
        arraySize = initialSize;
        array = new Type[initialSize];
    }

    ~Queue() {
        delete[] array;
        count = 0;
        ihead = -1;
        itail = -1;
    }

    Type front() const {
        if(empty()) {
            cerr << "Error. Queue is Empty." << endl;
        }
        else
            return array[ihead];
        }

    Type back() const {
        if(empty()) {
            cerr << "Error. Queue is Empty." << endl;
        }
        else
            cout << "Back: " << array[itail] << endl;
        return array[itail];
    }

    int size() const {
        cout << "Size: " << count << endl;
        return count;
    }

    int capacity() const {
        cout << "Capacity: " << arraySize << endl;
        return arraySize;
    }

    bool empty() const { return count == 0; }

    void display() {
        if(empty()){
            cerr << "Error. Queue is Empty." << endl;
        }
        else{
            for (int i = count - 1; i >= 0; i--) {
                cout << " -> " << array[i];
            }
            cout << "\n";
        }

    }

    void enqueue(Type const &data) {
        itail++;
        if (count < arraySize - 1) {
            array[itail] = data;
            ihead = 0;
            count++;
        }
        else {
            arraySize = arraySize * 2;
            Type *temp;
            temp = new Type[arraySize];
            for (int i = 0; i < count; i++) {
                temp[i] = array[i];
            }
            delete[] array;
            array = temp;
            array[itail] = data;
            count++;
        }
    }

    Type dequeue() {
        Type val = array[ihead];
        if (empty()) {
            cerr << "Error. Queue is Empty." << endl;
        }
        else {
            for (int i = 0; i < count; i++) {
                array[i] = array[i + 1];
            }
            count--;
            itail = count - 1;
        }
        if (count == arraySize / 4 && arraySize > initialSize) {
            arraySize = arraySize / 2;
            Type *temp;
            temp = new Type[arraySize];

            for (int i = 0; i < count; i++) {
                temp[i] = array[i];
            }
            delete[] array;
            array = temp;
        }
        return val;
    }

    void clear() {
        Type * temp;
        temp = new Type[initialSize];
        Queue::~Queue();
        arraySize = initialSize;
        array = temp;
    }

    int erase(Type const &data) {
        int counter = 0;
        int size = count;
        int tmp_size = 0;
        Type *temp = new Type[arraySize];

        for (int i = 0, j = 0; i < size; i++, j++) {
            Type tmp_val = dequeue();
            if (tmp_val != data) {
                temp[j] = tmp_val;
                tmp_size++;
            }
            else {
                j--;
                counter++;
            }
        }
        for (int i = 0; i < tmp_size; i++) {
            enqueue(temp[i]);
        }
        delete[] temp;
//        for (int i = 0, j = 0; i < size; i++, j++) {
//            Type tmp_val = array[i];
//            if(tmp_val != data ){
//                temp[j] = tmp_val;
//            }
//            else{
//                j--;
//                counter++;
//                count--;
//            }
//        }
//        delete [] array;
//        array = temp;

        if (count == arraySize / 4 && arraySize > initialSize) {
            arraySize = arraySize / 2;
            Type *temp2;
            temp2 = new Type[arraySize];

            for (int i = 0; i < count; i++) {
                temp2[i] = array[i];
            }
            delete[] array;
            array = temp2;
        }
        return counter;
    }
};