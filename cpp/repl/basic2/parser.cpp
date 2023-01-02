#include "parser.h"

Parser::Parser() {
    prefixParseFns.insert(std::pair(TT_INT, &Parser::parseIntegerExpression));
    prefixParseFns.insert(std::pair(TT_LPAREN, &Parser::parseGroupedExpression));
    infixParseFns.insert(std::pair(TT_PLUS, &Parser::parseInfixExpression));
    infixParseFns.insert(std::pair(TT_MINUS, &Parser::parseInfixExpression));
    infixParseFns.insert(std::pair(TT_MULTIPLY, &Parser::parseInfixExpression));
    infixParseFns.insert(std::pair(TT_DIVIDE, &Parser::parseInfixExpression));
}

void Parser::load(std::string s) {
    source = s;
    lexer.load(source);
    nextToken();
    nextToken();
}

void Parser::nextToken() {
    current_token = peek_token;
    peek_token = lexer.nextToken();
}

Token Parser::currentToken() {
    return current_token;
}

Token Parser::peekToken() {
    return peek_token;
}

bool Parser::currentTokenIs(TokenTypeEnum tte) {
    return current_token.type == tte;
}

bool Parser::peekTokenIs(TokenTypeEnum tte) {
    return peek_token.type == tte;
}

bool Parser::expectPeek(TokenTypeEnum tte) {
    if (peekTokenIs(tte)) {
        nextToken();
        return true;
    } else {
        return false;
    }
}

PrecedenceTypeEnum Parser::currentPrecedence() {
    if (precedences.find(current_token.type) != precedences.end()) {
        return precedences[current_token.type];
    }
    return PT_LOWEST;
}

PrecedenceTypeEnum Parser::peekPrecedence() {
    if (precedences.find(peek_token.type) != precedences.end()) {
        return precedences[peek_token.type];
    }
    return PT_LOWEST;
}

void Parser::parseProgram(ASTProgram& program) {
    while(current_token.type != TT_EOF) {
        ASTNode* node = parseStatement();
        program.statements.push_back(node);
        nextToken();
    }
}

ASTNode* Parser::parseStatement() {
    // check token type for TT_LET, TT_RETURN, TT_COMMENT, etc..., if none of those then i have an expression that needs to be evaluated
    return parseExpressionStatement();
}

ASTNode* Parser::parseExpressionStatement() {
    ASTExpressionStatement *stmt = new ASTExpressionStatement(current_token);
    stmt->expression = parseExpression(PT_LOWEST);
    return stmt;
}

ASTNode* Parser::parseIntegerExpression() {
    ASTInteger *stmt = new ASTInteger(current_token);
    stmt->value = stoi(current_token.tokenLiteral);
    return stmt;
}

ASTNode* Parser::parseGroupedExpression() {
    nextToken();
    ASTNode* expr = parseExpression(PT_LOWEST);
    if (!expectPeek(TT_RPAREN)) {
        //free_Ad_AST_Node_memory(expr); // TODO: yeah, cleanup memory
        return NULL;
    }
    return expr;
}

ASTNode* Parser::parsePrefixExpression() {
    return NULL;
}

ASTNode* Parser::parseInfixExpression(ASTNode* left) {
    ASTInfixExpression *stmt = new ASTInfixExpression(current_token);
    stmt->_operator = current_token.tokenLiteral;
    stmt->left = left;
    PrecedenceTypeEnum current_precedence = currentPrecedence();
    nextToken();
    stmt->right = parseExpression(current_precedence);
    return stmt;
}

ASTNode* Parser::parseExpression(PrecedenceTypeEnum precedence) {
    if (prefixParseFns.find(current_token.type) == prefixParseFns.end()) {
        return NULL;
    }
    PrefixCallback prefix = prefixParseFns[current_token.type];

    ASTNode* leftExp = (this->*prefix)();

    while(!peekTokenIs(TT_SEMICOLON) && (precedence < peekPrecedence())) {
        if (infixParseFns.find(peek_token.type) == infixParseFns.end()) {
            return leftExp;
        }
        InfixCallback infix = infixParseFns[peek_token.type];
        nextToken();
        leftExp = (this->*infix)(leftExp);
    }
    return leftExp;
}