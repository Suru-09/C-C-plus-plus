#ifndef INDEXFILESYSTEM_INDEX_H
#define INDEXFILESYSTEM_INDEX_H

#endif

using namespace std;

#include<iostream>
#include<fstream>

class IndexFile {
private:
    FILE* data_file;
    int current_offset;
    char* file_name;

public:
    IndexFile(char* fileName);
    void createIndex(int record_size, int key_size);
};
