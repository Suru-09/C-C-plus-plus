# Compression Tool
# Using huffman tree method

### Structure of the program:

* BST_Class - has the *binary search tree* definition
        
        In header we have: 
        
      
        struct bst_node {
            char c;
            int freq;
            
            bool is_leaf;
            struct bst_node *left, *right;
        };
        
        which represents the structure of the Huffman tree node
        
        Whereas, in .cpp we have the allocation of a new node:
        
        bst_node* create_node(char c, int freq) {
            bst_node *node{};
            node = new bst_node();
        
            node->c = c;
            node->freq = freq;
        
            c != 'N' ? node->is_leaf = true : node->is_leaf = false;
        
            node->left = nullptr;
            node->right = nullptr;
        
            return node;
        }
        
* HUFFMAN_Class - has all the functions for compression

        The class for huffman has the following structure:
        
        class Huffman {

        private:
            bst_node *root;
            unordered_map<char, pair<int, int> > huffman_table{};
        public:
            explicit Huffman(char *file_name);
            bst_node * build_huffman_tree(entry arr[]);
            void encode_huffman_in_file(char *input_file, char *output_file);
            void decode_huffman_in_file(const unordered_map<char, pair <int, int> >& huffmanTable, char *input_file, char *output_file);
            void create_huffman_table(bst_node *tree, int bits);
            unordered_map<char, pair<int, int> > get_huffman_table();
        };
