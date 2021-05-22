// ts2 p 71 e1
#include <iostream>

struct Node {
    int info;
    Node* prev;
};

Node* v;
int n;

void Push(Node* &v, int n) {
    if (v) {
       Node* cur = new Node();
       cur->info = n;
       cur->prev = v;
       v = cur;
    } else {
        v = new Node();
        v->info = n;
        v->prev = NULL;
    }
}

int Pop(Node* &v) {
    int res = v->info;
    Node* cur = v;
    v = v->prev;
    delete cur;
    return res;
}

void Print(Node* v) {
    Node* cur = v;
    while(cur) {
        std::cout << cur->info << " ";
        cur = cur->prev;
    }
}

int main(int argc, char *argv[]) {
    Push(v, 1);
    Push(v, 2);
    Push(v, 3);
    Print(v);
    std::cout << Pop(v);
    std::cout << Pop(v);
    Print(v);
    std::cout << Pop(v);
    return 0;
}
