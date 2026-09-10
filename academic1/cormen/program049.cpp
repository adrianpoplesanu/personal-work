/*
   exercise: 049
   page: 288
   description: inorder-tree-walk
   command: ./program049
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

Node *make_node(int key) {
    Node *x = new Node();
    x->key = key;
    x->parent = nullptr;
    x->left = nullptr;
    x->right = nullptr;
    return x;
}

void link_left(Node *parent, Node *child) {
    parent->left = child;
    if (child != nullptr) {
        child->parent = parent;
    }
}

void link_right(Node *parent, Node *child) {
    parent->right = child;
    if (child != nullptr) {
        child->parent = parent;
    }
}

void inorder_tree_walk(Node *x) {
    if (x != nullptr) {
        inorder_tree_walk(x->left);
        std::cout << x->key << " ";
        inorder_tree_walk(x->right);
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    // CLRS Figure 12.1-style BST:
    //           15
    //         /    \
    //        6      18
    //       / \    /  \
    //      3   7  17  20
    //     / \   \
    //    2   4  13
    //          /
    //         9

    Node *n15 = make_node(15);
    Node *n6 = make_node(6);
    Node *n18 = make_node(18);
    Node *n3 = make_node(3);
    Node *n7 = make_node(7);
    Node *n17 = make_node(17);
    Node *n20 = make_node(20);
    Node *n2 = make_node(2);
    Node *n4 = make_node(4);
    Node *n13 = make_node(13);
    Node *n9 = make_node(9);

    link_left(n15, n6);
    link_right(n15, n18);
    link_left(n6, n3);
    link_right(n6, n7);
    link_left(n18, n17);
    link_right(n18, n20);
    link_left(n3, n2);
    link_right(n3, n4);
    link_right(n7, n13);
    link_left(n13, n9);

    Node *root = n15;

    std::cout << "[ INORDER ] ";
    inorder_tree_walk(root);
    std::cout << "\n";

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}
