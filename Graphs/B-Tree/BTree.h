//
// Created by Dragos Surugiu on 3/8/2021.
//

#ifndef LAB4_BTREE_H
#define LAB4_BTREE_H

#endif //LAB4_BTREE_H

class Node {
private:

    int *keys; // arrays of keys for each node
    int n;  //number of keys stored in node x

    int t; //minimum degree
    Node **children;    //array of children

    bool leaf;  //leaf or not?

public:
    Node(int t, bool leaf);
    void traverse();
    void BTreeSplitChild(Node* y, int i);
    void insertNonfull(int key);

    friend class BTree;
};

class BTree {

private:

    Node *root;
    int t;

public:
    BTree(int t);
    void traverse();
    void insert(int key);


};

