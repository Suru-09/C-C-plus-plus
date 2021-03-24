#include <bitset>
#include "Huffman.h"

#define BLOCK_SIZE 512

struct Comparator {
    bool operator()(const bst_node *b1, const bst_node *b2) {
        return b1->freq > b2->freq;
    }
};


void Huffman::write_huffman_table_in_file() {

    string s = "huffman_table";

    ofstream f(s);
    if(f.is_open()) {
        for(auto it: huffman_table) {
            f << it.first;
            f << ";";
            f << it.second.first;
            f<< ";";
            f << it.second.second;
            f << "\n";
        }
    }
    f.close();
}

Huffman::Huffman(char *file_name) {

    ifstream file(file_name);
    vector<char> buffer(BLOCK_SIZE , 0);

    entry arr[256]{};

    if(file.is_open()) {
        while(true) {

            file.read(&buffer[0], buffer.size() );

            for(char i : buffer) {

                if(!arr[i].c) {
                    arr[i].c = i;
                    arr[i].freq++;
                }
                else {
                    arr[i].freq++;
                }
            }

            if(file.eof())
                break;

        }
    }
    else {
        cout << " There was an an error while opening the file! (Huffman constructor) ";
        exit(1);
    }

    file.close();
    root = build_huffman_tree(arr);
    create_huffman_table(root, 0);

    write_huffman_table_in_file();
}

bst_node * Huffman::build_huffman_tree(entry arr[]) {

    priority_queue<bst_node *, vector<bst_node *>, Comparator > min_Q{};

    for(int i = 0 ; i < 255; ++i) {
        if(arr[i].c != 0) {
            bst_node *new_node = create_node(arr[i].c, arr[i].freq);
            min_Q.push(new_node);
        }
    }

    while(min_Q.size() != 1 ) {
        for(int i = 0 ; i < min_Q.size(); ++i) {
            bst_node *x = min_Q.top();
            min_Q.pop();

            bst_node *y = min_Q.top();
            min_Q.pop();

            bst_node *new_node = create_node('N', x->freq + y->freq);
            new_node->left = x;
            new_node->right = y;

            min_Q.push(new_node);
        }
    }

    return min_Q.top();
}

void Huffman::encode_huffman_in_file(char *input_file, char *output_file) {

    ifstream input(input_file);
    ofstream output(output_file);

    vector<char> buffer (BLOCK_SIZE, 0);

    if(input.is_open() && output.is_open()) {
        while(true) {

            input.read(&buffer[0], buffer.size());
            for(auto &c : buffer) {

                auto got = huffman_table.find(c);
                if( got != huffman_table.end()) {

                    string aux{};
                    unsigned int nr = got->second.second;
                    for(int i = sizeof(int) ; i >= 0 ; --i) {
                        if( (nr >> i) & 1)
                            aux.append("1");
                        else if(!aux.empty())
                            aux.append("0");
                    }

                    if(aux.empty())
                        aux.append("0");

                    //cout << "Number : " << nr << " String: " << aux << "\n";
                    output << aux;
                }

            }
            if(input.eof())
                break;
        }
    }
    else {
        cout << "There was an error while opening the input file / output file(print_huffman function)!";
        exit(1);
    }


    input.close();
    output.close();
}

void Huffman::create_huffman_table(bst_node *tree, int bits) {

    if(!tree)
        return;

    if(tree->is_leaf)
        huffman_table.insert( make_pair(tree->c, make_pair(tree->freq, bits) ) );

    create_huffman_table(tree->left, bits * 2);
    create_huffman_table(tree->right, bits * 2 + 1);
}

void Huffman::decode_huffman_in_file(char *huffman_table_file, char *encoded_file, char *decoded_file) {

    ifstream huff_table(huffman_table_file);
    unordered_map< char , pair <int, int> > huffmanTable{};

    if(huff_table.is_open()) {

        char c;
        char del;
        int freq;
        int code;

        while(true) {
            huff_table >> c;
            huff_table >> del;
            huff_table >> freq;
            huff_table >> del;
            huff_table >> code;

            if(huff_table.eof())
                break;

            huffmanTable.insert(make_pair(c , make_pair(freq, code)));
        }

    }
    else {
            cout << "There was an error while opening the files!";
            exit(1);
    }

    huff_table.close();

    ifstream input(encoded_file);
    ofstream output(decoded_file);

    entry arr[256]{};
    int index = 0;

    for(auto i : huffmanTable) {
        arr[index].c = i.first;
        arr[index].freq = i.second.first;
        ++index;
    }

//    for(int i = 0 ; i < index; ++i)
//        cout << arr[i].c << "  " << arr[i].freq << "\n";

    bst_node *huffman_tree = Huffman::build_huffman_tree(arr);
    bst_node *iterator = huffman_tree;

    char character;

    if(input.is_open() && output.is_open()) {
        while(true) {

            input >> character;

            if(iterator->c != 'N') {
                output << iterator->c;
                iterator = huffman_tree;
            }

            if(character == '0')
                iterator = iterator->left;
            else if(character == '1')
                iterator = iterator->right;

            if(input.eof())
                break;
        }
    }
    else {
        cout << "There was an error while opening the files!";
        exit(1);
    }


    input.close();
    output.close();

}

unordered_map<char, pair<int, int> > Huffman::get_huffman_table() {
    return huffman_table;
}