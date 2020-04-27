#include <iostream>
using namespace std;

int add(int x, int y) {
    return x + y;
}

int subtract(int x, int y) {
    return x - y;
}

int (*get_function(char c))(int,int) {
    return (c == '+') ? add : subtract;
}

int main() {
    cout << get_function('+')(5, 7) << endl;
    cout << get_function('-')(7, 5) << endl;
    return 0;
}

