#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int *a;
    a = (int*) malloc(10 * sizeof(int));
    memset(a, 0, 10 * sizeof(int));
    for (int i = 0; i < 10; i++) cout << a[i] << " "; 
    cout << endl;
    return 0;
}
