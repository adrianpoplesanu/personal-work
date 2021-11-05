#include <iostream>
#include <vector>
#include <map>

enum TokenType {
    TT_PLUS,
    TT_MINUS,
    TT_ASTERISK,
    TT_SLASH,
    TT_INT,
    TT_LPAREN,
    TT_RPAREN,
    TT_EOF
};

struct Token {
    TokenType type;
    std::string val;
};

class AstNode {
public:
    virtual std::string inspect() {
        return "ERROR: not implemented in subclass";
    }
};

class AstInfixExpression : public AstNode {
public:
    AstNode *left;
    AstNode *right;
    std::string op;
    virtual std::string inspect() {
        return "(" + left->inspect() + op + right->inspect() + ")";
    }
};

class AstPrefixExpression : public AstNode {
public:
    AstNode *right;
    virtual std::string inspect() {
        return "(-" + right->inspect() + ")";
    }
};

class AstExpressionStatement : public AstNode {
public:
    AstNode *expression;
    virtual std::string inspect() {
        return expression->inspect();
    }
};

class AstInteger : public AstNode {
public:
    std::string val;
    virtual std::string inspect() {
        return val;
    }
};

enum PrecedenceType {
    PT_LOWEST,
    PT_SUM,
    PT_PRODUCT,
    PT_PREFIX,
    PT_CALL
};

class Parser {
public:
    std::vector<Token> tokens;
    Token current_token, peek_token;
    int pos;
    typedef AstNode* (Parser::*PrefixCallback)();
    typedef AstNode* (Parser::*InfixCallback)(AstNode*);
    std::map<TokenType, PrefixCallback> prefixParseFns;
    std::map<TokenType, InfixCallback> infixParseFns;

    Parser() {
        prefixParseFns.insert(std::make_pair(TT_INT, &Parser::parseInteger));
        prefixParseFns.insert(std::make_pair(TT_MINUS, &Parser::parsePrefixExpression));
        prefixParseFns.insert(std::make_pair(TT_LPAREN, &Parser::parseGroupedExpression));
        infixParseFns.insert(std::make_pair(TT_PLUS, &Parser::parseInfixExpression));
        infixParseFns.insert(std::make_pair(TT_MINUS, &Parser::parseInfixExpression));
        infixParseFns.insert(std::make_pair(TT_ASTERISK, &Parser::parseInfixExpression));
        infixParseFns.insert(std::make_pair(TT_SLASH, &Parser::parseInfixExpression));
    }

    void load(std::vector<Token> t) {
        tokens = t;
        pos = 0;
        current_token = tokens[pos];
        peek_token = tokens[pos + 1];
    }

    void nextToken() {
        pos++;
        current_token = tokens[pos];
        peek_token = tokens[pos + 1];
    }

    PrecedenceType current_precedence() {
        switch(current_token.type) {
            case TT_PLUS:
                return PT_SUM;
            case TT_MINUS:
                return PT_SUM;
            case TT_ASTERISK:
                return PT_PRODUCT;
            case TT_SLASH:
                return PT_PRODUCT;
            default:
                return PT_LOWEST;
        }
    }

    PrecedenceType peek_precedence() {
        switch(peek_token.type) {
            case TT_PLUS:
                return PT_SUM;
            case TT_MINUS:
                return PT_SUM;
            case TT_ASTERISK:
                return PT_PRODUCT;
            case TT_SLASH:
                return PT_PRODUCT;
            default:
                return PT_LOWEST;
        }
    }

    AstNode* parseInteger() {
        AstInteger* obj = new AstInteger();
        obj->val = current_token.val;
        return obj;
    }

    AstNode* parsePrefixExpression() {
        AstPrefixExpression* expr = new AstPrefixExpression();
        nextToken();
        expr->right = parseExpression(PT_PREFIX);
        return expr;
    }

    AstNode* parseGroupedExpression() {
        nextToken();
        AstNode *expr = parseExpression(PT_LOWEST);
        if (peek_token.type == TT_RPAREN) nextToken();
        return expr;
    }

    AstNode* parseInfixExpression(AstNode* left) {
        AstInfixExpression* expr = new AstInfixExpression();
        expr->left = left;
        expr->op = current_token.val;
        PrecedenceType precedence = current_precedence();
        nextToken();
        expr->right = parseExpression(precedence);
        return expr;
    }

    AstNode* parseExpression(PrecedenceType precedence) {
        if (prefixParseFns.find(current_token.type) == prefixParseFns.end()) {
            return NULL;
        }
        PrefixCallback prefix = prefixParseFns[current_token.type];
        AstNode* left = (this->* prefix)();
        while(precedence < peek_precedence()) {
            if (infixParseFns.find(peek_token.type) == infixParseFns.end()) {
                return left;
            }
            InfixCallback infix = infixParseFns[peek_token.type];
            nextToken();
            left = (this->*infix)(left);
        }
        return left;
    }

    AstNode* parseExpressionStatement() {
        AstExpressionStatement* stmt = new AstExpressionStatement();
        stmt->expression = parseExpression(PT_LOWEST);
        return stmt;
    }

    void build_program_statements() {
        while(current_token.type != TT_EOF) {
            AstNode *stmt = parseExpressionStatement();
            nextToken();
            if (stmt != NULL) {
                std::cout << stmt->inspect() << '\n';
            }
        }
    }
};

bool is_digit(char ch) {
    return ('0' < ch) && (ch < '9');
}

std::vector<Token> get_tokens(std::string source) {
    std::vector<Token> tokens;
    int pos = 0;
    while (pos < source.length()) {
        Token t;
        switch(source[pos]) {
            case '+':
                t.type = TT_PLUS;
                t.val = "+";
                tokens.push_back(t);
            break;
            case '-':
                t.type = TT_MINUS;
                t.val = "-";
                tokens.push_back(t);
            break;
            case '*':
                t.type = TT_ASTERISK;
                t.val = "*";
                tokens.push_back(t);
            break;
            case '/':
                t.type = TT_SLASH;
                t.val = "/";
                tokens.push_back(t);
            break;
            case '(':
                t.type = TT_LPAREN;
                t.val = "(";
                tokens.push_back(t);
            break;
            case ')':
                t.type = TT_RPAREN;
                t.val = ")";
                tokens.push_back(t);
            break;
            default:
                if (is_digit(source[pos])) {
                    int start = pos;
                    while(is_digit(source[pos])) pos++;
                    t.type = TT_INT;
                    t.val = source.substr(start, pos - start);
                    pos--;
                    tokens.push_back(t);
                }
            break;
        }
        pos++;
    }
    Token end;
    end.type = TT_EOF;
    end.val = "EOF";
    tokens.push_back(end);
    tokens.push_back(end);
    return tokens;
}

void print_tokens(std::vector<Token> tokens) {
    for (int i = 0; i < tokens.size(); i++) {
        std::cout << "Token [type: " << tokens[i].type << ", type: " << tokens[i].val << "]\n";
    }
}

int main(int argc, char *argv[]) {
    while(1) {
        std::cout << ">> ";
        std::string source;
        getline(std::cin, source);
        if (source == "exit()") break;
        if (source != "") {
            std::vector<Token> tokens = get_tokens(source);
            //print_tokens(tokens);
            Parser parser;
            parser.load(tokens);
            parser.build_program_statements();
        }
    }
    return 0;
}
