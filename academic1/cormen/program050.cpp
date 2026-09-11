/*
   exercise: 050
   page: 00
   description: full binary tree
   command: echo 11 6 8 3 10 18 2 4 12 15 13 9 | ./program050
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

struct Node {
    int key;
    Node *parent;
    Node *left;
    Node *right;
};

struct BinarySearchTree {
    Node *root;
};

void inorder_tree_walk(Node *x) {
    if (x != nullptr) {
        inorder_tree_walk(x->left);
        std::cout << x->key << " ";
        inorder_tree_walk(x->right);
    }
}

Node* tree_search(Node *x, int k) {
    if (x == nullptr || k == x->key) {
        return x;
    }
    if (k < x->key) {
        return tree_search(x->left, k);
    }
    return tree_search(x->right, k);
}

Node* iterative_tree_search(Node *x, int k) {
    while (x != nullptr && k != x->key) {
        if (k < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    return x;
}

Node* tree_minimum(Node *x) {
    while(x->left != nullptr) {
        x = x->left;
    }
    return x;
}

Node* tree_maximum(Node *x) {
    while(x->right != nullptr) {
        x = x->right;
    }
    return x;
}

Node* tree_successor(Node *x) {
    if (x->right != nullptr) {
        return tree_minimum(x->right);
    }
    Node *y = x->parent;
    while(y != nullptr && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

Node* tree_predecessor(Node *x) {
    if (x->left != nullptr) {
        return tree_maximum(x->left);
    }
    Node *y = x->parent;
    while(y != nullptr && x == y->left) {
        x = y;
        y = y->parent;
    }
    return y;
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here



    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

