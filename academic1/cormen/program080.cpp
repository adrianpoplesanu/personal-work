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

void b_tree_split_child(BTree &tree, Node *x, int i) {
    int t = tree.t;
    Node *y = x->children[i];
    Node *z = allocate_node(t, y->is_leaf);
    z->n = t - 1;
    for (int j = 0; j < t - 1; j++) {
        z->keys[j] = y->keys[j + t];
    }
    if (!y->is_leaf) {
        for (int j = 0; j < t; j++) {
            z->children[j] = y->children[j + t];
        }
    }
    y->n = t - 1;
    for (int j = x->n; j >= i + 1; j--) {
        x->children[j + 1] = x->children[j];
    }
    x->children[i + 1] = z;
    for (int j = x->n - 1; j >= i; j--) {
        x->keys[j + 1] = x->keys[j];
    }
    x->keys[i] = y->keys[t - 1];
    x->n = x->n + 1;
}

void b_tree_insert_nonfull(BTree &tree, Node *x, int k) {
    int i = x->n - 1;
    if (x->is_leaf) {
        while (i >= 0 && k < x->keys[i]) {
            x->keys[i + 1] = x->keys[i];
            i = i - 1;
        }
        x->keys[i + 1] = k;
        x->n = x->n + 1;
    } else {
        while (i >= 0 && k < x->keys[i]) {
            i = i - 1;
        }
        i = i + 1;
        if (x->children[i]->n == 2 * tree.t - 1) {
            b_tree_split_child(tree, x, i);
            if (k > x->keys[i]) {
                i = i + 1;
            }
        }
        b_tree_insert_nonfull(tree, x->children[i], k);
    }
}

void b_tree_insert(BTree &tree, int k) {
    Node *r = tree.root;
    if (r->n == 2 * tree.t - 1) {
        Node *s = allocate_node(tree.t, false);
        tree.root = s;
        s->n = 0;
        s->children[0] = r;
        b_tree_split_child(tree, s, 0);
        b_tree_insert_nonfull(tree, s, k);
    } else {
        b_tree_insert_nonfull(tree, r, k);
    }
}

void free_node(Node *x) {
    delete[] x->keys;
    delete[] x->children;
    delete x;
}

void delete_key_from_leaf(Node *x, int i) {
    for (int j = i; j < x->n - 1; j++) {
        x->keys[j] = x->keys[j + 1];
    }
    x->n = x->n - 1;
}

int subtree_predecessor(Node *x) {
    while (!x->is_leaf) {
        x = x->children[x->n];
    }
    return x->keys[x->n - 1];
}

int subtree_successor(Node *x) {
    while (!x->is_leaf) {
        x = x->children[0];
    }
    return x->keys[0];
}

void merge_children(Node *x, int i) {
    Node *y = x->children[i];
    Node *z = x->children[i + 1];
    int y_n = y->n;
    y->keys[y_n] = x->keys[i];
    for (int j = 0; j < z->n; j++) {
        y->keys[y_n + 1 + j] = z->keys[j];
    }
    if (!y->is_leaf) {
        for (int j = 0; j <= z->n; j++) {
            y->children[y_n + 1 + j] = z->children[j];
        }
    }
    y->n = y_n + 1 + z->n;
    for (int j = i; j < x->n - 1; j++) {
        x->keys[j] = x->keys[j + 1];
    }
    for (int j = i + 1; j < x->n; j++) {
        x->children[j] = x->children[j + 1];
    }
    x->n = x->n - 1;
    free_node(z);
}

void borrow_from_previous(Node *x, int i) {
    Node *y = x->children[i];
    Node *z = x->children[i - 1];
    for (int j = y->n - 1; j >= 0; j--) {
        y->keys[j + 1] = y->keys[j];
    }
    if (!y->is_leaf) {
        for (int j = y->n; j >= 0; j--) {
            y->children[j + 1] = y->children[j];
        }
    }
    y->keys[0] = x->keys[i - 1];
    if (!y->is_leaf) {
        y->children[0] = z->children[z->n];
    }
    x->keys[i - 1] = z->keys[z->n - 1];
    y->n = y->n + 1;
    z->n = z->n - 1;
}

