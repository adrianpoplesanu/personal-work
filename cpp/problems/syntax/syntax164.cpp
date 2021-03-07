#include <iostream>
using namespace std;

struct Node {
    Node* next;
    int info;
};

void Change(Node *node) {
    node = new Node();
    cout << node << '\n';
    delete node; // daca nu pun delete atunci o sa se incementeze pointerul de memorie pentru Node
}

void Change2(Node* &node) {
    node = new Node();
    cout << node << '\n';
}

int main(int argc, char *argv[]) {
    Node *node = new Node();
    cout << node << '\n';
    Change(node);
    cout << node << '\n';
    Change2(node);
    cout << node << '\n';
    return 0;
}
