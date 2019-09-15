// TS1 ex 4 pg132
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n1, n2, n3;
    cout << "Input 3 ints: " << endl;
    cin >> n1 >> n2 >> n3;
    if (n1 == n2 + n3) {
        cout << "Solution: " << n1 << " = " << n2 << " + " << n3 << endl;
    } else
    if (n2 == n1 + n3) {
        cout << "Solution: " << n2 << " = " << n1 << " + " << n3 << endl;
    } else
    if (n3 == n1 + n2) {
        cout << "Solution: " << n3 << " = " << n1 << " + " << n2 << endl;
    } else {
        cout << "No solution" << endl;
    }
    return 0;
}
