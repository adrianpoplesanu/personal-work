#include <iostream>
using namespace std;

float hardcoded() {
    return 0.5;
}

float hardcoded2() {
    return 0.6;
}

float normalize(float a) {
    return a + 0.2;
}

float normalize2(float (*a)()) {
    return a();
}

int provider() {
    float (*f)(float);
    f = normalize;
    float b = f(0.5);
    return (int)(b * 10);
}

int provider2() {
    float (*f)(float(*a)());
    f = normalize2;

    float b = f (hardcoded);
    return (int)(b * 10);
}

int provider3(float (*normalizer_func)()) {
    float (*f)(float(*a)());
    f = normalize2;   
 
    float b = f (normalizer_func);
    return (int)(b * 10);
}

int main(int argc, char *argv[]) {
    cout << provider() << endl;
    cout << provider2() << endl;
    cout << provider3(hardcoded2) << endl;
    return 0;
}
