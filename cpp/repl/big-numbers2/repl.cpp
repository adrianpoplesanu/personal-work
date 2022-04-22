#include "repl.h"

Repl::Repl() {

}

Repl::~Repl() {

}

void Repl::Loop() {
    while(1) {
        std::string line;
        std::cout << ">> ";
        std::getline(std::cin, line);
        bool end_execution = ParseLine(line);
        if (end_execution) {
            break;
        }
    }
}

void Repl::ExecuteFile(std::ifstream& target) {

}

bool Repl::ParseLine(std::string line) {
    return line == "exit";
}
