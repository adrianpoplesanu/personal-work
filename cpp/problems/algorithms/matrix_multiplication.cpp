#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int A[4][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {1, 2, 3}
    };
    int B[3][2] = {
        {1, 1},
        {1, 2},
        {3, 3}
    };

    int C[4][2];

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            int cell_value = 0;
            for (int k = 0; k < 3; k++) cell_value += A[i][k] * B[k][j];
            C[i][j] = cell_value;
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) cout << C[i][j] << " ";
        cout << "\n";
    }

    return 0;
}
