#include <iostream>

int main(int argc, char* argv[]) {
    int *a = new int();
    std::cout << a << "\n";
    delete a;
    a = NULL;
    a = new int();
    std::cout << a << "\n";

    /* output:
    [1:20:22] adrianpoplesanu:syntax git:(master*) $ ./syntax250 
    0x600002710010
    0x600002710010
    */
    return 0;
}
