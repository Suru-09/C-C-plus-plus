//
// Created by Dragos Surugiu on 3/23/2021.
//

#include "BST.h"

bst_node* create_node(char c, int freq) {
    bst_node *node{};
    node = new bst_node();

    node->c = c;
    node->freq = freq;

    c != 'N' ? node->is_leaf = true : node->is_leaf = false;

    node->left = nullptr;
    node->right = nullptr;

    return node;
}
