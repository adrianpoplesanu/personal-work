/*
   exercise: 054
   page: 333
   description: avl tree
   command: echo 29 10 20 5 7 12 17 25 30 22 27 35 40 37 32 28 24 21 18 16 14 13 11 9 8 6 4 3 2 1 | ./program054
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
    int height;

    Node(int key) : key(key), parent(nullptr), left(nullptr), right(nullptr), height(0) {}
};

void tree_destroy(Node *x, Node *nil) {
    if (x == nil) {
        return;
    }
    tree_destroy(x->left, nil);
    tree_destroy(x->right, nil);
    delete x;
}

struct AVLTree {
    Node *root;
    Node *nil;
    AVLTree() : nil(new Node(0)) {
        nil->height = 0;
        nil->left = nil;
        nil->right = nil;
        nil->parent = nil;
        root = nil;
    }
    ~AVLTree() {
        tree_destroy(root, nil);
        delete nil;
    }
};

Node *new_node(AVLTree &tree, int key) {
    Node *z = new Node(key);
    z->parent = tree.nil;
    z->left = tree.nil;
    z->right = tree.nil;
    z->height = 1;
    return z;
}

void update_height(Node *x) {
    x->height = 1 + std::max(x->left->height, x->right->height);
}

Node* tree_minimum(AVLTree &tree, Node *x) {
    while(x->left != tree.nil) {
        x = x->left;
    }
    return x;
}

Node* tree_search(AVLTree &tree, Node *x, int k) {
    while(x != tree.nil && k != x->key) {
        if (k < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    return x;
}

void left_rotate(AVLTree &tree, Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left != tree.nil) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == tree.nil) {
        tree.root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
    update_height(x);
    update_height(y);
}

void right_rotate(AVLTree &tree, Node *x) {
    Node *y = x->left;
    x->left = y->right;
    if (y->right != tree.nil) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == tree.nil) {
        tree.root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
    update_height(x);
    update_height(y);
}

void avl_balance(AVLTree &tree, Node *z) {
    int bf = z->left->height - z->right->height;
    if (bf == 2) {
        if (z->left->left->height >= z->left->right->height) {
            right_rotate(tree, z);
        } else {
            left_rotate(tree, z->left);
            right_rotate(tree, z);
        }
    } else if (bf == -2) {
        if (z->right->right->height >= z->right->left->height) {
            left_rotate(tree, z);
        } else {
            right_rotate(tree, z->right);
            left_rotate(tree, z);
        }
    }
}

void avl_insert_fixup(AVLTree &tree, Node *z) {
    while(z != tree.nil) {
        update_height(z);
        avl_balance(tree, z);
        z = z->parent;
    }
}

void avl_insert(AVLTree &tree, Node *z) {
    Node *y = tree.nil;
    Node *x = tree.root;
    while(x != tree.nil) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == tree.nil) {
        tree.root = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }
    z->left = tree.nil;
    z->right = tree.nil;
    z->height = 1;
    avl_insert_fixup(tree, z->parent);
}

void avl_transplant(AVLTree &tree, Node *u, Node *v) {
    if (u->parent == tree.nil) {
        tree.root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void avl_delete_fixup(AVLTree &tree, Node *z) {
    while(z != tree.nil) {
        update_height(z);
        avl_balance(tree, z);
        z = z->parent;
    }
}

void avl_delete(AVLTree &tree, Node *z) {
    Node *y = z;
    Node *p;
    if (z->left == tree.nil) {
        p = z->parent;
        avl_transplant(tree, z, z->right);
    } else if (z->right == tree.nil) {
        p = z->parent;
        avl_transplant(tree, z, z->left);
    } else {
        y = tree_minimum(tree, z->right);
        p = y->parent;
        if (y->parent == z) {
            y->right->parent = y;
            avl_transplant(tree, z, y);
            y->left = z->left;
            y->left->parent = y;
            p = y;
        } else {
            avl_transplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
            avl_transplant(tree, z, y);
            y->left = z->left;
            y->left->parent = y;
        }
    }
    avl_delete_fixup(tree, p);
}

int tree_height(Node *x, Node *nil) {
    if (x == nil) {
        return 0;
    }
    return 1 + std::max(tree_height(x->left, nil), tree_height(x->right, nil));
}

void tree_print(Node *x, Node *nil) {
    if (x == nil) {
        return;
    }
    const int cell = 6;
    int h = tree_height(x, nil);
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
            std::string s;
            if (u == nil) {
                s = "-";
            } else {
                s = std::to_string(u->key) + "(" + std::to_string(u->height) + ")";
            }
            int left = (field - (int)s.size()) / 2;
            if (left < 0) {
                left = 0;
            }
            int right = field - left - (int)s.size();
            if (right < 0) {
                right = 0;
            }
            std::cout << std::string(left, ' ') << s << std::string(right, ' ');
            if (u == nil) {
                q.push(nil);
                q.push(nil);
            } else {
                q.push(u->left);
                q.push(u->right);
                if (u->left != nil || u->right != nil) {
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

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    AVLTree tree;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int key;
        std::cin >> key;
        Node *z = new_node(tree, key);
        avl_insert(tree, z);
    }

    tree_print(tree.root, tree.nil);

    Node *z = tree_search(tree, tree.root, 10);
    avl_delete(tree, z);
    delete z;

    std::cout << "\n";
    tree_print(tree.root, tree.nil);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}
