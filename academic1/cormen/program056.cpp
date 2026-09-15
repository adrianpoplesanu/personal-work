/*
   exercise: 056
   page: 348
   description: interval tree
   command: echo 10 16 21 8 9 25 30 5 8 15 23 17 19 26 26 0 3 6 10 19 20 | ./program056
*/

#include <iostream>
#include <chrono>
#include <queue>
#include <algorithm>
#include <string>

#define PRINT_EXECUTION_DURATION 0

struct Node {
    int key;
    int high;
    Node *parent;
    Node *left;
    Node *right;
    int color;
    int max;

    Node(int key) : key(key), high(key), parent(nullptr), left(nullptr), right(nullptr), color(0), max(0) {}
    Node(int key, int high) : key(key), high(high), parent(nullptr), left(nullptr), right(nullptr), color(0), max(high) {}
};

void tree_destroy(Node *x, Node *nil) {
    if (x == nil) {
        return;
    }
    tree_destroy(x->left, nil);
    tree_destroy(x->right, nil);
    delete x;
}

struct IntervalTree {
    Node *root;
    Node *nil;
    IntervalTree() : nil(new Node(0)) {
        nil->color = 0;
        nil->high = 0;
        nil->max = -1000000000;
        nil->left = nil;
        nil->right = nil;
        nil->parent = nil;
        root = nil;
    }
    ~IntervalTree() {
        tree_destroy(root, nil);
        delete nil;
    }
};

Node *new_node(IntervalTree &tree, int low, int high) {
    Node *z = new Node(low, high);
    z->parent = tree.nil;
    z->left = tree.nil;
    z->right = tree.nil;
    z->color = 0;
    z->max = high;
    return z;
}

void update_max(Node *x) {
    x->max = std::max(x->high, std::max(x->left->max, x->right->max));
}

Node* tree_minimum(IntervalTree &tree, Node *x) {
    while(x->left != tree.nil) {
        x = x->left;
    }
    return x;
}

Node* tree_search(IntervalTree &tree, Node *x, int k) {
    while(x != tree.nil && k != x->key) {
        if (k < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    return x;
}

bool interval_overlap(Node *x, int low, int high) {
    return x->key <= high && low <= x->high;
}

Node* interval_search(IntervalTree &tree, int low, int high) {
    Node *x = tree.root;
    while(x != tree.nil && !interval_overlap(x, low, high)) {
        if (x->left != tree.nil && x->left->max >= low) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    return x;
}

void left_rotate(IntervalTree &tree, Node *x) {
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
    update_max(x);
    update_max(y);
}

void right_rotate(IntervalTree &tree, Node *x) {
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
    update_max(x);
    update_max(y);
}

void interval_insert_fixup(IntervalTree &tree, Node *z) {
    while(z != tree.nil) {
        update_max(z);
        z = z->parent;
    }
}

void rb_insert_fixup(IntervalTree &tree, Node *z) {
    while(z->parent->color == 1) {
        if (z->parent == z->parent->parent->left) {
            Node *y = z->parent->parent->right;
            if (y->color == 1) {
                z->parent->color = 0;
                y->color = 0;
                z->parent->parent->color = 1;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    left_rotate(tree, z);
                }
                z->parent->color = 0;
                z->parent->parent->color = 1;
                right_rotate(tree, z->parent->parent);
            }
        } else {
            Node *y = z->parent->parent->left;
            if (y->color == 1) {
                z->parent->color = 0;
                y->color = 0;
                z->parent->parent->color = 1;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    right_rotate(tree, z);
                }
                z->parent->color = 0;
                z->parent->parent->color = 1;
                left_rotate(tree, z->parent->parent);
            }
        }
    }
    tree.root->color = 0;
}

void interval_insert(IntervalTree &tree, Node *z) {
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
    z->color = 1;
    z->max = z->high;
    interval_insert_fixup(tree, z->parent);
    rb_insert_fixup(tree, z);
}

void interval_transplant(IntervalTree &tree, Node *u, Node *v) {
    if (u->parent == tree.nil) {
        tree.root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void rb_delete_fixup(IntervalTree &tree, Node *x) {
    while(x != tree.root && x->color == 0) {
        if (x == x->parent->left) {
            Node *w = x->parent->right;
            if (w->color == 1) {
                w->color = 0;
                x->parent->color = 1;
                left_rotate(tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == 0 && w->right->color == 0) {
                w->color = 1;
                x = x->parent;
            } else {
                if (w->right->color == 0) {
                    w->left->color = 0;
                    w->color = 1;
                    right_rotate(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = 0;
                w->right->color = 0;
                left_rotate(tree, x->parent);
                x = tree.root;
            }
        } else {
            Node *w = x->parent->left;
            if (w->color == 1) {
                w->color = 0;
                x->parent->color = 1;
                right_rotate(tree, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == 0 && w->left->color == 0) {
                w->color = 1;
                x = x->parent;
            } else {
                if (w->left->color == 0) {
                    w->right->color = 0;
                    w->color = 1;
                    left_rotate(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = 0;
                w->left->color = 0;
                right_rotate(tree, x->parent);
                x = tree.root;
            }
        }
    }
    x->color = 0;
}

void interval_delete_fixup(IntervalTree &tree, Node *z) {
    while(z != tree.nil) {
        update_max(z);
        z = z->parent;
    }
}

void interval_delete(IntervalTree &tree, Node *z) {
    Node *x;
    Node *y = z;
    int y_original_color = y->color;
    Node *p;
    if (z->left == tree.nil) {
        p = z->parent;
        x = z->right;
        interval_transplant(tree, z, z->right);
    } else if (z->right == tree.nil) {
        p = z->parent;
        x = z->left;
        interval_transplant(tree, z, z->left);
    } else {
        y = tree_minimum(tree, z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
            interval_transplant(tree, z, y);
            y->left = z->left;
            y->left->parent = y;
            p = y;
        } else {
            p = y->parent;
            interval_transplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
            interval_transplant(tree, z, y);
            y->left = z->left;
            y->left->parent = y;
        }
        y->color = z->color;
    }
    interval_delete_fixup(tree, p);
    if (y_original_color == 0) {
        rb_delete_fixup(tree, x);
    }
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
    const int cell = 14;
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
                s = std::to_string(u->key) + "," + std::to_string(u->high) + "(" + std::to_string(u->max) + ")";
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

    IntervalTree tree;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int low;
        int high;
        std::cin >> low >> high;
        Node *z = new_node(tree, low, high);
        interval_insert(tree, z);
    }

    tree_print(tree.root, tree.nil);

    Node *s = interval_search(tree, 22, 25);
    std::cout << "\n";
    if (s == tree.nil) {
        std::cout << "nil\n";
    } else {
        std::cout << s->key << " " << s->high << "\n";
    }

    s = interval_search(tree, 11, 14);
    if (s == tree.nil) {
        std::cout << "nil\n";
    } else {
        std::cout << s->key << " " << s->high << "\n";
    }

    Node *z = tree_search(tree, tree.root, 16);
    interval_delete(tree, z);
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
