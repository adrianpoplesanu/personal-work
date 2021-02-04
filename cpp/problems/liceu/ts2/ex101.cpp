// ts2 p48 e23
#include <iostream>
using namespace std;

struct Rational {
    float x, y;
};

float cmmdc(float a, float b);
float cmmmc(float a, float b);
void simplify(Rational &r);

Rational add (Rational r1, Rational r2) {
    Rational rez;
    float numitor_comun = cmmmc(r1.y, r2.y);
    rez.y = numitor_comun;
    rez.x = numitor_comun / r1.y * r1.x + numitor_comun / r2.y * r2.x;
    simplify(rez);
    return rez;
}

Rational substract (Rational r1, Rational r2) {
    Rational rez;
    float numitor_comun = cmmmc(r1.y, r2.y);
    rez.y = numitor_comun;
    rez.x = numitor_comun / r1.y * r1.x - numitor_comun / r2.y * r2.x;
    simplify(rez);
    return rez;
}

Rational multiply (Rational r1, Rational r2) {
    Rational rez;
    rez.x = r1.x * r2.x;
    rez.y = r1.y * r2.y;
    simplify(rez);
    return rez;
}

Rational divide (Rational r1, Rational r2) {
    Rational rez;
    rez.x = r1.x * r2.y;
    rez.y = r1.y * r2.x;
    simplify(rez);
    return rez;
}

void simplify(Rational &r) {
    float c = cmmdc(r.x, r.y);
    r.x /= c;
    r.y /= c;
}

float cmmdc(float a, float b) {
    // vreau sa fac cea mai putin optimizata metoda ever
    float rez = 1;
    for (float i = 2; i <= a; i++) {
        if ((int)a % (int)i == 0 && (int)b % (int)i == 0) rez = i;
    }
    return rez;
}

float cmmmc(float a, float b) {
    // vreau sa fac cea mai putin optimizata metoda ever
    float rez = a * b;
    for (float i = a * b; i >= 1; i--) {
        if ((int)i % (int)a == 0 && (int)i % (int)b == 0) rez = i;
    }
    return rez;
}

int main(int argc, char *argv[]) {
    Rational r1, r2, o1, o2, o3, o4;
    r1.x = 1; r1.y = 2;
    r2.x = 3; r2.y = 5;
    o1 = add(r1, r2);
    cout << o1.x << " " << o1.y << "\n";
    o2 = substract(r1, r2);
    cout << o2.x << " " << o2.y << "\n";
    o3 = multiply(r1, r2);
    cout << o3.x << " " << o3.y << "\n";
    o4 = divide(r1, r2);
    cout << o4.x << " " << o4.y << "\n";
    return 0;
}
