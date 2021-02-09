// ts2 p49 e25
#include <iostream>
using namespace std;

int z;
void test(int a) {
   cout << ++a << " ";
}

int main(int argc, char *argv[]) {
    z = 5; test(z); cout << z << "\n";
    return 0;
}
