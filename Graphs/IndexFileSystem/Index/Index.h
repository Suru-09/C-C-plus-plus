#ifndef INDEXFILESYSTEM_INDEX_H
#define INDEXFILESYSTEM_INDEX_H

#endif

using namespace std;

#include<iostream>
#include<fstream>

class IndexFile {
private:
    ifstream data_file;
public:
    IndexFile(string data_file_name);
    void createIndex(int record_size, int key_size);
};
