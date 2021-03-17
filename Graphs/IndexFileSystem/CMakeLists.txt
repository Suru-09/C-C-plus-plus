cmake_minimum_required(VERSION 3.16)
project(IndexFileSystem)

set(CMAKE_CXX_STANDARD 20)

add_executable(IndexFileSystem main.cpp BTree/BTree.cpp BTree/BTree.h Index/Index.cpp Index/Index.h)