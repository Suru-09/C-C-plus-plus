#include "BTree.h"
#include<iostream>


Node::Node(int t, bool leaf) {
    this->t = t;
    this->leaf = leaf;

    keys = new int[2 * t - 1];
    values = new
    children = new Node *[2 * t];
    n = 0;  //initialising
}

void Node::traverse() {

    int i;
    for(i = 0 ; i < n ; ++i) {
        if(!leaf)
            children[i]->traverse();
        cout <<" " << keys[i];
    }

    //it wouldn't go on the following subtree if not for this
    if(!leaf)
        children[i]->traverse();
}
void BTree::traverse() {

    if(root)
        root->traverse();
}

BTree::BTree(int t) {
    this->t = t;
    root = nullptr;
}

void Node::BTreeSplitChild(Node *y, int i) {

    //create new node to store half of elements
    Node *z = new Node(y->t, y->leaf);
    z->n = t - 1;

    //copy the keys into the z node
    for(int j = 0 ; j < t - 1; ++j)
        z->keys[j] = y->keys[t + j];

    //copy the children of y to z(last t ones)
    if( !(y->leaf) )
        for(int j = 0;  j < t; ++j)
            z->children[j] = y->children[t + j];

    /*
     Being a full node y had 2t - 1 children, therefore
     after moving t children we have only t-1 children left
     */
    y->n = t - 1;

    //Make some space for the new child
    for(int j = n ; j >= i + 1; --j ) {
        children[j + 1] = children[j];
    }

    //linking the new child
    children[i + 1] = z;

    for(int j = n - 1 ; j >= i ; --j)
        keys[j + 1] = keys[j];

    keys[i] = y->keys[t - 1];
    n++;
}

void Node::insertNonfull(int key) {

    int i = n - 1;

    if(leaf) {
        while(i >= 0 && key < keys[i]) {
            keys[i + 1] = keys[i];
            --i;
        }
        keys[i + 1] = key;
        n++;
    }
    else {
        while(i >= 0 && key < keys[i])
            --i;

        if(children[i + 1]->n == 2 * t - 1) {
            BTreeSplitChild(children[i + 1], i + 1);

            if(key > keys[i + 1])
                ++i;
        }

        children[i + 1]->insertNonfull(key);
    }
}
void BTree::insert(int key) {

    if(!root) {
        root = new Node(t, true);
        root->keys[0] = key;
        root->n = 1;
    }
    else {
        if(root->n == 2 * t - 1) {

            Node* new_node = new Node(t, false);

            new_node->children[0] = root;
            new_node->BTreeSplitChild(root, 0);

            if(new_node->keys[0] < key)
                new_node->children[1]->insertNonfull(key);
            else
                new_node->children[0]->insertNonfull(key);

            //finally change root
            root = new_node;
        }
        else {
            root->insertNonfull(key);
        }
    }

}


