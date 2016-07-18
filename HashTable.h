#pragma once
#include <iostream>
#include "Vertex.h"

using namespace std;

template<class Data> class HashTable {
protected:
    // To be filled in later
    int tableSize;
    double loadFactor;
    const double THRESHOLD = 0.3;
    string hashResult;
    Vertex<Data> **table;

public:
    int numOfEntries;

    HashTable() {
        tableSize = 20;
        table = new Vertex<Data> *[tableSize];
        numOfEntries = 0;
        // Set all values to NULL as default
        for (int i = 0; i < tableSize; i++) {
            table[i] = NULL;
        }
    }

    ~HashTable() {
        for(int i=0; i < numOfEntries; i++) {
            if(table[i]->next != NULL) {
                Vertex<Data> *ptr = table[i];
                while(ptr != NULL) {
                    Vertex<Data> *temp = ptr;
                    ptr = ptr->next;
                    delete temp;
                }
            } else {
                delete table[i];
            }
        }
    }


    Vertex<Data> *search(string query) {
        // Searches for a data in the hashmap
        int intKey = 0;
        for (int i = 0; i < query.length(); i++) {
            intKey += query[i];
        }
        hashResult = to_string((intKey * 1000) % 31);
        /*
         * Ok NOW LISTEN
         * Don't listen to that guy up above
         * You don't need a 2 dimensional array, you've been working for too long
         * You need to just make a 1 dimensional array of HashNodes like you were
         * Except instead of making the index the hash result
         * Do the same thing you were where you loop through the array,
         * look for the HashNode with a matching key. Except do it like this
         * table[i]->key == hashResult
         * Duh
         *
         * Do that in the AM, get some sleep
         */

        for (int i = 0; i < tableSize; i++) {
            if (table[i] != NULL) {
                if (table[i]->getName() == hashResult) {
                    // If a result is found
                    if ((table[i]->next) != NULL) {
                        // Means that there is more than one data there
                        Vertex<Data> *ptr = table[i];
                        int arraySize = 0;
                        while (ptr != NULL) {
                            // Figuring out the size array should be
                            arraySize++;
                            ptr = ptr->next;
                        }
                        Data *result = new Data[arraySize];
                        ptr = table[i];
                        cout << "List of results: " << endl;
                        for (int j = 0; j < arraySize; j++) {
                            result[j] = ptr->getData();
                            ptr = ptr->next;
                            cout << result[j] << endl;
                        }
                        return result;
                    } else {
                        // Means there's only one data there
                        Data *result = new Data[1];
                        result[0] = table[i]->getData();
                        cout << "List of results: " << endl;
                        cout << result[0] << endl;
                        return result;
                    }
                }
            }
        }
        // If no result is found
        cout << "Search query not found!" << endl;
        return NULL;
    }

    void insertValue(string name, double data) {
        // Boolean to track whether the for loop found any data
        bool blankInsert = true;
        // Inserts a data into the hashmap
        loadFactor = numOfEntries / (double) tableSize;
        int intKey = 0;
        for (int i = 0; i < name.length(); i++) {
            intKey += name[i];
        }
        hashResult = to_string((intKey * 1000) % 31);
        for (int i = 0; i < tableSize; i++) {
            if (table[i] != NULL) {
                if (table[i]->getName() == hashResult) {
                    blankInsert = false;
                    if (table[i]->next != NULL) {
                        // Means there's already a data in there,
                        // must implement chaining
                        Vertex<Data> *ptr = table[i];
                        while (ptr->next != NULL) {
                            // Just setting ptr to the last node
                            ptr = ptr->next;
                        }
                        ptr->next = new Vertex<Data>(hashResult, data);
                    } else {
                        table[i]->next = new Vertex<Data>(hashResult, data);
                    }
                }
            }
        }
        if (blankInsert) {
            // No key data matches, creating new space
            numOfEntries++;
            table[numOfEntries - 1] = new Vertex<Data>(hashResult, data);
        }
        // Checking to see if need to increase size of HashMap
        if (loadFactor > THRESHOLD) {
            int oldTableSize = tableSize;
            tableSize *= 2;
//            cout << "Resizing array to " << tableSize << endl;
            Vertex<Data> **temp = table;
            table = new Vertex<Data> *[tableSize];
            for (int i = 0; i < oldTableSize; i++) {
                table[i] = temp[i];
            }
            delete temp;
        }

    }

    void deleteValue(string name) {
        // Deletes a data from the hashmap
        bool found = false;
        hashResult = hash<string>()(name);
        for (int i = 0; i < numOfEntries; i++) {
            if (table[i] != NULL) {
                if (table[i]->getName() == hashResult) {
                    found = true;
                    if (table[i]->next != NULL) {
                        // There's more than one data
                        Vertex<Data> *temp = table[i];
                        while (temp->next != NULL) {
                            Vertex<Data> *toDelete = temp;
                            temp = temp->next;
                            delete (toDelete);
                        }
                        for (int j = i + 1; j < numOfEntries; j++) {
                            *table[i] = *table[j];
                            table[numOfEntries-1] = NULL;
                        }
                    } else {
                        // Only one element in there
                        Vertex<Data> *temp = table[i];
                        for (int j = i + 1; j < numOfEntries; j++) {
                            *table[i] = *table[j];
                            table[numOfEntries-1] = NULL;
                        }
                        delete temp;
                    }
                }
            }

        }
        if(found) {
            numOfEntries--;
        } else {
            cout << "Key data was not found" << endl;
        }
    }

    void print() {
        int counter = 1;
        for (int i = 0; i < numOfEntries; i++) {
            if (table[i] != NULL) {
                if(table[i]->next != NULL) {
                    // More than one data
                    Vertex<Data> *ptr = table[i];
                    while(ptr != NULL) {
                        cout << "Item number: " << counter << endl;
                        cout << "Name: " << ptr->getName() << endl;
                        cout << "Data: " << ptr->getData() << endl;
                        ptr = ptr->next;
                        counter++;
                    }
                } else {
                    cout << "Item number: " << counter << endl;
                    cout << "Key: " << table[i]->getName() << endl;
                    cout << "Data: " << table[i]->getData() << endl;
                    counter++;
                }
            } else {
                cout << "Null data" << endl;
            }

        }
    }
};