#include "program.h"
#include "lexer.h"
#include <iostream>

Program::Program() {
    lexer = Lexer();
}

Program::~Program() {

}

void Program::Loop() {
    while (1) {
        std::string line;
        std::cout << ">> ";
        //std::cin >> line;
        std::getline(std::cin, line);
        //std::cout << line << '\n';
        ParseLine(line);
    }
}

void Program::ParseLine(std::string line) {
    lexer.Load(line);
    Token current_token = lexer.NextToken();
    while(current_token.token_type != END) {
        cout << current_token.ToString() << "\n";
        current_token = lexer.NextToken();
    }
    //cout << '\n';
}