//
// Created by Dragos Surugiu on 3/23/2021.
//

#ifndef COMPRESSIONTOOL_BST_H
#define COMPRESSIONTOOL_BST_H

#endif //COMPRESSIONTOOL_BST_H


struct bst_node {
    char c;
    int freq;

    bool is_leaf;
    struct bst_node *left, *right;
};

bst_node *create_node(char c, int freq);


