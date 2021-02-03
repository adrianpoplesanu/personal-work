// ts2 p48 e22
#include <iostream>
using namespace std;

struct Complex {
    float x, y;
};

Complex add(Complex c1, Complex c2) {
    Complex rez;
    rez.x = c1.x + c2.x;
    rez.y = c2.y + c2.y;
    return rez;
}

Complex substract(Complex c1, Complex c2) {
    Complex rez;
    rez.x = c1.x - c2.x;
    rez.y = c1.y - c2.y;
    return rez;
}

Complex multiply(Complex c1, Complex c2) {
    Complex rez;
    rez.x = c1.x * c2.x - c1.y * c2.y;
    rez.y = c1.x * c2.y + c2.y * c2.x;
    return rez;
}

Complex divide(Complex c1, Complex c2) {
    Complex rez;
    rez.x = (c1.x * c2.x + c1.y * c2.y) / (c2.x * c2.x + c2.y * c2.y);
    rez.y = (c1.y * c2.x - c1.x * c2.y) / (c2.x * c2.x + c2.y * c2.y);
    return rez;
}

int main(int argc, char *argv[]) {
    Complex c1, c2;
    c1.x = 1; c1.y = 2;
    c2.x = 3; c2.y = 4;
    Complex r1 = add(c1, c2);
    Complex r2 = substract(c1, c2);
    Complex r3 = multiply(c1, c2);
    Complex r4 = divide(c1, c2);
    cout << r1.x << " " << r1.y << "\n";
    cout << r2.x << " " << r2.y << "\n";
    cout << r3.x << " " << r3.y << "\n";
    cout << r4.x << " " << r4.y << "\n";
    return 0;
}
