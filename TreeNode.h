#pragma once
#include <iostream>
using namespace std;

template<class Type>class TreeNode {
private:
    int key, balanceFactor;
    Type value;
    TreeNode *parent;
    TreeNode *children;
    TreeNode *sibling;
    TreeNode *left;
    TreeNode *right;
public:
    TreeNode(string treeType, int key, Type value) {
        if(treeType == "General"){
            this->key = key;
            this->value = value;
            this->children = nullptr;
            this->sibling = nullptr;
        }
        else if(treeType == "Heap"){
            this->key = key;
            this->value = value;
        }
        else if(treeType == "AVL"){
            this->key = key;
            this->value = value;
            this->left = nullptr;
            this->right = nullptr;
        }
        else{
            cout << "Node could not be created. Try again." << endl;
        }
    }

    TreeNode(string treeType, int key) {
        if(treeType == "General"){
            this->key = key;
            this->value = 0;
            this->children = nullptr;
            this->sibling = nullptr;
        }
        else if(treeType == "Heap"){
            this->key = key;
            this->value = 0;
        }
        else if(treeType == "AVL"){
            this->key = key;
            this->value = 0;
            this->left = nullptr;
            this->right = nullptr;
        }
        else{
            cout << "Node could not be created. Try again." << endl;
        }
    }

    TreeNode(string treeType, Type value) {
        if(treeType == "General"){
            this->value = value;
            this->children = nullptr;
            this->sibling = nullptr;
        } else if(treeType == "Heap"){
            this->key = 0;
            this->value = value;
        } else if(treeType == "AVL"){
            this->key = 0;
            this->value = value;
            this->left = nullptr;
            this->right = nullptr;
        } else{
            cout << "Node could not be created. Try again." << endl;
        }
    }


    TreeNode(string treeType) {
        if(treeType == "General"){
            this->key = 0;
            this->children = nullptr;
            this->sibling = nullptr;
        }
        else if(treeType == "Heap"){
            this->key = 0;
            this->left = nullptr;
            this->right = nullptr;
        }
        else if(treeType == "AVL"){
            this->key = 0;
            this->left = nullptr;
            this->right = nullptr;
        }
        else{
            cout << "Node could not be created. Try again." << endl;
        }
    }

    int getKey() const {
        return key;
    }

    void setKey(int key) {
        this->key = key;
    }

    Type getValue() const {
        return value;
    }

    void setValue(Type value) {
        this->value = value;
    }

    TreeNode *getParent() const {
        return parent;
    }

    void setParent(TreeNode *parent) {
        this->parent = parent;
    }

    TreeNode *getChildren() const {
        return children;
    }

    void setChildren(TreeNode *children) {
        this->children = children;
    }

    TreeNode *getSibling() const {
        return sibling;
    }

    void setSibling(TreeNode *sibling) {
        this->sibling = sibling;
    }

    TreeNode *setLeft(TreeNode *left) {
        this->left = left;
        return left;
    }

    TreeNode *getLeft() {
        return left;
    }

    TreeNode *setRight(TreeNode *right) {
        this->right = right;
        return right;
    }
    TreeNode *getRight() const {
        return right;
    }

    int getBalanceFactor() {
        return this->balanceFactor;
    }

    int setBalanceFactor(int x) {
        balanceFactor = x;
        return balanceFactor;
    }
};
