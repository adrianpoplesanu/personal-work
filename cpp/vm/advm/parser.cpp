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
    //prefixParseFns.insert(std::make_pair(TT_IF, [this]() { return parseIfStatement(); } ));
    prefixParseFns.insert(std::make_pair(TT_IF, &Parser::parseIfStatement));
    prefixParseFns.insert(std::make_pair(TT_NULL, &Parser::parseNullExpression));
    prefixParseFns.insert(std::make_pair(TT_STRING, &Parser::parseStringLiteral));
    prefixParseFns.insert(std::make_pair(TT_LBRACKET, &Parser::parseListLiteral));
    prefixParseFns.insert(std::make_pair(TT_LBRACE, &Parser::parseHashLiteral));

    prefixParseFns.insert(std::make_pair(TT_FUNC, &Parser::parseFunctionLiteral));

    infixParseFns.insert(std::make_pair(TT_PLUS, &Parser::parseInfixExpression));
    infixParseFns.insert(std::make_pair(TT_MINUS, &Parser::parseInfixExpression));
    infixParseFns.insert(std::make_pair(TT_MULTIPLY, &Parser::parseInfixExpression));
    infixParseFns.insert(std::make_pair(TT_DIVIDE, &Parser::parseInfixExpression));
    infixParseFns.insert(std::make_pair(TT_GT, &Parser::parseInfixExpression));
    infixParseFns.insert(std::make_pair(TT_LT, &Parser::parseInfixExpression));
    infixParseFns.insert(std::make_pair(TT_GTE, &Parser::parseInfixExpression));
    infixParseFns.insert(std::make_pair(TT_LTE, &Parser::parseInfixExpression));
    infixParseFns.insert(std::make_pair(TT_EQUALS, &Parser::parseInfixExpression));
    infixParseFns.insert(std::make_pair(TT_LBRACKET, &Parser::parseIndexExpression));
    infixParseFns.insert(std::make_pair(TT_LPAREN, &Parser::parseCallExpression));
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
    /*if (currentToken.type == TT_BREAK)
        return parseBreakStatement();
    if (currentToken.type == TT_CONTINUE)
        return parseContinueStatement();
    if (currentToken.type == TT_MULTICOMMENT)
        return parseComment();
    if (currentToken.type == TT_SINGLECOMMENT)
        return parseSingleLineComment();
    if (currentToken.type == TT_IF)
        return parseIfStatement();*/
    return parseExpressionStatement();
}

ASTNode* Parser::parseIdent() {
    ASTIdentifier *ident = new ASTIdentifier(currentToken, currentToken.stringLiteral);
    return ident;
}

ASTNode* Parser::parseLetStatement() {
    ASTLetStatement* stmt = new ASTLetStatement(currentToken);

    if (!expectPeek(TT_IDENT)) {
        //delete stmt;
        free_memory_ASTNode(stmt);
        return NULL;
    }

    stmt->name = ASTIdentifier(currentToken, currentToken.stringLiteral);

    if (!expectPeek(TT_ASSIGN)) {
        //delete stmt;
        free_memory_ASTNode(stmt);
        return NULL;
    }

    nextToken();
    stmt->value = parseExpression(PT_LOWEST);
    if (currentTokenIs(TT_SEMICOLON)) {
        nextToken();
    }
    return stmt;
}

