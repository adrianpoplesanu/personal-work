#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int *a;
    a = (int*) calloc(10, sizeof(int));
    for (int i = 0; i < 10; i++) cout << a[i] << " "; cout << endl;
    free(a);
    a = (int*) malloc(10 * sizeof(int));
    memset(a, 0, 10 * sizeof(int)); // works with 0 or -1, documentation says it allocs per bits, so no other values for ints !!! ha haha
    for (int i = 0; i < 10; i++) cout << a[i] << " "; cout << endl;
    free(a);
    return 0;
}
