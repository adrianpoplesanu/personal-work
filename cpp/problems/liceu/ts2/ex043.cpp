// ts2 p24 e1
#include <iostream>
using namespace std;

struct mat {
    float matrix[6][8];
};

mat read(int m, int n) {
    mat a;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) cin >> a.matrix[i][j];
    return a;
}

int main(int argc, char *argv[]) {
    mat m = read(3, 2);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) cout << m.matrix[i][j] << " ";
        cout << "\n";
    }
    return 0;
}