ASTNode* Parser::parseReturnStatement() {
    ASTReturnStatement* stmt = new ASTReturnStatement(currentToken);
    nextToken();
    stmt->value = parseExpression(PT_LOWEST);
    if (peekTokenIs(TT_RBRACE) || peekTokenIs(TT_SEMICOLON) || peekTokenIs(TT_EOF)) {
        return stmt;
    }
    return stmt;
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

ASTNode* Parser::parseNullExpression() {
    ASTNullExpression *expr = new ASTNullExpression();
    nextToken();
    return expr;
}

ASTNode* Parser::parseStringLiteral() {
    ASTString *expr = new ASTString(currentToken, currentToken.stringLiteral);
    return expr;
}

ASTNode* Parser::parseListLiteral() {
    ASTList* expr = new ASTList(currentToken);
    expr->elements = parseListExpressions();
    return expr;
}

std::vector<ASTNode*> Parser::parseListExpressions() {
    std::vector<ASTNode*> elements;
    if (peekTokenIs(TT_RBRACKET)) {
        nextToken();
        return elements;
    }
    nextToken();
    ASTNode* element = parseExpression(PT_LOWEST);
    //Ad_INCREF(element); // this might be needed
    elements.push_back(element);
    while(peekTokenIs(TT_COMMA)) {
        nextToken();
        nextToken();
        element = parseExpression(PT_LOWEST);
        //Ad_INCREF(element); // this might be needed
        elements.push_back(element);
    }
    if (!expectPeek(TT_RBRACKET)) {
        std::vector<ASTNode*> empty;
        return empty;
    }
    return elements;
}

ASTNode* Parser::parseHashLiteral() {
    ASTHash* hash = new ASTHash(currentToken);
    while (!peekTokenIs(TT_RBRACE)) {
        nextToken();
        ASTNode* key = parseExpression(PT_LOWEST);
        if (!expectPeek(TT_COLON)) {
            return NULL;
        }
        nextToken();
        ASTNode* value = parseExpression(PT_LOWEST);
        //Ad_INCREF(key);
        //Ad_INCREF(value);
        hash->pairs.insert(std::make_pair(key, value));
        if (!peekTokenIs(TT_RBRACE) && !expectPeek(TT_COMMA)) {
            return NULL;
        }
    }
    if (!expectPeek(TT_RBRACE)) {
        return NULL;
    }
    return hash;
}

ASTNode* Parser::parseFunctionLiteral() {
    ASTFunctionLiteral* fun_lit = new ASTFunctionLiteral(currentToken);
    if (!expectPeek(TT_LPAREN)) {
        //delete fun_lit;
        free_memory_ASTNode(fun_lit);
        return NULL;
    }
    std::pair<std::vector<ASTNode*>, std::vector<ASTNode*>> res = parseFunctionParameters();
    fun_lit->parameters = res.first;
    fun_lit->default_params = res.second;
    if (!expectPeek(TT_LBRACE)) {
        //delete fun_lit;
        free_memory_ASTNode(fun_lit);
        return NULL;
    }
    fun_lit->body = parseBlockStatement();
    Ad_INCREF(fun_lit->body);
    return fun_lit;
}

std::pair<std::vector<ASTNode*>, std::vector<ASTNode*>> Parser::parseFunctionParameters() {
    std::vector<ASTNode*> identifiers;
    std::vector<ASTNode*> defaultParams;
    if (peekTokenIs(TT_RPAREN)) {
        nextToken();
        return std::make_pair(identifiers, defaultParams);
    }
    nextToken();
    ASTIdentifier* ident = new ASTIdentifier(currentToken, currentToken.stringLiteral);
    identifiers.push_back(ident);
    Ad_INCREF(ident);
    if (peekTokenIs(TT_ASSIGN)) {
        nextToken();
        nextToken();
        ASTNode *value = parseExpression(PT_LOWEST);
        defaultParams.push_back(value);
        Ad_INCREF(value);
    }
    while (peekTokenIs(TT_COMMA)) {
        nextToken();
        nextToken();
        ident = new ASTIdentifier(currentToken, currentToken.stringLiteral);
        identifiers.push_back(ident);
        Ad_INCREF(ident);
        if (peekTokenIs(TT_ASSIGN)) {
            nextToken();
            nextToken();
            ASTNode *value = parseExpression(PT_LOWEST);
            defaultParams.push_back(value);
            Ad_INCREF(value);
        } else {
            if (defaultParams.size() > 0) {
                std::cout << "ERROR: no positional arguments allowed after defaulted params!";
            }
        }
    }
    if (!expectPeek(TT_RPAREN)) {
        std::vector<ASTNode*> empty; // i don't like this, it should be NULL
        return std::make_pair(empty, empty);
    }
    return std::make_pair(identifiers, defaultParams);
}

ASTNode* Parser::parseCallExpression(ASTNode* left) {
    ASTCallExpression* expr = new ASTCallExpression(currentToken, left);
    std::pair<std::vector<ASTNode*>, std::vector<ASTNode*>> res = parseCallArguments();
    expr->arguments = res.first;
    expr->kw_args = res.second;
    return expr;
}

std::pair<std::vector<ASTNode*>, std::vector<ASTNode*>> Parser::parseCallArguments() {
    std::vector<ASTNode*> args;
    std::vector<ASTNode*> kw_args;
    if (peekTokenIs(TT_RPAREN)) {
        nextToken();
        return std::make_pair(args, kw_args);
    }
    nextToken();
    ASTNode *expr1 = parseExpression(PT_LOWEST);
    if (expr1->type == AT_ASSIGN_STATEMENT) {
        kw_args.push_back(expr1);
    } else {
        args.push_back(expr1);
    }
    while (peekTokenIs(TT_COMMA)) {
        nextToken();
        nextToken();
        ASTNode *expr1 = parseExpression(PT_LOWEST);
        if (expr1->type == AT_ASSIGN_STATEMENT) {
            kw_args.push_back(expr1);
        } else {
            args.push_back(expr1);
        }
    }
    if (!expectPeek(TT_RPAREN)) {
        std::vector<ASTNode*> empty; // i don't like this, it should be NULL
        return std::make_pair(empty, empty);
    }
    return std::make_pair(args, kw_args);
}

ASTNode* Parser::parseIndexExpression(ASTNode* left) {
    ASTIndexExpression* expr = new ASTIndexExpression(currentToken, left);
    nextToken();

    if (currentTokenIs(TT_COLON)) {
        ASTNode *index = new ASTNullExpression();
        expr->index = index;
    } else {
        ASTNode *index = parseExpression(PT_LOWEST);
        expr->index = index;
        nextToken();
        if (currentTokenIs(TT_RBRACKET)) {
            return expr;
        }
    }

    nextToken();

    if (currentTokenIs(TT_COLON)) {
        ASTNode *indexEnd = new ASTNullExpression();
        expr->indexEnd = indexEnd;
    } else {
        ASTNode *indexEnd = parseExpression(PT_LOWEST);
        expr->indexEnd = indexEnd;
        nextToken();
        if (currentTokenIs(TT_RBRACKET)) {
            ASTNode *step = new ASTInteger(currentToken, 1);
            expr->step = step;
            return expr;
        }
    }

    nextToken();

    if (currentTokenIs(TT_RBRACKET)) {
        ASTNode *step = new ASTInteger(currentToken, 1);
        expr->step = step;
        return expr;
    } else {
        ASTNode *step = parseExpression(PT_LOWEST);
        nextToken();
        expr->step = step;
    }

    if (!currentTokenIs(TT_RBRACKET)) {
        return NULL;
    }

    return expr;
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