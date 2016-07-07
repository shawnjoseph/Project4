#include <iostream>
#include "Vertex.h"

using namespace std;

template<class Key, class Value>
class HashTable {
    friend class Graph;
protected:
    // To be filled in later
    int tableSize;
    int numOfEntries;
    double loadFactor;
    const double THRESHOLD = 0.3;
    Key hashResult;
    Vertex<Key, Value> **table;

public:

    HashTable() {
        tableSize = 20;
        table = new Vertex<Key, Value> *[tableSize];
        numOfEntries = 0;
        // Set all values to NULL as default
        for (int i = 0; i < tableSize; i++) {
            table[i] = NULL;
        }
    }

    ~HashTable() {
        for(int i=0; i < numOfEntries; i++) {
            if(table[i]->next != NULL) {
                Vertex<Key, Value> *ptr = table[i];
                while(ptr != NULL) {
                    Vertex<Key, Value> *temp = ptr;
                    ptr = ptr->next;
                    delete *temp;
                }
            } else {
                delete table[i];
            }
        }
    }


    Value *search(Key query) {
        // Searches for a value in the hashmap
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
                if (table[i]->getKey() == hashResult) {
                    // If a result is found
                    if ((table[i]->next) != NULL) {
                        // Means that there is more than one value there
                        Vertex<Key, Value> *ptr = table[i];
                        int arraySize = 0;
                        while (ptr != NULL) {
                            // Figuring out the size array should be
                            arraySize++;
                            ptr = ptr->next;
                        }
                        Value *result = new Value[arraySize];
                        ptr = table[i];
                        cout << "List of results: " << endl;
                        for (int j = 0; j < arraySize; j++) {
                            result[j] = ptr->getValue();
                            ptr = ptr->next;
                            cout << result[j] << endl;
                        }
                        return result;
                    } else {
                        // Means there's only one value there
                        Value *result = new Value[1];
                        result[0] = table[i]->getValue();
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

    void insertValue(Key key, Value value) {
        // Boolean to track whether the for loop found any value
        bool blankInsert = true;
        // Inserts a value into the hashmap
        loadFactor = numOfEntries / (double) tableSize;
        int intKey = 0;
        for (int i = 0; i < key.length(); i++) {
            intKey += key[i];
        }
        hashResult = to_string((intKey * 1000) % 31);
        for (int i = 0; i < tableSize; i++) {
            if (table[i] != NULL) {
                if (table[i]->getKey() == hashResult) {
                    blankInsert = false;
                    if (table[i]->next != NULL) {
                        // Means there's already a value in there,
                        // must implement chaining
                        Vertex<Key, Value> *ptr = table[i];
                        while (ptr->next != NULL) {
                            // Just setting ptr to the last node
                            ptr = ptr->next;
                        }
                        ptr->next = new Vertex<Key, Value>(hashResult, value);
                    } else {
                        table[i]->next = new Vertex<Key, Value>(hashResult, value);
                    }
                }
            }
        }
        if (blankInsert) {
            // No key value matches, creating new space
            numOfEntries++;
            table[numOfEntries - 1] = new Vertex<Key, Value>(hashResult, value);
        }
        // Checking to see if need to increase size of HashMap
        if (loadFactor > THRESHOLD) {
            int oldTableSize = tableSize;
            tableSize *= 2;
//            cout << "Resizing array to " << tableSize << endl;
            Vertex<Key, Value> **temp = table;
            table = new Vertex<Key, Value> *[tableSize];
            for (int i = 0; i < oldTableSize; i++) {
                table[i] = temp[i];
            }
            delete temp;
        }

    }

    void deleteValue(Key key) {
        // Deletes a value from the hashmap
        bool found = false;
        hashResult = hash<Key>()(key);
        for (int i = 0; i < numOfEntries; i++) {
            if (table[i] != NULL) {
                if (table[i]->getKey() == hashResult) {
                    found = true;
                    if (table[i]->next != NULL) {
                        // There's more than one value
                        Vertex<Key, Value> *temp = table[i];
                        while (temp->next != NULL) {
                            Vertex<Key, Value> *toDelete = temp;
                            temp = temp->next;
                            delete (toDelete);
                        }
                        for (int j = i + 1; j < numOfEntries; j++) {
                            *table[i] = *table[j];
                            table[numOfEntries-1] = NULL;
                        }
                    } else {
                        // Only one element in there
                        Vertex<Key, Value> *temp = table[i];
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
            cout << "Key value was not found" << endl;
        }
    }

    void print() {
        int counter = 1;
        for (int i = 0; i < numOfEntries; i++) {
            if (table[i] != NULL) {
                if(table[i]->next != NULL) {
                    // More than one value
                    Vertex<Key, Value> *ptr = table[i];
                    while(ptr != NULL) {
                        cout << "Item number: " << counter << endl;
                        cout << "Key: " << ptr->getKey() << endl;
                        cout << "Value: " << ptr->getValue() << endl;
                        ptr = ptr->next;
                        counter++;
                    }
                } else {
                    cout << "Item number: " << counter << endl;
                    cout << "Key: " << table[i]->getKey() << endl;
                    cout << "Value: " << table[i]->getValue() << endl;
                    counter++;
                }
            } else {
                cout << "Null value" << endl;
            }

        }
    }
};

