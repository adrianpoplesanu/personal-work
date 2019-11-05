#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int b = 1000;
    cout << (b >> 8) << endl; // 3 * 256 = 768 ; 4 * 256 = 1024
    cout << (768 >> 8) << endl; // 3
    cout << (767 >> 8) << endl;  // 2
    cout << (1023 >> 8) << endl; // 3
    cout << (1024 >> 8) <<endl; // 4
    return 0;
}
