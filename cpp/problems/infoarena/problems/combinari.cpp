#include <iostream>
#include <ctime>
using namespace std;

int n = 16;
int a[16];

void afis() {
    for (int i = 0; i < 16; i++) cout << a[i] << " ";
    cout << "\n";
}

void back(int i) {
    if (i == n) {
        afis();
    } else {
        for(int j = 0; j <= 1; j++) {
            a[i] = j;
            back(i + 1);
        }
    }
}

int main(int argc, char *argv[]) {
    double start = clock();
    back(0);
    double end = (clock() - start) / CLOCKS_PER_SEC;
    cout << "ran for: " << end << " seconds\n";
    return 0;
}
