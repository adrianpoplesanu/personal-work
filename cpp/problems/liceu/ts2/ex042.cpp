// ts2 p23 e1
#include <iostream>
using namespace std;

void read(int vt[10], int n) {
    int i;
    for (i = 0; i < n; i++) {
        cout << "vt[" << i << "] = "; cin >> vt[i];
    }
}

void sort(int vt[10], int n) {
    int found, aux;
    do {
        found = 0;
        for (int i = 0; i < n - 1; i++)
            if (vt[i] > vt[i + 1]) {
                aux = vt[i];
                vt[i] = vt[i + 1];
                vt[i + 1] = aux;
                found = 1;
            }
    } while(found);
}

void write(int vt[10], int n) {
    for (int i = 0; i < n; i++) cout << vt[i] << " ";
    cout << "\n"; 
}

int main(int argc, char *argv[]) {
    int v[10], n;
    cout << "n = "; cin >> n;
    read(v, n);
    sort(v, n);
    write(v, n);
    return 0;
}
