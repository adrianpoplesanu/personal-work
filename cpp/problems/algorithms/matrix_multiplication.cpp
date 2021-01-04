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
        {1, 1, 2},
        {1, 2, 2},
        {3, 3, 1}
    };

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            cout << A[i][j] << " ";
        }
        cout << "\n";
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            cout << B[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}
