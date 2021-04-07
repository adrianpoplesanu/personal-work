#include <iostream>
#include <string>
using namespace std;

struct Node {
    void *data;
    Node *next;
};

void display(Node* node) {
    while(node) {
        cout << node->data << " ";
        node = node->next;
    }
    cout << "\n";
}

int main(int argc, char *argv[]) {
    Node *node = new Node();
    int a = 5;
    string s = "aaa";

    node->data = &a;
    node->next = new Node();
    node->next->data = &s;

    display(node);
    return 0;
}
