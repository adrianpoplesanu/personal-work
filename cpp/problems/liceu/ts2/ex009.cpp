// ts2 p10 e1
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int a = 257, i, j;
    char *adr_byte = (char*) &a, masca;
    for (i = 0; i < sizeof(a); i++) {
        masca = 128;
        for (j = 0; j < 8; j++) {
            if (*adr_byte & masca) cout << 1;
            else cout << 0;
            masca >>= 1;
        }
        adr_byte++;
    }
    return 0;
}
