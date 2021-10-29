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
    bool isEmpty();
    void addRoot(Node<T>* r) {
        if (root == NULL) {
            root = r;
        } else {
            std::cout << "root is already\n";
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
        }
    }
    void addRight(Node<T>* p, Node<T>* r) {

    }
};

int main(int argc, char *argv[]) {
    return 0;
}
