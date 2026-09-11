/*
   exercise: 050
   page: 294
   description: full binary tree
   command: echo 11 6 8 3 10 18 2 4 12 15 13 9 | ./program050
*/

#include <iostream>
#include <chrono>
#include <queue>
#include <algorithm>
#include <string>

#define PRINT_EXECUTION_DURATION 0

struct Node {
    int key;
    Node *parent;
    Node *left;
    Node *right;

    Node() : key(0), parent(nullptr), left(nullptr), right(nullptr) {}
    Node(int key) : key(key), parent(nullptr), left(nullptr), right(nullptr) {}
    ~Node() {
        delete left;
        delete right;
    }
};

void inorder_tree_walk(Node *x) {
    if (x != nullptr) {
        inorder_tree_walk(x->left);
        std::cout << x->key << " ";
        inorder_tree_walk(x->right);
    }
}

int tree_height(Node *x) {
    if (x == nullptr) {
        return 0;
    }
    return 1 + std::max(tree_height(x->left), tree_height(x->right));
}

void normal_tree_walk(Node *x) {
    if (x == nullptr) {
        return;
    }
    const int cell = 3;
    int h = tree_height(x);
    std::queue<Node*> q;
    q.push(x);
    int level = 0;
    while (!q.empty()) {
        int level_size = q.size();
        bool has_next = false;
        int field = cell * (1 << (h - 1 - level));
        for (int i = 0; i < level_size; i++) {
            Node *u = q.front();
            q.pop();
            std::string s = (u == nullptr) ? "-" : std::to_string(u->key);
            int left = (field - (int)s.size()) / 2;
            if (left < 0) {
                left = 0;
            }
            int right = field - left - (int)s.size();
            if (right < 0) {
                right = 0;
            }
            std::cout << std::string(left, ' ') << s << std::string(right, ' ');
            if (u == nullptr) {
                q.push(nullptr);
                q.push(nullptr);
            } else {
                q.push(u->left);
                q.push(u->right);
                if (u->left != nullptr || u->right != nullptr) {
                    has_next = true;
                }
            }
        }
        std::cout << "\n";
        if (!has_next) {
            break;
        }
        level++;
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

void tree_insert(Node *&root, Node *z) {
    Node *y = nullptr;
    Node *x = root;
    while(x != nullptr) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == nullptr) {
        root = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    Node *root = nullptr;

    tree_insert(root, new Node(11));
    tree_insert(root, new Node(6));
    tree_insert(root, new Node(8));
    tree_insert(root, new Node(3));
    tree_insert(root, new Node(10));
    tree_insert(root, new Node(18));
    tree_insert(root, new Node(2));
    tree_insert(root, new Node(4));
    tree_insert(root, new Node(12));
    tree_insert(root, new Node(15));
    tree_insert(root, new Node(13));
    tree_insert(root, new Node(9));

    inorder_tree_walk(root);

    std::cout << "\n";

    normal_tree_walk(root);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