void borrow_from_next(Node *x, int i) {
    Node *y = x->children[i];
    Node *z = x->children[i + 1];
    y->keys[y->n] = x->keys[i];
    if (!y->is_leaf) {
        y->children[y->n + 1] = z->children[0];
    }
    x->keys[i] = z->keys[0];
    for (int j = 0; j < z->n - 1; j++) {
        z->keys[j] = z->keys[j + 1];
    }
    if (!z->is_leaf) {
        for (int j = 0; j < z->n; j++) {
            z->children[j] = z->children[j + 1];
        }
    }
    y->n = y->n + 1;
    z->n = z->n - 1;
}

void ensure_child(BTree &tree, Node *x, int i) {
    int t = tree.t;
    if (i != 0 && x->children[i - 1]->n >= t) {
        borrow_from_previous(x, i);
    } else if (i != x->n && x->children[i + 1]->n >= t) {
        borrow_from_next(x, i);
    } else if (i != x->n) {
        merge_children(x, i);
    } else {
        merge_children(x, i - 1);
    }
}

void b_tree_delete_from(BTree &tree, Node *x, int k);

void delete_key_from_internal(BTree &tree, Node *x, int i) {
    int t = tree.t;
    int k = x->keys[i];
    Node *y = x->children[i];
    Node *z = x->children[i + 1];
    if (y->n >= t) {
        int predecessor = subtree_predecessor(y);
        x->keys[i] = predecessor;
        b_tree_delete_from(tree, y, predecessor);
    } else if (z->n >= t) {
        int successor = subtree_successor(z);
        x->keys[i] = successor;
        b_tree_delete_from(tree, z, successor);
    } else {
        merge_children(x, i);
        b_tree_delete_from(tree, y, k);
    }
}

void b_tree_delete_from(BTree &tree, Node *x, int k) {
    int t = tree.t;
    int i = 0;
    while (i < x->n && k > x->keys[i]) {
        i++;
    }
    if (i < x->n && x->keys[i] == k) {
        if (x->is_leaf) {
            delete_key_from_leaf(x, i);
        } else {
            delete_key_from_internal(tree, x, i);
        }
        return;
    }
    if (x->is_leaf) {
        return;
    }
    bool last_child = (i == x->n);
    if (x->children[i]->n == t - 1) {
        ensure_child(tree, x, i);
    }
    if (last_child && i > x->n) {
        b_tree_delete_from(tree, x->children[i - 1], k);
    } else {
        b_tree_delete_from(tree, x->children[i], k);
    }
}

void b_tree_delete(BTree &tree, int k) {
    b_tree_delete_from(tree, tree.root, k);
    if (tree.root->n == 0 && !tree.root->is_leaf) {
        Node *old_root = tree.root;
        tree.root = tree.root->children[0];
        free_node(old_root);
    }
}

void b_tree_print(BTree &tree) {
    Node *x = tree.root;
    while (x != nullptr) {
        for (int i = 0; i < x->n; i++) {
            std::cout << x->keys[i] << " ";
        }
        std::cout << std::endl;
        x = x->children[0];
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    BTree tree = b_tree_create(3);
    b_tree_insert(tree, 10);
    b_tree_insert(tree, 20);
    b_tree_insert(tree, 30);
    b_tree_insert(tree, 40);
    b_tree_insert(tree, 50);
    b_tree_insert(tree, 60);
    b_tree_insert(tree, 70);
    b_tree_insert(tree, 80);
    b_tree_insert(tree, 90);
    b_tree_insert(tree, 100);
    b_tree_insert(tree, 110);
    b_tree_insert(tree, 120);
    b_tree_insert(tree, 130);
    b_tree_insert(tree, 140);
    b_tree_insert(tree, 150);
    b_tree_insert(tree, 160);

    b_tree_delete(tree, 10);
    b_tree_delete(tree, 20);
    b_tree_delete(tree, 30);
    b_tree_delete(tree, 40);
    b_tree_delete(tree, 50);
    b_tree_delete(tree, 60);
    b_tree_delete(tree, 70);
    b_tree_delete(tree, 80);
    b_tree_delete(tree, 90);

    b_tree_print(tree);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

