#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    float a = 0.12345678;
    cout << (float)((int)(a * 1000000) % 10000) * 0.0001 << endl;
    return 0;
}
