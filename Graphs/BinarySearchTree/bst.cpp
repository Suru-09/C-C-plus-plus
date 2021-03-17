#include <iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

struct bst_node {
    int key;
    struct bst_node *left, *right;
};

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

void in_order(bst_node *root) {
    if(!root)
        return;

    in_order(root->left);
    std::cout<< root->key << std::endl;
    in_order(root->right);
}

void pre_order(bst_node *root) {

    if(!root)
        return;

    std::cout<< root->key << std::endl;
    pre_order(root->left);
    pre_order(root->right);
}

int height(bst_node *root, int leftDepth, int rightDepth) {

    if(!root)
        return -1;

    leftDepth = height(root->left, leftDepth + 1, rightDepth);
    rightDepth = height(root->right, leftDepth, rightDepth + 1);

    return std::max(leftDepth, rightDepth) + 1;

}
bst_node * bst_to_test() {
    bst_node *root = nullptr;
    std::vector<int> arr;

    arr.push_back(8);
    arr.push_back(2);
    arr.push_back(1);
    arr.push_back(15);
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(5);
    arr.push_back(7);
    arr.push_back(4);
    arr.push_back(3);
    arr.push_back(18);
    arr.push_back(22);

    for(int i : arr)
        root = insert_node(root, i);

    return root;
}

bst_node* search(bst_node *root, int key) {

    if(!root || root->key == key ) {
        return root;
    }

    if(root->key < key)
        return search(root->right, key);

    return search(root->left, key);
}

bst_node* successor(bst_node *root, int key) {

    if( !root ||  ( (root->left) && root->left->key == key)
        || ( (root->right) && root->right->key == key ) ){
        return root;
    }

    if(root->key < key)
        return successor(root->right, key);

    return successor(root->left, key);
}

bool isPerfectlyBalancedBST(bst_node* root, int nr_of_nodes) {

    if(!root )
        return true;

    return isPerfectlyBalancedBST(root->left, nr_of_nodes) && isPerfectlyBalancedBST(root->right, nr_of_nodes)
           && abs(height(root->left, 0, 0) - height(root->right, 0, 0)) <= 1;
}

int search_closest(bst_node *root, int value, int searched) {

    if(!root) {
        return searched;
    }

    if(root->key < value)
        return search_closest(root->right, value, root->key);

    return search_closest(root->left, value, searched);
}

void createVectorFromBST(bst_node *root, std::vector<int> &arr) {

    if(!root)
        return;

    createVectorFromBST(root->left, arr);
    arr.push_back(root->key);
    createVectorFromBST(root->right, arr);
}

bool checkExistsTwoNodesWithSum(int sum, std::vector<int> arr) {

    int j = 0, k = arr.size() - 1;

    while(j < k) {
        if(arr[j] + arr[k] == sum) {
            return true;
        }
        else if(arr[j] + arr[k] < sum) {
            j++;
        }
        else
            k--;
    }
    return false;
}

//uncomment which test you would like to see

void createPathFromRootToNode(bst_node *root, int key_node, std::vector<int> &arr) {

    if(!root) {
        return;
    }
    arr.push_back(root->key);

    if(key_node == root->key)
        return;

    if(key_node < root->key)
        createPathFromRootToNode(root->left, key_node, arr);
    else
        createPathFromRootToNode(root->right, key_node, arr);
}

void printPathFromTo(bst_node *root, int key_first_node, int key_second_node) {

    if( !search(root, key_first_node) || !search(root, key_second_node) ) {
        std::cout<<" One of the nodes doesn't exists in the tree";
        return;
    }

    std::vector<int> path_to_first, path_to_second;
    createPathFromRootToNode(root, key_first_node, path_to_first);
    createPathFromRootToNode(root, key_second_node, path_to_second);

//    std::cout<< "First road from node " << key_first_node <<": \n";
//    for(auto x: path_to_first)
//        std::cout<< " " << x << " ";
//
//    std::cout<< "\nSecond road from node " << key_second_node <<": \n";
//    for(auto x: path_to_second)
//        std::cout<< " " << x << " ";
//    std::cout<<"\n";

    int i = 0;
    while(i < path_to_first.size() - 1) {
        if(path_to_first[i] == path_to_second[i] && path_to_first[i + 1] == path_to_second[i + 1]){
            path_to_first.erase(path_to_first.begin());
            path_to_second.erase(path_to_second.begin());
            --i;
        }
        else if(path_to_first[i] == path_to_second[i] && path_to_first[i + 1] != path_to_second[i + 1]) {
            path_to_second.erase(path_to_second.begin());
            break;
        }
        ++i;
    }

    reverse(path_to_first.begin(), path_to_first.end());

    for(auto x: path_to_second)
        path_to_first.push_back(x);

    for(auto x: path_to_first)
        std::cout<< " " << x << " ";

}

