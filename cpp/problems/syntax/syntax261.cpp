#include <iostream>
#include <vector>
#include <map>

enum TokenType {
    ILLEGAL,
    IDENT,
    SUM,
    MINUS,
    MULTIPLY,
    DIVIDE,
    SEMICOLON,
    ASSIGN,
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,
    LBRACKET,
    RBRACKET
};

enum ASTNodeType {
    PROGRAM,
    EXPRESSION_STATEMENT,
    INTEGER,
    IDENTIFIER,
    INFIX_EXPRESSION
};

class Token {
public:
    TokenType type;
    std::string literal;
};

class ASTNode {
public:
    ASTNodeType type;
    Token token;
};

class ASTProgram : public ASTNode {
public:
    std::vector<ASTNode> statements;
};

class Lexer {
public:
    std::string source;
    int position;
    int readPosition;
    char currentChar;
};

class Parser {
public:
    typedef ASTNode (Parser::*prefixCallback)();
    typedef ASTNode (Parser::*infixCallback)(ASTNode);

    std::map<TokenType, prefixCallback> prefixParseFns;
    std::map<TokenType, infixCallback> infixParseFns;

    Parser() {

    }
};

class Object {

};

class Environment {

};

class Evaluator {

};

class Repl {
public:
    void loop() {
        while (1) {
            std::cout << "ad > ";
            std::string line;
            std::getline(std::cin, line);
        }
    }
};

int main(int argc, char *argv[]) {
    std::cout << "Ad with no pointers?!?\n";
    Repl repl;
    repl.loop();
    return 0;
}
