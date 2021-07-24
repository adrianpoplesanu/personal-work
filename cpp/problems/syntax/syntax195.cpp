#include <iostream>

int cmmdc(int a, int b) {
    while(a != b) {
        if (a > b) a -= b;
        else if (b > a) b -= a;
    }
    return a;
}

int main(int argc, char *argv[]) {
    int a = 33, b = 44;
    std::cout << cmmdc(a, b) << "\n";
    return 0;
}
