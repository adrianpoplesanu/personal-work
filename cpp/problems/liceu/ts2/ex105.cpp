// ts2 p57 e1 - studiu de caz liste simplu inlantuite memorate intr-un vector
#include <iostream>
using namespace std;

typedef int adresa;

struct Nod {
    int info;
    adresa adr_urm;
};

Nod L[1000];
int nr_elem;
adresa ocupat[1000]; // this could be bool
adresa v = -1, sf = -1;

int Exista_spatiu() {
    return nr_elem < 1000;
}

void Aloca(adresa &x) {
    adresa i = 0;
    while (ocupat[i]) i++;
    x = i;
    ocupat[i] = 1;
    nr_elem++;
}

void Elibereaza(adresa x) {
    ocupat[x] = 0;
    nr_elem--;
}

void Adaugare(adresa &varf, int val) {
    adresa c;
    if (varf == -1) {
        Aloca(varf);
        L[varf].info = val;
        L[varf].adr_urm = -1;
        sf = varf;
    } else {
        if (Exista_spatiu()) {
            Aloca(c);
            L[sf].adr_urm = c;
            L[c].info = val;
            L[c].adr_urm = -1;
            sf = c;
        } else {
            cout << "lipsa spatiu\n";
        }
    }
}

void Inserare_dupa(adresa varf, int val, int val1) {
    adresa c = varf;
    while (L[c].info != val) c = L[c].adr_urm;
    if (sf == c) {
        Adaugare(varf, val1);
    } else {
        adresa element;
        Aloca(element);
        L[element].adr_urm = L[c].adr_urm;
        L[element].info = val1;
        L[c].adr_urm = element;
    }
}

void Inserare_inainte(adresa &varf, int val, int val1) {
    adresa c = varf, prev = -1;
    while (L[c].info != val) {
        prev = c;
        c = L[c].adr_urm;
    }
    if (prev == -1) { 
        adresa element;
        Aloca(element);
        L[element].info = val1;
        L[element].adr_urm = varf;
        varf = element;
    } else {
        adresa element;
        Aloca(element);
        L[element].info = val1;
        L[element].adr_urm = c;
        L[prev].adr_urm = element;
    }
}

void Sterge(adresa &varf, int val) {
    adresa c = varf, prev = -1;
    while (L[c].info != val) {
        prev = c;
        c = L[c].adr_urm;
    }
    if (c == varf) {
        varf = L[c].adr_urm;
        Elibereaza(c);
    } else {
        adresa next = L[c].adr_urm;
        L[prev].adr_urm = next;
        Elibereaza(c);
    }
}

void Listare(adresa v) {
    adresa c = v;
    while (c != -1) {
        cout << L[c].info << " ";
        c = L[c].adr_urm;
    }
    cout << '\n';
}

int main (int argc, char *argv[]) {
    Adaugare (v, 7);
    Adaugare (v, 5);
    Adaugare (v, 3);
    Inserare_dupa(v, 5, 6);
    Sterge(v, 5);
    Inserare_inainte(v, 6, 4);
    Listare (v);
    return 0;
}
