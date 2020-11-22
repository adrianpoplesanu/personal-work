#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int a = 5, j;
    char *adr_byte = (char*) &a, masca = 128;
    for (j = 0; j < 8; ++j) {
        if (*adr_byte & masca) cout << 1;
        else cout << 0;
        *adr_byte = *adr_byte << 1; // sau *adr_byte <<= 1;
    }
    cout << "\n";
    return 0;
}
