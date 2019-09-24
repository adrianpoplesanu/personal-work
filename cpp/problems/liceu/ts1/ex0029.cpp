// TS1 e1 p 167 v2
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n, s = 0, i = 0;
    cout << "n = "; cin >> n;
    do s+=++i; while(i < n);
    cout << "s = " << s << endl;
    return 0;
}
