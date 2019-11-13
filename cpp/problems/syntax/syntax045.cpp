#include <iostream>
using namespace std;

struct Node {
    int a;
};

void increment(Node node) {
    node.a++;
}

void increment2(Node *node) {
    node->a++;
}

void increment3(Node &node) {
    node.a++;
}

int main(int argc, char *argv[]) {
    Node node;
    node.a = 5;
    increment(node);
    cout << node.a << endl;

    increment2(&node);
    cout << node.a << endl;

    increment3(node);
    cout << node.a << endl;

    return 0;
}
