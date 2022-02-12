#include <iostream>

template <typename T>
struct Node {
    T info;
    Node<T> *next;
};

template <typename T>
void print_node(Node<T> e) {
    std::cout << e.info << "\n";
}

int main(int argc, char *argv[]) {
    Node<int> varf;
    varf.info = 5;
    print_node(varf);
    return 0;
}
