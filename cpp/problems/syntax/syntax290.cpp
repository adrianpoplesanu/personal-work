#include <iostream>

class Number {
public:
    int a;

    Number(int m_a) {
        a = m_a;
    }

    Number operator + (const Number& n) {
        Number number(0);
        number.a = this->a + n.a;
        return number;
    }
};

int main(int argc, char *argv[]) {
    Number a(4), b(5);
    Number c = a + b;
    std::cout << c.a << "\n";
    return 0;
}
