// ts2 p62 e2
#include <iostream>
using namespace std;

struct node {
    int info;
    node* next;
};

int main(int argc, char *argv[]) {
    node *c, *d, *v;
    v = new node();
    v->info = 1;
    c = new node();
    c->info = 2;
    v->next = c;
    d = new node();
    d->info = 3;
    c->next = d;
    c = v;
    while(c) {
        cout << c->info << " ";
        c = c->next;
    }
    cout << '\n';
    return 0;
}