// asta NU MERGE
#include <iostream>

void test2(int n, ...) {
    va_list ap;
    va_start(ap, n);
    for(int i = 1; i <= n; i++) {
        int a = va_arg(ap, int);
	std::cout << a << "\n";
    }
    va_end(ap);
}

void test(int n, ...) {
    va_list ap;
    test2(n, ap);
}

int main(int argc, char *args[]) {
    test(2, 22, 55);
    return 0;
}
