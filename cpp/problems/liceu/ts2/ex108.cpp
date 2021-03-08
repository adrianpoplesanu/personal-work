// ts2 p64 e1
#include <iostream>
using namespace std;

struct Node {
    int info;
    Node* next;
};

void Add(Node* &start, Node* &end, int val) {
    if (start == NULL) {
        start = new Node();
        start->info = val;
        end = start;
    } else {
        Node *current = new Node();
        current->info = val;
        end->next = current;
        end = current;
    }
}

void List(Node* v) {
    while(v) {
        cout << v->info << " ";
        v = v->next;
    }
    cout << '\n';
}

void InsertAfter(Node* &start, Node* &end, int searched, int val) {
    Node *c = start;
    while(c->info != searched) {
        c = c->next;
    }
    if (c) {
        Node *current = new Node();
        if (c == end) end = current;
        current->info = val;
        current->next = c->next;
        c->next = current;
    } else {
        cout << "Value " << searched << " not found\n";
    }
}

void InsertBefore(Node* &start, int searched, int val) {

}

void Delete(Node* &start, int searched) {

}

int main(int argc, char *argv[]) {
    Node *start, *end;
    Add(start, end, 1);
    Add(start, end, 2);
    Add(start, end, 3);
    InsertAfter(start, end, 2, 7);
    InsertAfter(start, end, 3, 9);
    InsertAfter(start, end, 9, 2);
    List(start);
    return 0;
}