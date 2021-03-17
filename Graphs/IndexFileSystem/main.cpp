#include <iostream>
#include "BTree/BTree.h"

int main() {

    FILE * fp = fopen("test.txt", "r");
    fseek(fp, 79, SEEK_SET);
    BTree tree(2, 1);
    tree.insert(48, fp);
    tree.insert(52, fp);
    tree.insert(53, fp);

    tree.traverse();
    return 0;
}
