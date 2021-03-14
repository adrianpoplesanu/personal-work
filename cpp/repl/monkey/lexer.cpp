#include "lexer.h"
#include <string>
using namespace std;

Lexer::Lexer() {
    position = 0;
    readPosition = 0;
}

Lexer::~Lexer() {

}

void Lexer::Load(string s) {
    position = 0;
    readPosition = 0;
    source = s;
    ReadChar();
}

void Lexer::ReadChar() {
    if (readPosition < source.length()) {
        current_char = source[readPosition];
    } else {
        current_char = 0;
    }
    position = readPosition;
    readPosition++;
}

char Lexer::NextToken() {
    switch(current_char) {
        case 0:
            return 0;
            break;
        default:
            return current_char;
            break;
    }
}