#include "parser.h"

Parser::Parser() {
    statementParseFns.insert(std::make_pair(TT_IF, &Parser::parseIfStatement));

    prefixParseFns.insert(std::make_pair(TT_IDENT, &Parser::parseIdent));
    prefixParseFns.insert(std::make_pair(TT_INT, &Parser::parseIntegerLiteral));
    prefixParseFns.insert(std::make_pair(TT_MINUS, &Parser::parsePrefixExpression));
    prefixParseFns.insert(std::make_pair(TT_BANG, &Parser::parsePrefixExpression));
    prefixParseFns.insert(std::make_pair(TT_TRUE, &Parser::parseBooleanExpression));
    prefixParseFns.insert(std::make_pair(TT_FALSE, &Parser::parseBooleanExpression));
    prefixParseFns.insert(std::make_pair(TT_LPAREN, &Parser::parseGroupedExpression));

    infixParseFns.insert(std::make_pair(TT_PLUS, &Parser::parseInfixExpression));
    infixParseFns.insert(std::make_pair(TT_MINUS, &Parser::parseInfixExpression));
    infixParseFns.insert(std::make_pair(TT_MULTIPLY, &Parser::parseInfixExpression));
    infixParseFns.insert(std::make_pair(TT_DIVIDE, &Parser::parseInfixExpression));
    infixParseFns.insert(std::make_pair(TT_GT, &Parser::parseInfixExpression));
    infixParseFns.insert(std::make_pair(TT_LT, &Parser::parseInfixExpression));
    infixParseFns.insert(std::make_pair(TT_GTE, &Parser::parseInfixExpression));
    infixParseFns.insert(std::make_pair(TT_LTE, &Parser::parseInfixExpression));
    infixParseFns.insert(std::make_pair(TT_EQUALS, &Parser::parseInfixExpression));
}

PrecedenceType Parser::currentPrecedence() {
    return precedenceMap[currentToken.type];
}

PrecedenceType Parser::peekPrecedence() {
    return precedenceMap[peekToken.type];
}

bool Parser::currentTokenIs(TokenType type) {
    return currentToken.type == type;
}

bool Parser::peekTokenIs(TokenType type) {
    return peekToken.type == type;
}

bool Parser::expectPeek(TokenType type) {
    if (peekTokenIs(type)) {
        nextToken();
        return true;
    }
    std::cout << "expect token error: " << tokenTypeConverter[type] << " not found\n";
    return false;
}

void Parser::load(std::string source) {
    lexer.load(source);
    nextToken();
    nextToken();
}

void Parser::buildProgramStatement(ASTProgram *program) {
    while(currentToken.type != TT_EOF) {
        // std::cout << currentToken.toString() << "\n";
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
    if (currentToken.type == TT_IF)
        return parseIfStatement();
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

ASTNode* Parser::parseBooleanExpression() {
    if (currentToken.type == TT_TRUE) {
        ASTBoolean* boolean_node = new ASTBoolean();
        boolean_node->token = currentToken;
        boolean_node->value = true;
        return boolean_node;
    }
    if (currentToken.type == TT_FALSE) {
        ASTBoolean* boolean_node = new ASTBoolean();
        boolean_node->token = currentToken;
        boolean_node->value = false;
        return boolean_node;
    }
    return NULL;
}

ASTNode* Parser::parseGroupedExpression() {
    nextToken();
    ASTNode *expr = parseExpression(PT_LOWEST);
    if (!expectPeek(TT_RPAREN)) {
        return NULL;
    }
    return expr;
}

ASTNode* Parser::parseIfStatement() {
    ASTIfStatement* expr = new ASTIfStatement(currentToken);
    if (!expectPeek(TT_LPAREN)) {
        free_memory_ASTNode(expr);
        return NULL;
    }
    nextToken();
    expr->condition = parseExpression(PT_LOWEST);
    if (!expectPeek(TT_RPAREN)) {
        free_memory_ASTNode(expr);
        return NULL;
    }
    if (!expectPeek(TT_LBRACE)) {
        expr->consequence = parseSingleBlockStatement();
    } else {
        expr->consequence = parseBlockStatement();
    }

    if (peekTokenIs(TT_ELSE)) {
        nextToken();
        if (!expectPeek(TT_LBRACE)) {
            expr->alternative = parseSingleBlockStatement();
        } else {
            expr->alternative = parseBlockStatement();
        }
    }
    return expr;
}

ASTNode* Parser::parseSingleBlockStatement() {
    ASTBlockStatement* block = new ASTBlockStatement(currentToken);
    nextToken();
    ASTNode* stmt = (ASTNode*)parseStatement();
    if (stmt) {
        block->statements.push_back(stmt);
    }
    return block;

}

ASTNode* Parser::parseBlockStatement() {
    ASTBlockStatement* block = new ASTBlockStatement(currentToken);
    nextToken();
    while(!currentTokenIs(TT_RBRACE) && !currentTokenIs(TT_EOF)) {
        ASTNode* stmt = (ASTNode*)parseStatement();
        if (stmt) {
            block->statements.push_back(stmt);
        }
        nextToken();
    }
    return block;

}

ASTNode* Parser::parsePrefixExpression() {
    ASTPrefixExpression *expr = new ASTPrefixExpression(currentToken, currentToken.stringLiteral);
    nextToken();
    expr->right = parseExpression(PT_PREFIX);
    return expr;
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