#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int a = 3, *adr_int = &a;
    char *adr_char = (char*) adr_int;
    cout << (int)*adr_int << "\n";
    return 0;
}
