//
// Created by Dragos Surugiu on 3/23/2021.
//

#ifndef COMPRESSIONTOOL_HUFFMAN_H
#define COMPRESSIONTOOL_HUFFMAN_H

#endif //COMPRESSIONTOOL_HUFFMAN_H

#include<queue>
#include "../BST_Class/BST.h"
#include<unordered_map>
#include<iostream>
#include <fstream>
#include <algorithm>

struct entry {
    char c;
    int freq;
};

using namespace std;



class Huffman {

private:
    bst_node *root;
    unordered_map<char, pair<int, int> > huffman_table{};
public:
    explicit Huffman(char *file_name);
    bst_node * build_huffman_tree(entry arr[]);
    void encode_huffman_in_file(char *input_file, char *output_file);
    void decode_huffman_in_file(const unordered_map<char, pair <int, int> >& huffmanTable, char *input_file, char *output_file);
    void create_huffman_table(bst_node *tree, int bits);
    unordered_map<char, pair<int, int> > get_huffman_table();
};
