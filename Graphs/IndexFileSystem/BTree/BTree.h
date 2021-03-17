#ifndef LAB4_BTREE_H
#define LAB4_BTREE_H

#endif //LAB4_BTREE_H

using namespace std;
#include<vector>

class Node {
private:

    int *keys; //key vector
    int *values; // values vector

    int n;  //number of keys stored in node

    int t; //minimum degree
    Node **children;   // vector for children

    bool leaf;  //leaf or not?

public:
    Node(int t, bool leaf);
    void traverse();
    void BTreeSplitChild(Node* y, int i);
    void insertNonfull();

    friend class BTree;
};

class BTree {

private:

    Node *root;
    int t;

public:
    explicit BTree(int t);
    void traverse();
    void insert(int key);


};

