#ifndef LAB4_BTREE_H
#define LAB4_BTREE_H

#endif //LAB4_BTREE_H

using namespace std;

#include<vector>
#include <cstdint>
#include<fstream>

class Node {
private:

    uint64_t *keys; //key vector
    uint64_t *values; // values vector

    int offset_in_file;
    int n;  //number of keys stored in node

    int t; //minimum degree
    Node **children;   // vector for children

    bool leaf;  //leaf or not?

public:
    Node(int t, bool leaf);
    void traverse();
    void right_in_file(char *file_name);
    void BTreeSplitChild(Node* y, int i);
    void insertNonfull(uint64_t key, uint64_t value);

    friend class BTree;
};

class BTree {

private:

    Node *root;
    int t;
    int key_size; //size of the key

public:
    explicit BTree(int t, int keysize);
    void traverse();
    void insert(uint64_t key, FILE* file_iterator);


};

