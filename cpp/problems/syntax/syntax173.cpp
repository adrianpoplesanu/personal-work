#include <iostream>
using namespace std;

template<typename E>
struct Node {
    E info;
    Node *next;
};

int main(int argc, char *argv[]) {
    Node<int> *node;
    cout << node << "\n";

    node = new Node<int>();
    node->info = 5;
    cout << node << "\n";
    cout << node->info << "\n";
    cout << node->next << "\n";

    Node<int> node2;
    node2.info = 6;
    Node<int> node3;
    node3.info = 7;
    node2.next = &node3;
    cout << node2.info << "\n";
    cout << node2.next->info << "\n";
    return 0;
}
