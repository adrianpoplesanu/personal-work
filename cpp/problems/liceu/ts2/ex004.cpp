// TS2 p7 e2
#include <iostream>
using namespace std;

struct elev {
    char nume[20], prenume[20];
};

int main(int argc, char *argv[]) {
    elev a, *adr = &a;
    strcpy(a.nume, "Alin");
    strcpy(a.prenume, "Andrei");
    cout << (*adr).nume << " " << (*adr).prenume << "\n";
    cout << adr->nume << " " << adr->prenume << "\n";
    return 0;
}
