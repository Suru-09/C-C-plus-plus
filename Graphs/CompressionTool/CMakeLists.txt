cmake_minimum_required(VERSION 3.16)
project(CompressionTool)

set(CMAKE_CXX_STANDARD 20)

add_executable(CompressionTool main.cpp HUFFMAN_Class/Huffman.cpp HUFFMAN_Class/Huffman.h BST_Class/BST.cpp BST_Class/BST.h)