#include "parser.h"

Parser::Parser() {
    prefixParseFns.insert(std::make_pair(TT_IDENT, &Parser::parseIdent));
    prefixParseFns.insert(std::make_pair(TT_INT, &Parser::parseIntegerLiteral));
    prefixParseFns.insert(std::make_pair(TT_MINUS, &Parser::parsePrefixExpression));
    infixParseFns.insert(std::make_pair(TT_PLUS, &Parser::parseInfixExpression));
    infixParseFns.insert(std::make_pair(TT_MINUS, &Parser::parseInfixExpression));
    infixParseFns.insert(std::make_pair(TT_MULTIPLY, &Parser::parseInfixExpression));
    infixParseFns.insert(std::make_pair(TT_DIVIDE, &Parser::parseInfixExpression));
}

PrecedenceType Parser::currentPrecedence() {
    return precedenceMap[currentToken.type];
}

PrecedenceType Parser::peekPrecedence() {
    return precedenceMap[peekToken.type];
}

bool Parser::currentTokenIs(TokenType type) {
    return false;
}

bool Parser::peekTokenIs(TokenType type) {
    return false;
}

void Parser::load(std::string source) {
    lexer.load(source);
    nextToken();
    nextToken();
}

void Parser::buildProgramStatement(ASTProgram *program) {
    while(currentToken.type != TT_EOF) {
        //std::cout << currentToken.toString() << "\n";
        ASTNode* stmt = parseStatement();
        program->statements.push_back(stmt);
        nextToken();
    }
}

void Parser::nextToken() {
    currentToken = peekToken;
    peekToken = lexer.nextToken();
}

ASTNode* Parser::parseStatement() {
    if (currentToken.type == TT_LET)
        return parseLetStatement();
    if (currentToken.type == TT_RETURN)
        return parseReturnStatement();
    if (currentToken.type == TT_BREAK)
        return parseBreakStatement();
    if (currentToken.type == TT_CONTINUE)
        return parseContinueStatement();
    if (currentToken.type == TT_MULTICOMMENT)
        return parseComment();
    if (currentToken.type == TT_SINGLECOMMENT)
        return parseSingleLineComment();
    return parseExpressionStatement();
}

ASTNode* Parser::parseIdent() {
    ASTIdentifier *ident = new ASTIdentifier(currentToken, currentToken.stringLiteral);
    return ident;
}

ASTNode* Parser::parseLetStatement() {
    return NULL;
}

ASTNode* Parser::parseReturnStatement() {
    return NULL;
}

ASTNode* Parser::parseBreakStatement() {
    return NULL;
}

ASTNode* Parser::parseContinueStatement() {
    return NULL;
}

ASTNode* Parser::parseComment() {
    return NULL;
}

ASTNode* Parser::parseSingleLineComment() {
    return NULL;
}

ASTNode* Parser::parseIntegerLiteral() {
    ASTInteger* integer_node = new ASTInteger();
    int val = stoi(currentToken.stringLiteral);
    integer_node->token = currentToken;
    integer_node->value = val;
    return integer_node;
}

ASTNode* Parser::parsePrefixExpression() {
    ASTPrefixExpression *expr = new ASTPrefixExpression();
    return NULL;
}

ASTNode* Parser::parseInfixExpression(ASTNode* left) {
    ASTInfixExpression* expr = new ASTInfixExpression();
    expr->token = currentToken;
    expr->_operator = currentToken.stringLiteral;
    expr->left = left;
    PrecedenceType preced = currentPrecedence();
    nextToken();
    expr->right = parseExpression(preced);
    return expr;
}

ASTNode* Parser::parseExpressionStatement() {
    ASTExpressionStatement* stmt = new ASTExpressionStatement(currentToken);
    stmt->expression = parseExpression(PT_LOWEST);
    if (peekTokenIs(TT_SEMICOLON)) {
        nextToken();
    }
    return stmt;
}

ASTNode* Parser::parseExpression(PrecedenceType precedence) {
    if (prefixParseFns.find(currentToken.type) == prefixParseFns.end()) {
        return NULL;
    }
    PrefixCallback prefix = prefixParseFns[currentToken.type];

    ASTNode* leftExp = (this->*prefix)();

    while(!peekTokenIs(TT_SEMICOLON) && (precedence < peekPrecedence())) {
        if (infixParseFns.find(peekToken.type) == infixParseFns.end()) {
            return leftExp;
        }
        InfixCallback infix = infixParseFns[peekToken.type];
        nextToken();
        leftExp = (this->*infix)(leftExp);
    }
    return leftExp;
}