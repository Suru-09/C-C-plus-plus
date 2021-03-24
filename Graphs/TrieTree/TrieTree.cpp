//
// Created by Dragos Surugiu on 3/15/2021.
//

#include<stack>
#include "TrieTree.h"
#include<iostream>

using namespace std;

TrieTree::TrieTree() {

    root = new TrieNode();
    for(auto & i : root->children)
        i = nullptr;

    root->isEnd = false;
}

void TrieTree::insert(string word) {

    TrieNode *iterator = root;
    for(char i : word) {

        int occurence = i - 'a';
        if(iterator->children[occurence] == nullptr) {

            TrieNode *new_node = new TrieNode();
            new_node->isEnd = false;

            for(auto & j : new_node->children)
                j = nullptr;

            iterator->children[occurence] = new_node;
        }

        iterator = iterator->children[occurence];
    }

    iterator->isEnd = true;
}

void PrintStack(stack<char> s)
{
    if (s.empty())
        return;

    char x = s.top();
    s.pop();
    PrintStack(s);
    cout << x;
    s.push(x);

}
void TrieTree::print(TrieNode *tree, stack<char> s) {

     if( tree->isEnd) {
         PrintStack(s);
         cout << endl;
     }

     for(int i = 0 ; i < size_of_alphabet; ++i) {

         if(tree->children[i]) {
             s.push(i + 'a');
             print(tree->children[i], s);
             s.pop();
         }
     }
}