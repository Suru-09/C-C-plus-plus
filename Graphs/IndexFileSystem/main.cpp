#include <iostream>
#include "BTree/BTree.h"
#include "Index/Index.h"


int main() {

//    IndexFile index_file("test.txt");
//    index_file.createIndex(32, 1);

      IndexFile index_file("medium_test.txt");
      index_file.createIndex(84, 4);

//      IndexFile index_file("large.dat");
//      index_file.createIndex(84, 4);

    return 0;
}
