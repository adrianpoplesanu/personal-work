#include <iostream>

int main(int argc, char *argv[]) {
    for (int i = 11; i < 92; i++) {
        std::cout << "mv test" << i << ".ad test0" << i << ".ad ;\n";
    }
    std::cout << "echo 'done!'\n";
    return 0;
}
