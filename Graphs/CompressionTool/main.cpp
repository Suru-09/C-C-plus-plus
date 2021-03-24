#include <iostream>
#include "HUFFMAN_Class/Huffman.h"


int main(int argc, char *argv[]) {

    //Mode can be either -c (compression) or -d (decompression)
//    if(argc != 4) {
//        printf("Usage: ./%s mode file_input file_output", argv[0]);
//    }

    Huffman obj("sth.txt");
    obj.encode_huffman_in_file("sth.txt", "output.txt");

    obj.decode_huffman_in_file(obj.get_huffman_table(), "output.txt", "decoded.txt");

    return 0;
}
