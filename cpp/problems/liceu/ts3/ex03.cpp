// binary tree implementation with dynamic nodes
#include <iostream>

template<typename T>
struct Node {
    T info;
    Node<T>* parent;
    Node<T>* left_child;
    Node<T>* right_child;
};

template<typename T>
class BinaryTree {
private:
    Node<T>* root;
    int size;
public:
    int Size() {
        return size;
    }
    bool isEmpty() {
        return size == 0;
    }
    void addRoot(Node<T>* r) {
        if (root == NULL) {
            root = r;
        } else {
            std::cout << "root already exists\n";
        }
    }
    void addLeft(Node<T>* p, Node<T>* l) {
        if (p == NULL) {
            std::cout << "invalid parent for this add\n";
        } else
        if (p->left_child != NULL) {
            std::cout << "parent already has a left child\n";
        } else {
            p->left_child = l;
            size++;
        }
    }
    void addRight(Node<T>* p, Node<T>* r) {
        if (p == NULL) {
            std::cout << "invalid parent for this add\n";
        } else
        if (p->right_child != NULL) {
            std::cout << "parent already has a right child\n";
        } else {
            p->right_child = r;
            size++;
        }
    }
    T set(Node<T>* p, T val) {
        T old = p->info;
        p->info = val;
        return old;
    }
    T get(Node<T>* p) {
        return p->info;
    }
    void PrintSubtreePreorder(Node<T>* p) {
        std::cout << p->info << '\n';
        if (p->left_child != NULL) PrintSubtreePreorder(p->left_child);
        if (p->right_child != NULL) PrintSubtreePreorder(p->right_child);
    }
    void PrintPreorder() {
        PrintSubtreePreorder(root);
    }
};

int main(int argc, char *argv[]) {
    BinaryTree<int> tree;
    Node<int>* rad = new Node<int>();
    rad->info = 1;
    tree.addRoot(rad);
    tree.PrintPreorder();
    return 0;
}
