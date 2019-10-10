#include <iostream>
using namespace std;

int main(int argc, char * argv[]) {
    int n = 12321;
    int *ptr = new int();
    *ptr = n;
    cout << ptr << " " << *ptr << endl;
    n++;
    cout << &n << " " << n << endl;
    cout << ptr << " " << *ptr << endl;
    return 0;
}
