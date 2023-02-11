#include <iostream>
#include <vector>
#include <map>

enum TokenType {
    TT_ILLEGAL,
    TT_IDENT,
    TT_SUM,
    TT_MINUS,
    TT_MULTIPLY,
    TT_DIVIDE,
    TT_SEMICOLON,
    TT_ASSIGN,
    TT_LPAREN,
    TT_RPAREN,
    TT_LBRACE,
    TT_RBRACE,
    TT_LBRACKET,
    TT_RBRACKET,
    TT_NULLOBJECT
};

enum ASTNodeType {
    AST_PROGRAM,
    AST_EXPRESSION_STATEMENT,
    AST_INTEGER,
    AST_IDENTIFIER,
    AST_INFIX_EXPRESSION,
    AST_BLOCK_STATEMENT,
    AST_IF_EXPRESSION,
    AST_WHILE_EXPRESSION,
    AST_FOR_EXPRESSION
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

    void reset() {

    }
};

class ASTExpressionStatement : public ASTNode {
public:
    ASTNode expression;
};

class Lexer {
public:
    std::string source;
    int position;
    int readPosition;
    char currentChar;

    void load(std::string s) {
        source = s;
        position = 0;
        readPosition = 0;
        currentChar = 0;
    }

    void readChar() {
        if (readPosition >= source.size()) {
            currentChar = 0;
        } else {
            currentChar = source.at(readPosition);
        }
        position = readPosition;
        readPosition++;
    }

    void skipWhitespaces() {
        while (currentChar == ' ' || currentChar == '\t' || currentChar == '\n' || currentChar == '\r') {
            readChar();
        }
    }

    Token nextToken() {
        Token token;
        token.type = TT_ILLEGAL;
        return token;
    }
};

class Parser {
public:
    typedef ASTNode (Parser::*prefixCallback)();
    typedef ASTNode (Parser::*infixCallback)(ASTNode);

    std::map<TokenType, prefixCallback> prefixParseFns;
    std::map<TokenType, infixCallback> infixParseFns;

    std::string source;

    Parser() {
        prefixParseFns.insert(std::make_pair(TT_MINUS, &Parser::parsePrefixExpression));
    }

    ASTNode parsePrefixExpression() {
        ASTNode result;
        return result;
    }

    void load(std::string s) {
        source = s;
    }

    void parseProgram(ASTNode &program) {
        //((ASTProgram) program).reset(); // din cauza asta sunt pointere
    }
};

enum ObjectType {
    OT_INTEGER,
    OT_NULLOBJECT,
    OT_LIST,
    OT_HASH,
    OT_FUNCTION,
    OT_CLASS,
    OT_CLASS_INSTANCE
};

class Object {

};

class Environment {

};

class IntegerObject : public Object {

};

class ClassObject : public Object {

};

class ClassInstance : public Object {

};

class Evaluator {

};

class Repl {
public:
    void loop() {
        while (1) {
            std::cout << "ad> ";
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
