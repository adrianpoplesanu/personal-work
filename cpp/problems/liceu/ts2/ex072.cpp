// ts2 p42 e2
#include <iostream>
#include <fstream>
using namespace std;

void read(int &n, int &m, int a[100][100]) {
    ifstream in("ex072.in");
    in >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) in >> a[i][j];
    }
    in.close();
}

void show(int n, int m, int a[100][100]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }
}

int main(int argc, char *argv[]) {
    int a[100][100], n, m;
    read(n, m, a);
    show(n, m, a);
    return 0;
}
