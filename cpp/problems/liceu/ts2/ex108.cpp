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

void InsertBefore(Node* &start, Node* &end, int searched, int val) {
    Node *c = start, *prev;
    while(c->info != searched) {
        if (c == end) {
            cout << "Value " << searched << " not found\n";
            return;
        }
        prev = c;
        c = c->next;
    }
    if (c == start) {
        prev = new Node();
        prev->info = val;
        prev->next = start;
        start = prev;
    } else {
        Node *current = new Node();
        current->info = val;
        current->next = c;
        prev->next = current;
    }
}

void Delete(Node* &start, Node* &end, int searched) {
    Node *c = start, *prev;
    while(c->info != searched) {
        if (c == end) {
            cout << "Value " << searched << " not found\n";
            return;
        }
        prev = c;
        c = c->next;
    }
    if (c == start) {
        start = c->next;
        delete c;
    } else if (c == end) {
        prev->next = NULL;
        end = prev;
        delete c;
    } else {
        prev->next = c->next;
        delete c;
    }
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
    Delete(start, end, 1);
    List(start);
    Delete(start, end, 2);
    List(start);
    Delete(start, end, 2);
    List(start);
    Delete(start, end, 2);
    List(start);    
    return 0;
}