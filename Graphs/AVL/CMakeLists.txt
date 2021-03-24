cmake_minimum_required(VERSION 3.16)
project(Lab3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,1000000000")

add_executable(Lab3 AVLTree.cpp)