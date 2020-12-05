// ts2 p18 e5
#include <iostream>
using namespace std;

void convert_to_binary(int n) {
    if (n != 0) {
        convert_to_binary(n/2);
        cout << n % 2;
    }
}

void convert_decimal_to_binary(float n) {
    n *= 2;
    if (n >= 1) {
        cout << 1;
        n -= 1;
    } else {
        cout << 0;
    }
    if (n != 0) convert_decimal_to_binary(n);
}


int main (int argc, char *argv[]) {
    float a = 1864.78;
    cout << a << "\n";

    int intreg = (int)a;
    float decimal = a - intreg;

    cout << intreg << "\n";
    cout << decimal << "\n";

    convert_to_binary(intreg);
    cout << "\n";

    convert_decimal_to_binary(decimal);
    cout << "\n";

    return 0;
}
