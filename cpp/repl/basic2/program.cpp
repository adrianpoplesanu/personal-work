#include "program.h"

Program::Program() {

}

void Program::loop() {
    while(true) {
        std::string line;
        std::cout << ">> ";
        std::cin >> line;
        parser.load(line);

    }
}
