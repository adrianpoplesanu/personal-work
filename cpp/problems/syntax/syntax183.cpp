// stiva cu un tip generic
#include <iostream>
#include <string>

template<typename T>
struct Node {
    T info;
    Node<T>* prev;
};

Node<int>* st;
Node<std::string>* st2;
int n;

template<typename T>
void Push(Node<T>* &v, T val) {
    if (v) {
        Node<T>* cur = new Node<T>();
        cur->info = val;
        cur->prev = v;
        v = cur;
    } else {
        v = new Node<T>();
        v->info = val;
        v->prev = 0x0;
    }
}

template<typename T>
T Pop(Node<T>* &v) {
    if (v) {
        Node<T>* cur = v;
        v = v->prev;
        T res = cur->info;
        delete cur;
        return res;
    }
    T e;
    return e;
}

int main(int argc, char *argv[]) {
    Push(st, 1);
    Push(st, 2);
    Push(st, 3);
    std::cout << Pop(st);
    std::cout << Pop(st);
    std::cout << Pop(st);

    std::string a = "!", b = "dimineata", c = "buna";
    Push(st2, a);
    Push(st2, b);
    Push(st2, c);
    std::cout << Pop(st2);
    std::cout << Pop(st2);
    std::cout << Pop(st2);
    return 0;
}
