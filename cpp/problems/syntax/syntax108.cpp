#include <iostream>
using namespace std;

void change_val(int &a) {
    a = 7;
}

int main(int argc, char *argv[]) {
    int a = 5;
    change_val(a);
    cout << a << endl;
    return 0;
}
