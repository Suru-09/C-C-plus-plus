#include <iostream>
#include <vector>
#include<algorithm>
#include<ctime>

class Node {
public:

    int key;
    Node *left;
    Node *right;
    int height;

};

class AVLTree{

    private:
    Node *root;

    public:

    int getHeight(Node *node) {
            if(!node)
                return 0;
            return node->height;
    }
    Node* createNode(int key) {

    auto *node = new Node();
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;

    return node;
    }

    int updateNode(Node *node) {
        return std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    Node* rightRotate(Node *node) {

    Node *new_root = node->left; // new_root will change positions with node practically
    Node *old_right = new_root->right; //we need right of new_root because it will be on
                                      // the opposite part of the tree
    // perform the actual rotation
    new_root->right = node;
    node->left = old_right;

    //Let's update our height for the right subtree and left one
    node->height = updateNode(node);
    new_root->height = updateNode(node);

    return new_root;
    }

    Node* leftRotate(Node *node) {

    Node *new_root = node->right;
    Node *old_left = new_root->left;

    //Perform actual rotation

    new_root->left = node;
    node->right = old_left;

    //Again, update heights

    node->height = updateNode(node);
    new_root->height = updateNode(new_root);

    return new_root;
    }

    int balanceFactor(Node *node) {
         if(!node)
             return 0;
         return getHeight(node->left) - getHeight(node->right);
    }

    Node* insert(Node *node, int new_key) {

         //If the tree is empty insert the node
         if(!node)
             return createNode(new_key);

         //basically BST definition here
         if(new_key < node->key) {
             node->left = insert(node->left, new_key);
         }
         else if(new_key > node->key) {
             node->right = insert(node->right, new_key);
         }
         else
             return node;   //can't insert the same key twice

         //std::cout<< "Key: " << node->key <<" and height: " << node->height << "\n";

         //Update BF for each node
         node->height = updateNode(node);

         //Now we treat the 4 possible cases
         int BF = balanceFactor(node);

         //LEFT LEFT CASE
         if(BF > 1 && new_key < node->left->key )
             return rightRotate(node);

         //LEFT RIGHT CASE
         if(BF > 1 && new_key > node->left->key) {
             node->left = leftRotate(node->left);
             return rightRotate(node);
         }

         //RIGHT RIGHT CASE
         if(BF < -1 && new_key > node->right->key)
             return leftRotate(node);

         //RIGHT LEFT CASE
         if(BF < -1 && new_key < node->right->key ){
             node->right = rightRotate(node->right);
             return leftRotate(node);
         }

         return node;
     }

     void inOrder(Node *node) {

         if(node) {
             std::cout<<" " << node->key;
             inOrder(node->left);
             inOrder(node->right);
         }
    }

    Node* nodeBeforeGivenNode(Node *node) {

        Node *iterator = node;
        while(iterator->left)
            iterator = iterator->left;
        return iterator;
    }

    Node* deleteNode(Node* node, int key) {

        if(!node)
            return node;

        if(node->key > key)
            node->left = deleteNode(node->left, key);
        else if(node->key < key)
            node->right = deleteNode(node->right, key);
        else {  //we have 4 cases ( 1-1 1-0 0-1 0-0)

                //The case with both children( 1-1 )
                if(node->left && node->right) {
                    Node *temp = nodeBeforeGivenNode(node->right);
                    node->key = temp->key;
                    node->right = deleteNode(node->right, temp->key);
                }
                else {  //3 possible cases (1-0 0-1 or 0-0)
                    Node *aux = nullptr;
                    if(node->left)
                        aux = node->left;
                    else if(node->right)
                        aux = node->right;

                    //Case with 0-0 (no children)
                    if(aux == nullptr) {
                        aux = node;
                        node = nullptr; //We need to have null for right/left of the parent node
                    }
                    else {   //cases with 1-0 or 0-1 (only 1 child)
                        *node = *aux;
                    }

                    free(aux);
                }
        }


        if(!node)
            return node;

        //Update the heights for the rebalancing calculations
        node->height = updateNode(node);

        //Calculate the BalanceFactor( considered left - right)
        int BF = balanceFactor(node);

        // 2 Cases: Left Left and Left Right

        if(BF > 1) {
            if(balanceFactor(node->left) >= 0) {        //this is left left
                return rightRotate(node);
            }
            else {      //this is left right
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        }

        // 2 Cases: Right Right and Right Left

        if(BF < -1) {
            if(balanceFactor(node->right) <= 0) {   //Right Right case
                return leftRotate(node);
            }
            else {      //Right left case
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }

        return node;
    }

    Node* search(Node *node, int key) {

        if(!node || node->key == key ) {
            return node;
        }

        if(node->key < key)
            return search(node->right, key);

        return search(node->left, key);
    }
};


class Permutation {
private:
    int n;
public:
    [[nodiscard]] std::vector<int> generatePermutation(std::vector<int> arr) const {

        srand(time(NULL));

        for(int i = 0 ; i < n; ++i) {
            int index = rand() % n;

            int aux = arr[n - 1];
            arr[n - 1] = arr[index];
            arr[index] = aux;

            arr.push_back(arr[index]);
            arr.pop_back();

        }
        return arr;
    }

    Permutation(int i) {
        n = i;
    }
};

class bst_node {
public:
    int key;
    bst_node *left;
    bst_node *right;
};

class BST {
private:
    bst_node *node;
public:
    bst_node* create_node(int key) {
        bst_node *node{};
        node = new bst_node();
        node->key = key;
        node->left = nullptr;
        node->right = nullptr;

        return node;
    }

    bst_node * insert_node(bst_node *root, int key) {
        if(!root) {
            return create_node(key);
        }

        if(key > root->key )
            root->right = insert_node(root->right, key);
        else
            root->left = insert_node(root->left, key);

        return root;
    }

    int height(bst_node *node, int leftDepth, int rightDepth) {

        if(!node)
            return -1;

        leftDepth = height(node->left, leftDepth + 1, rightDepth);
        rightDepth = height(node->right, leftDepth, rightDepth + 1);

        return std::max(leftDepth, rightDepth) + 1;

    }

    void preOrder(bst_node *T) {

        if(!T)
            return;

        std::cout<<" " << T->key << " ";
        preOrder(T->left);
        preOrder(T->right);

    }
    bool testClones(bst_node *T1, bst_node *T2) {

        if(!T1 && !T2)
            return true;

        if(T1 && T2) {
            return (
                    T1->key == T2->key &&
                    testClones(T1->left, T2->left) &&
                    testClones(T1->right, T2->right)
                    );
        }

        return false;
    }

    bst_node* rightRotate(bst_node *node) {

        bst_node *new_root = node->left; // new_root will change positions with node practically
        bst_node *old_right = new_root->right; //we need right of new_root because it will be on
        // the opposite part of the tree
        // perform the actual rotation
        new_root->right = node;
        node->left = old_right;

        return new_root;
    }

    bst_node* leftRotate(bst_node *node) {

        bst_node *new_root = node->right;
        bst_node *old_left = new_root->left;

        //Perform actual rotation

        new_root->left = node;
        node->right = old_left;

        return new_root;
    }

    bst_node* search(bst_node *root, int key) {

        if(!root || root->key == key ) {
            return root;
        }

        if(root->key < key)
            return search(root->right, key);

        return search(root->left, key);
    }


    bst_node* transformTree(bst_node *T1, bst_node *T2) {

        if(!T1 || !T2)
            return T1;

        if(testClones(T1, T2))
            return T1;


        if(T1->key < T2->key) {
            T1 = leftRotate(T1);
            std::cout<<"The tree: ";
            preOrder(T1);
            std::cout<<"\n";
        }
        else if(T1->key > T2->key){
            T1 = rightRotate(T1);
            std::cout<<"The tree: ";
            preOrder(T1);
            std::cout<<"\n";
        }
        else {
            transformTree(T1->left, T2->left);
            transformTree(T1->right, T2->right);
        }

        return T1;
    }
};

void test_permutation() {

    bst_node *T1 = nullptr;
    bst_node *T2 = nullptr;

    std::vector<int> arr;
    for(int i = 0 ; i < 5; ++i)
        arr.push_back(i + 1);

    Permutation p1 = *new Permutation(5);
    Permutation p2 = *new Permutation(5);
    arr = p1.generatePermutation(arr);
    std::vector<int> arr2 = p2.generatePermutation(arr);

    BST bst_1{};
    BST bst_2{};

    for(int i = 0 ; i < arr.size(); ++i) {
        T1 = bst_1.insert_node(T1, arr[i]);
        T2 = bst_2.insert_node(T2, arr2[i]);
    }

    bst_1.preOrder(T1);
    std::cout << "\n";
    bst_2.preOrder(T2);


    std::cout<< std::endl<< " Result of testClones: "
    << bst_1.testClones(T1, T2) << "\n";

    bst_1.transformTree(T1, T2);
    bst_1.preOrder(T1);
    std::cout << "\n";
    bst_2.preOrder(T2);
}

#define test_nr 1000000

void test_AVL() {

    Node *root_AVL = nullptr;
    bst_node *root_BST = nullptr;

    AVLTree avl{};
    BST bst{};


    time_t starting_time = time(nullptr);
    for(int i = 0 ; i < test_nr; ++i )
        root_AVL = avl.insert(root_AVL, i);
    time_t ending_time = time(nullptr);

    std::cout << " Time for AVL: " << ending_time - starting_time << "\n";
    std::cout << " Height for AVL: " << avl.getHeight(root_AVL) << "\n";

    starting_time = time(nullptr);
    for(int i = 0 ; i < test_nr; ++i)
        root_BST = bst.insert_node(root_BST, i);
    ending_time = time(nullptr);

    std::cout << " Time for BST: " << ending_time - starting_time << "\n";
    std::cout << " Height for BST:: " << bst.height(root_BST, 0, 0);

}
int main() {

    //test_permutation();
    test_AVL();
    return 0;
}
