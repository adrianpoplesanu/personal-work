#include <iostream>
using namespace std;

struct nod {
    int valoare;
    int pozitie;
};

void init_noduri(nod *&noduri, int n) {
    noduri = new nod[n];
}

void fill(nod *&noduri, int n, int value) {
    for(int i = 0; i < n; i++) {
        noduri[i].valoare = value;
        noduri[i].pozitie = i;
    }
}

void print_noduri(nod *noduri, int n) {
    for (int i = 0; i < n; i++) {
        cout << noduri[i].pozitie << " ... " << noduri[i].valoare << endl;
    }
}

int main(int argc, char *argv[]) {
    nod* noduri;
    init_noduri(noduri, 10);
    fill(noduri, 10, 4);
    print_noduri(noduri, 10);
    return 0;
}
