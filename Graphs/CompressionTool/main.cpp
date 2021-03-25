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


    //Compression case
    if(!strcmp(argv[1], "-c")) {
        Huffman tool(argv[2]);
        tool.encode_huffman_in_file(argv[2], argv[3]);
        cout << "The file with name: " << argv[2] <<
        " has been compressed in the file with name: " << argv[3] << "\n";
    }

    //Decompression case
    if(!strcmp(argv[1], "-d")) {
        char str[] = "huffman_table";
        Huffman::decode_huffman_in_file(argv[2], argv[3]);\
        cout << "The file with name: " << argv[2] <<
        " has been decompressed in the file with name : " << argv[3] << "\n";
    }


    
    return 0;
}
