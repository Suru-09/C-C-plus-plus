#include "Index.h"
#include "../BTree/BTree.h"
#include<fstream>
#include<cstring>

void file_error_handler(FILE *fp) {

    //Checking whether the file opened correctly or not
    if(!fp) {
        cout << "There was an error while opening the data file, program exits!";
        exit(1);
    }
}
IndexFile::IndexFile(char* fileName) {

   strcpy(file_name, fileName);
   current_offset = 0;
}

void IndexFile::createIndex(int record_size, int key_size) {

    data_file = fopen(file_name, "rb");
    file_error_handler(data_file);

    //creating a BTree
    BTree tree(2, key_size);

    uint64_t key = 0;

    //creating a BTree which has all the index file data
    while( fread(&key, key_size, 1, data_file) ) {

        if(feof(data_file)) {
            cout << "Got to the end of file!\n";
            break;
        }
        //cout << key << " " << endl;

        tree.insert(key, data_file);
        //Searching the current position in the file
        fseek(data_file, record_size, SEEK_CUR);

        current_offset += record_size;
    }

    tree.traverse();
    fclose(data_file);
}