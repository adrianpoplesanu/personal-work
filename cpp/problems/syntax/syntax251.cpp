#include <iostream>

int main(int argc, char* argv[]) {
    int* a = new int();
    *a = 5;
    std::cout << "deleting once\n";
    delete a;
    //a = NULL;
    if (a) {
        std::cout << "deleting twice\n";
        delete a;
    }
    return 0;
}
