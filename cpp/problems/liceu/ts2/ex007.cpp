#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int a = 3;
    char *adr_char = (char*)&a;
    cout << (int)*adr_char << "\n";
    return 0;
}
