#include <iostream>
using namespace std;

void print_array(int *a) {
    for (int i = 0; i < 10; i++) cout << a[i] << " ";
    cout << endl;
}

int main(int argc, char *argv[]) {
    int *a;
    a = (int*) calloc(10, sizeof(int));
    for (int i = 0; i < 10; i++) {
        a[i] = 10;
    }
    print_array(a);
    return 0;
}
