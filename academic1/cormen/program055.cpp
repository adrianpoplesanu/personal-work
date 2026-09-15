/*
   exercise: 055
   page: 339
   description: order-statistic tree
   command: echo 29 10 20 5 7 12 17 25 30 22 27 35 40 37 32 28 24 21 18 16 14 13 11 9 8 6 4 3 2 1 | ./program055
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
    int color;
    int size;

    Node(int key) : key(key), parent(nullptr), left(nullptr), right(nullptr), color(0), size(0) {}
};

void tree_destroy(Node *x, Node *nil) {
    if (x == nil) {
        return;
    }
    tree_destroy(x->left, nil);
    tree_destroy(x->right, nil);
    delete x;
}

struct OrderStatisticTree {
    Node *root;
    Node *nil;
    OrderStatisticTree() : nil(new Node(0)) {
        nil->color = 0;
        nil->size = 0;
        nil->left = nil;
        nil->right = nil;
        nil->parent = nil;
        root = nil;
    }
    ~OrderStatisticTree() {
        tree_destroy(root, nil);
        delete nil;
    }
};

Node *new_node(OrderStatisticTree &tree, int key) {
    Node *z = new Node(key);
    z->parent = tree.nil;
    z->left = tree.nil;
    z->right = tree.nil;
    z->color = 0;
    z->size = 1;
    return z;
}

void update_size(Node *x) {
    x->size = x->left->size + x->right->size + 1;
}

Node* tree_minimum(OrderStatisticTree &tree, Node *x) {
    while(x->left != tree.nil) {
        x = x->left;
    }
    return x;
}

Node* tree_search(OrderStatisticTree &tree, Node *x, int k) {
    while(x != tree.nil && k != x->key) {
        if (k < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    return x;
}

void left_rotate(OrderStatisticTree &tree, Node *x) {
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
    update_size(x);
    update_size(y);
}

void right_rotate(OrderStatisticTree &tree, Node *x) {
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
    update_size(x);
    update_size(y);
}

void os_insert_fixup(OrderStatisticTree &tree, Node *z) {
    while(z != tree.nil) {
        update_size(z);
        z = z->parent;
    }
}

void rb_insert_fixup(OrderStatisticTree &tree, Node *z) {
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

void os_insert(OrderStatisticTree &tree, Node *z) {
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
    z->size = 1;
    os_insert_fixup(tree, z->parent);
    rb_insert_fixup(tree, z);
}

void os_transplant(OrderStatisticTree &tree, Node *u, Node *v) {
    if (u->parent == tree.nil) {
        tree.root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void rb_delete_fixup(OrderStatisticTree &tree, Node *x) {
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

void os_delete_fixup(OrderStatisticTree &tree, Node *z) {
    while(z != tree.nil) {
        update_size(z);
        z = z->parent;
    }
}

void os_delete(OrderStatisticTree &tree, Node *z) {
    Node *x;
    Node *y = z;
    int y_original_color = y->color;
    Node *p;
    if (z->left == tree.nil) {
        p = z->parent;
        x = z->right;
        os_transplant(tree, z, z->right);
    } else if (z->right == tree.nil) {
        p = z->parent;
        x = z->left;
        os_transplant(tree, z, z->left);
    } else {
        y = tree_minimum(tree, z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
            os_transplant(tree, z, y);
            y->left = z->left;
            y->left->parent = y;
            p = y;
        } else {
            p = y->parent;
            os_transplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
            os_transplant(tree, z, y);
            y->left = z->left;
            y->left->parent = y;
        }
        y->color = z->color;
    }
    os_delete_fixup(tree, p);
    if (y_original_color == 0) {
        rb_delete_fixup(tree, x);
    }
}

Node* os_select(OrderStatisticTree &tree, Node *x, int i) {
    while(x != tree.nil) {
        int r = x->left->size + 1;
        if (i == r) {
            return x;
        } else if (i < r) {
            x = x->left;
        } else {
            i = i - r;
            x = x->right;
        }
    }
    return x;
}

int os_rank(OrderStatisticTree &tree, Node *x) {
    int r = x->left->size + 1;
    Node *y = x;
    while(y != tree.root) {
        if (y == y->parent->right) {
            r = r + y->parent->left->size + 1;
        }
        y = y->parent;
    }
    return r;
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
                s = std::to_string(u->key) + "(" + std::to_string(u->size) + ")";
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

    OrderStatisticTree tree;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int key;
        std::cin >> key;
        Node *z = new_node(tree, key);
        os_insert(tree, z);
    }

    tree_print(tree.root, tree.nil);

    std::cout << "\n";
    for (int i = 1; i <= n; i++) {
        Node *s = os_select(tree, tree.root, i);
        std::cout << i << " " << s->key << " " << os_rank(tree, s) << "\n";
    }

    Node *z = tree_search(tree, tree.root, 10);
    os_delete(tree, z);
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
