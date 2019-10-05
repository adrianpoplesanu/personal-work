// TS1 e11 p110 v1 pdf
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n; 
    float e = 0;
    cout << "n = "; cin >> n;
    for(int i = 1; i <= n; i++) {
        e += 1/(float)(i * i);
    }
    cout << "e1 = " << e << endl;
    return 0;
}