void getPathForSum(bst_node *root, int sum,int current_sum, std::vector<int> &arr) {

    //std::cout<<" Current Sum is: " << current_sum << "\n";

    if(current_sum == sum) {
        for(auto x: arr)
            std::cout<< " " << x << " ";
        std::cout<< "\n";
        return;
    }

    if(root && root->key + current_sum <= sum){
        arr.push_back(root->key);

        getPathForSum(root->left, sum, current_sum + root->key, arr);
        getPathForSum(root->right, sum , current_sum + root->key, arr);

        arr.pop_back();
    }
}

void printLevels(bst_node *root) {

    queue<pair <bst_node*, int> > Q;
    Q.push(make_pair(root ,0));
    int old_level = 0;

    while(!Q.empty()) {

        pair<bst_node*, int > current = Q.front();
        Q.pop();

        if(current.first->left)
            Q.push(make_pair(current.first->left, current.second + 1) );

        if(current.first->right)
            Q.push(make_pair(current.first->right, current.second + 1));

        if(old_level < current.second)
            std::cout<<"\n";

        std::cout<< " " <<  current.first->key << " ";
        old_level = current.second;
    }
}

bst_node* balancedBSTFromSortedArray(std::vector<int> &arr) {

    bst_node* root = nullptr;

    sort(arr.begin(), arr.end());
    int mid = arr.size() / 2;
    root = insert_node(root, arr[mid]);

    int i = mid - 1, j = mid + 1;
    while(i >= 0 || j < arr.size()) {

        if(i >= 0) {
            root = insert_node(root, arr[i]);
            --i;
        }

        if(j < arr.size()) {
            root = insert_node(root, arr[j]);
            ++j;
        }
    }

    if(isPerfectlyBalancedBST(root, 10) )
        return root;
    else
        return nullptr;
}

bool isPostOrderArray(const std::vector<int> &arr) {

    int i = 0;
    while(i < arr.size() - 2) {
        if(arr[i] > arr[i + 2] || arr[i + 1] < arr[i + 2])
            return false;
        i += 2;
    }

    return true;
}
void tests() {

    bst_node *root = bst_to_test();

    std::cout<< "In order traversal: " << std::endl;
    in_order(root);
    std::cout<<std::endl << std::endl;

    std::cout<< "Pre order traversal: "<< std::endl;
    pre_order(root);
    std::cout<<std::endl << std::endl;

    std::vector<int> arr;
    std::cout<< "Check if two Nodes have sum 12: ";
    createVectorFromBST(root, arr);
    std::cout<< std::endl <<  checkExistsTwoNodesWithSum(12, arr);
    std::cout<<std::endl << std::endl;


    std::cout<<"Check height of the tree: ";
    std::cout<< height(root, 0, 0) << std::endl;
    std::cout<<std::endl << std::endl;

    std::cout<<"Search a root in the tree: ";
    if(search(root, 15) != nullptr)
        std::cout<< search(root, 15)->key;
    std::cout<<std::endl << std::endl;

    std::cout<<"Search closest root to the given root: ";
    std::cout<< search(root, 15)->key;
    std::cout<<std::endl << std::endl;

    std::cout<<"Is the tree perfectly balanced?(0 NO , 1 YES) : ";
    std::cout << isPerfectlyBalancedBST(root, 10);
    std::cout<<std::endl << std::endl;


    std::cout<<"The path from node1 to node2: " << std::endl;
    printPathFromTo(root, 7,  10);
    std::cout<<std::endl << std::endl;

    std::cout<<"Print path with sum: " << std::endl;
    std::vector<int> testeaza;
    getPathForSum(root, 22, 0, testeaza);
    std::cout<<std::endl << std::endl;

    std::cout<<" Print levels :\n";
    printLevels(root);
    std::cout<<std::endl << std::endl;

    std::cout<<" Create the balanced tree from sorted array: \n";
    std::vector<int> arr1;
    arr1.push_back(1);
    arr1.push_back(2);
    arr1.push_back(3);
    arr1.push_back(4);
    bst_node *test = balancedBSTFromSortedArray(arr1);
    if(test)
        in_order(test);
    std::cout<<std::endl << std::endl;

    std::cout<<" Can I create a BST from the given arrays : ?(the examples) : \n";
    std::vector<int> false_arr, true_arr;
    false_arr.push_back(1);
    false_arr.push_back(15);
    false_arr.push_back(2);
    false_arr.push_back(5);
    false_arr.push_back(8);

    true_arr.push_back(1);
    true_arr.push_back(5);
    true_arr.push_back(2);
    true_arr.push_back(15);
    true_arr.push_back(8);
    std::cout<< "\nFalse array: " << isPostOrderArray(false_arr);
    std::cout<< "\nTrue aray: " << isPostOrderArray(true_arr);

}
int main() {

    tests();

    return 0;
}
