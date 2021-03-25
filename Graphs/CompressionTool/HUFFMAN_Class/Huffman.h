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

    /**
     * @param file_name takes parameter the file_name which has the plain text
     * @brief the constructor opens the file, then creates the huffman tree, huffman_table
     * writing the huffman_table in a file called "huffman_table"
     */
    explicit Huffman(char *file_name);

    /**
     * @param arr take the frequency array of the plain text
     * @return returns the root of the huffman tree created
     */

    static bst_node * build_huffman_tree(entry arr[]);

    /**
     * @param input_file the file to be compressed
     * @param output_file the location where to compress the file
     */

    void encode_huffman_in_file(char *input_file, char *output_file);

    /**
     * @param input_file encoded file with the previous mentioned huffman_table
     * @param output_file location where to decode the file
     */
    static void decode_huffman_in_file(char *input_file, char *output_file);

    /**
     * @param tree the huffman tree from where we create the huffman_table
     * @param bits the code for encoding each character
     */

    void create_huffman_table(bst_node *tree, int bits);

    /**
     * @brief Function that writes huffman_table in a file called "huffman_table"
     */
    void write_huffman_table_in_file();
};
