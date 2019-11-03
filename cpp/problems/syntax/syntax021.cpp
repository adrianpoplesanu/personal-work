#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int a[] = {1, 3, 7, 4};
    for (int i = 0; i < 4; i++) cout << a[i] << " ";
    cout << endl;
    for (int i = 0; i < 4; i++) cout << i[a] << " ";
    cout << endl;
    for (int i = 0; i < 4; i++) cout << a + i << " ";
    cout << endl;
    for (int i = 0; i < 4; i++) cout << *(a + i) << " ";
    cout << endl;
    cout << a << endl;
    cout << *a << endl;
    return 0;
}
