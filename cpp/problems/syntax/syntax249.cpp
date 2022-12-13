#include <iostream>

int main(int argc, char* argv[]) {
    int *a = new int();
    std::cout << a << "\n";
    delete a;
    a = new int();
    std::cout << a << "\n";

    /* output:
    [1:18:56] adrianpoplesanu:syntax git:(master*) $ ./syntax249 
    0x600002224010
    0x600002224010
    */
    return 0;
}
