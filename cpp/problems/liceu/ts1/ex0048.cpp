// TS1 e2 p110 pdf v2
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    float a, b, c;
    cout << "a = "; cin >> a;
    cout << "b = "; cin >> b;
    cout << "c = "; cin >> c;
    if (a < b + c && b < a + c && c < a + b) cout << "e triunghi" << endl;
    else cout << "nu e triunghi" << endl; 
    return 0;
}
