#include <iostream>
using namespace std;

struct Node {
    int info;
    Node* next;
};

void test_memory_segment_used() {
    // pointerul e declarat in metoda iar adresa lui e stodaca in stiva
    // pointerul "pointeaza" insa spre o adresa din heap pentru ca e asignat cu operatorul new
    Node *p = new Node();
    cout << &p << '\n'; // stored in stack
    cout << p << '\n'; // stored in HEAP
}

int main(int argc, char *argv[]) {
    test_memory_segment_used();
    return 0;
}