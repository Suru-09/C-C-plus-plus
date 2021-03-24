#include <iostream>
#include<cstring>
#include "HUFFMAN_Class/Huffman.h"


int main(int argc, char *argv[]) {

    //Mode can be either -c (compression) or -d (decompression)
    if(argc != 4) {
        printf("Usage: ./%s mode file_input file_output", argv[0]);
        exit(1);
    }

    if( strcmp(argv[1], "-c") && strcmp(argv[1], "-d") ) {

        cout << "The mode entered is neither -c (for compression) neither -d (for decompression) !";
        exit(1);
    }

    if(!strcmp(argv[1], "-c")) {
        Huffman tool(argv[2]);
        tool.encode_huffman_in_file(argv[2], argv[3]);
    }

    //!!!! ------- CAREFUL ------- !!!!!! //

    //The function works fine, but we need the huffman_table as a parameter
    //so I am using the huffman generated for the compression instead of hardcoding
    //one in main, that's why I have the the char file[] = "input.txt" hardcoded

    char file[] = "input.txt";

    //This works only if we change argv[2] to the old input file in the constructor
    //because the constructor generates the huffman_table which we need for
    //decompression
    //otherwise we could save it somewhere and then just call the function

    unordered_map< char, pair<int, int> > huffman_table;

    if(!strcmp(argv[1], "-d")) {
        //Huffman tool(argv[2]);
        Huffman tool(file);

        /*
        if we use argv[2] it wouldn't work because the constructor
        would generate the huffman_table for the encoded text
        which would only result in gibberish therefore we need
        the plain_text file to generate the huffman_table
        */

        huffman_table = tool.get_huffman_table();
        tool.decode_huffman_in_file(huffman_table, argv[2], argv[3]);
    }


    return 0;
}
