/*
   exercise: 080
   page: 492
   description: b-tree search
   command: ./program080
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

struct Node {
    int n;
    int *keys;
    Node **children;
    bool is_leaf;
};

struct BTree {
    Node *root;
    int t;
};

struct SearchResult {
    Node *node;
    int i;
};

SearchResult b_tree_search(Node *x, int k) {
    int i = 0;
    while (i < x->n && k > x->keys[i]) {
        i++;
    }
    if (i < x->n && k == x->keys[i]) {
        return {x, i};
    }
    if (x->is_leaf) {
        return {NULL, -1};
    }
    return b_tree_search(x->children[i], k);
}

Node *allocate_node(int t, bool leaf) {
    Node *x = new Node();
    x->n = 0;
    x->is_leaf = leaf;
    x->keys = new int[2 * t - 1];
    x->children = new Node *[2 * t];
    for (int i = 0; i < 2 * t; i++) {
        x->children[i] = nullptr;
    }
    return x;
}

BTree b_tree_create(int t) {
    BTree btree;
    Node *x = allocate_node(t, true);
    x->n = 0;
    btree.root = x;
    btree.t = t;
    return btree;
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

