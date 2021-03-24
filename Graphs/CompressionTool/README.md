#Compression Tool
#Using huffman tree method

### Structure of the program:

* BST_Class - has the *binary search tree* definition

        In header we have: 
        
        ```c++
        struct bst_node {
            char c;
            int freq;
            
            bool is_leaf;
            struct bst_node *left, *right;
        };
        ``` 
        
        which represents the structure of the Huffman tree node
        
        Whereas, in .cpp we have the allocation of a new node:
        
        ```c++
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
        ```
* HUFFMAN_Class - has all the functions for compression        