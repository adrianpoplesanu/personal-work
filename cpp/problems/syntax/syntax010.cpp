#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n = 12321;
    int *num, *inv;
    num = &n;

    cout << *num << endl;
    n++;
    cout << *num << endl;
    return 0;
}
