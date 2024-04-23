#include <iostream>

struct Node {
    int a = 5;
};

Node *p_node;
Node s_node;

void setNode(Node *node) {
    p_node = node;
}

void useNode(Node *node) {
    std::cout << node->a << "\n";
    std::cout << s_node.a << "\n";
}

void test() {
    Node node;
    node.a = 77;
    std::cout << node.a << "\n";
    setNode(&node); // this is wrong, node gets deallocated once test() finishes
    s_node = node; // this works
}


int main(int argc, char* argv[]) {
    test();
    useNode(p_node);
    return 0;
}
