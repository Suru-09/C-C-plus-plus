//
// Created by Dragos Surugiu on 3/15/2021.
//

#ifndef LAB4_TRIETREE_H
#define LAB4_TRIETREE_H

#endif //LAB4_TRIETREE_H

#include<string>
#include<stack>

using namespace std;

static const int size_of_alphabet = 28;

class TrieNode {

    TrieNode *children[size_of_alphabet];
    bool isEnd;

    friend class TrieTree;
};

class TrieTree {

public:
    TrieNode *root;
public:
    void insert(string word);
    void print( TrieNode *tree, stack<char> s);
    TrieTree();

};
