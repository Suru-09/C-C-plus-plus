#include <iostream>
#include "BTree.h"
#include "TrieTree.h"
#include<stack>

using namespace std;

int main() {


    TrieTree tree;
    tree.insert("all");
    tree.insert("alternate");
    tree.insert("alternative");
    tree.insert("are");
    tree.insert("arc");
    tree.insert("archbishop");
    tree.insert("bear");
    tree.insert("beard");
    tree.insert("bee");
    tree.insert("hear");
    tree.insert("horse");
    tree.insert("horseshoe");

    stack<char> s;
    tree.print( tree.root, s);

    return 0;
}
