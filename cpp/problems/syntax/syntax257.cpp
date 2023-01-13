#include <iostream>

// [19:28:37] adrianpoplesanu:syntax git:(master*) $ leaks --atExit -- ./syntax257

void change(int a) {
    a = 9;
}

void change2(int *a) {
    //delete a;
    int *b = new int();
    a = new int();
    *a = 7;
    delete b;
    //delete a;
}

int main(int argc, char *argv[]) {

    int *a = new int();
    *a = 5;
    std::cout << a << " " << *a << "\n";
    change(*a);
    std::cout << a << " " << *a << "\n";

    change2(a);
    std::cout << a << " " << *a << "\n";

    return 0;
}
