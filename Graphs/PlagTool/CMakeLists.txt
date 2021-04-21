cmake_minimum_required(VERSION 3.17)
project(PlagTool)

set(CMAKE_CXX_STANDARD 20)

add_executable(PlagTool main.cpp LCS.cpp LCS.h)