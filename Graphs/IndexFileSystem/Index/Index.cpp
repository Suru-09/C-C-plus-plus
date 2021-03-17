#include "Index.h"

IndexFile::IndexFile(string data_file_name) {

   data_file.open(data_file_name);
   if(!data_file.is_open()) {
       cout << "There was an error while opening the data file, program exits!";
       exit(1);
   }
}

void IndexFile::createIndex(int record_size, int key_size) {

}