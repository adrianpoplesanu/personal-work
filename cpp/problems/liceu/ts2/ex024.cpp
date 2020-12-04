// ts2 p17 e2
#include <iostream>
using namespace std;

int main (int argc, char *argv[]) {
    int a = 5; 
    *&a = 7;
    cout << a << "\n"; // 7
    return 0;
}
