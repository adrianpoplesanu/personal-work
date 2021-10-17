#include <iostream>

template<typename T>
struct Node {
    Node* left;
    Node* right;
    T data;
};

template<typename T>
class BinaryTree {
public:
    int size;
    Node<T>* root;
    BinaryTree() {
        root = new Node<T>();
    }
    ~BinaryTree() {
        delete root; // this needs to be a tree traversal(depth-first probably) that deallocates the nodes
    }
    void Print() {

    }
};

int main(int argc, char *argv[]) {
    BinaryTree<int> tree;
    return 0;
}
