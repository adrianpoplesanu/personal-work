#ifndef __AST_H
#define __AST_H

#include "token.h"
#include <vector>
#include <unordered_map>

enum ASTType {
    AT_PROGRAM,
    AT_EXPRESSION_STATEMENT,
    AT_IDENTIFIER,
    AT_INTEGER,
    AT_BOOLEAN,
    AT_INFIX_EXPRESSION,
    AT_PREFIX_EXPRESSION,
    AT_BLOCK_STATEMENT,
    AT_LET_STATEMENT,
    AT_RETURN_STATEMENT,
    AT_FUNCTION_STATEMENT,
    AT_DEF_STATEMENT,
    AT_WHILE_STATEMENT,
    AT_FOR_STATEMENT,
    AT_IF_STATEMENT,
    AT_NULL_EXPRESSION,
    AT_STRING_LITERAL,
    AT_LIST_LITERAL,
    AT_HASH_LITERAL,
    AT_INDEX_EXPRESSION,
    AT_FUNCTION_LITERAL,
    AT_CALL_EXPRESSION,
    AT_ASSIGN_STATEMENT
};

std::unordered_map<ASTType, std::string> ast_type_map = {
    {AT_PROGRAM, "Program"},
    {AT_EXPRESSION_STATEMENT, "ExpressionStatement"},
    {AT_IDENTIFIER, "Identifier"},
    {AT_INTEGER, "Integer"},
    {AT_BOOLEAN, "Boolean"},
    {AT_INFIX_EXPRESSION, "InfixExpression"},
    {AT_PREFIX_EXPRESSION, "PrefixExpression"},
    {AT_BLOCK_STATEMENT, "BlockStatement"},
    {AT_LET_STATEMENT, "LetStatement"},
    {AT_RETURN_STATEMENT, "ReturnStatement"},
    {AT_FUNCTION_STATEMENT, "FunctionStatement"},
    {AT_DEF_STATEMENT, "DefStatement"},
    {AT_WHILE_STATEMENT, "WhileStatement"},
    {AT_FOR_STATEMENT, "ForStatement"},
    {AT_IF_STATEMENT, "IfStatement"},
    {AT_NULL_EXPRESSION, "NullExpression"},
    {AT_STRING_LITERAL, "String"},
    {AT_LIST_LITERAL, "List"},
    {AT_HASH_LITERAL, "Hash"},
    {AT_INDEX_EXPRESSION, "IndexExpression"},
    {AT_FUNCTION_LITERAL, "Function"},
    {AT_CALL_EXPRESSION, "CallExpression"},
    {AT_ASSIGN_STATEMENT, "AssignStatement"}
};

class ASTNode {
public:
    Token token;
    ASTType type;
    int ref_count;

    virtual std::string inspect();
    virtual std::string toString();
    virtual std::string hash();
    //virtual ASTNode* copy(); // TODO: uncomment this
};

class ASTProgram : public ASTNode {
public:
    std::vector<ASTNode*> statements;

    ASTProgram();
    ~ASTProgram();
    virtual std::string inspect();
    virtual std::string toString();
    void reset();
};

class ASTIdentifier : public ASTNode {
public:
    std::string value;

    ASTIdentifier();
    ASTIdentifier(Token, std::string);
    virtual std::string inspect();
    virtual std::string toString();
};

class ASTExpressionStatement : public ASTNode {
public:
    ASTNode* expression;

    ASTExpressionStatement();
    ASTExpressionStatement(Token);
    ASTExpressionStatement(Token, ASTNode*);
    ~ASTExpressionStatement();
    virtual std::string inspect();
    virtual std::string toString();
};

class ASTInfixExpression : public ASTNode {
public:
    ASTNode* left;
    ASTNode* right;
    std::string _operator;

    ASTInfixExpression();
    ASTInfixExpression(Token);
    ASTInfixExpression(Token, ASTNode*, ASTNode*, std::string);
    ~ASTInfixExpression();
    virtual std::string inspect();
    virtual std::string toString();
};

class ASTPrefixExpression : public ASTNode {
public:
    ASTNode* right;
    std::string _operator;

    ASTPrefixExpression(Token, std::string);
    ~ASTPrefixExpression();
};

class ASTLetStatement : public ASTNode {
public:
    ASTIdentifier name;
    ASTNode *value;

    ASTLetStatement();
    ASTLetStatement(Token);
    virtual std::string inspect();
    virtual std::string toString();
};

class ASTReturnStatement : public ASTNode {
    
};

class ASTFunctionStatement : public ASTNode {

};

class ASTDefStatement : public ASTNode {

};

class ASTInteger : public ASTNode {
public:
    int value;

    ASTInteger();
    ASTInteger(Token);
    ASTInteger(Token, int);
    ~ASTInteger();
    virtual std::string inspect();
    virtual std::string toString();
    //virtual std::string hash();
};

class ASTString : public ASTNode {
public:
    std::string value;

    ASTString();
    ASTString(Token);
    ASTString(Token, std::string);
    ~ASTString();
    virtual std::string inspect();
    virtual std::string toString();
};

class ASTList : public ASTNode {
public:
    std::vector<ASTNode*> elements;

    ASTList();
    ASTList(Token);
    ASTList(Token, std::vector<ASTNode*>);
    ~ASTList();
    virtual std::string inspect();
    virtual std::string toString();
};

class ASTHash : public ASTNode {
public:
    std::unordered_map<ASTNode*, ASTNode*> pairs;

    ASTHash();
    ASTHash(Token);
    ASTHash(Token, std::unordered_map<ASTNode*, ASTNode*>);
    ~ASTHash();
    virtual std::string inspect();
    virtual std::string toString();
};

class ASTIndexExpression : public ASTNode {
public:
    ASTNode *left;
    ASTNode *index;
    ASTNode *indexEnd;
    ASTNode *step;

    ASTIndexExpression();
    ASTIndexExpression(Token);
    ASTIndexExpression(Token, ASTNode*);
    ~ASTIndexExpression();
    virtual std::string inspect();
    virtual std::string toString();
};

class ASTBoolean : public ASTNode {
public:
    bool value;

    ASTBoolean();
    ASTBoolean(Token);
    ASTBoolean(Token, bool);
    ~ASTBoolean();
    virtual std::string inspect();
    virtual std::string toString();
};

class ASTWhileStatement : public ASTNode {
public:

    ASTWhileStatement();
    ASTWhileStatement(Token);
    virtual std::string inspect();
    virtual std::string toString();
};

class ASTForStatement : public ASTNode {
public:

    //ASTForStatement();
    //ASTForStatement(Token);
    //virtual std::string inspect();
    //virtual std::string toString();
};

class ASTIfStatement : public ASTNode {
public:
    ASTNode *condition;
    ASTNode *consequence;
    ASTNode *alternative;

    ASTIfStatement();
    ASTIfStatement(Token);
    ~ASTIfStatement();
    virtual std::string inspect();
    virtual std::string toString();
};

class ASTBlockStatement : public ASTNode {
public:
    std::vector<ASTNode*> statements;

    ASTBlockStatement();
    ASTBlockStatement(Token);
    ~ASTBlockStatement();
    virtual std::string inspect();
    virtual std::string toString();
};

class ASTFunctionLiteral : public ASTNode {
public:
    Token token;
    std::vector<ASTNode*> parameters;
    std::vector<ASTNode*> default_params;
    ASTNode* body;

    ASTFunctionLiteral();
    ASTFunctionLiteral(Token);
    ~ASTFunctionLiteral();
    virtual std::string inspect();
    virtual std::string toString();
};

class ASTCallExpression : public ASTNode {
public:
    Token token;
    std::vector<ASTNode*> arguments;
    std::vector<ASTNode*> kw_args;
    ASTNode* function;

    ASTCallExpression();
    ASTCallExpression(Token);
    ASTCallExpression(Token, ASTNode*);
    ~ASTCallExpression();
    virtual std::string inspect();
    virtual std::string toString();
    virtual ASTNode* copy();
};

class ASTNullExpression : public ASTNode {
public:
    ASTNullExpression();
    virtual std::string inspect();
    virtual std::string toString();
};

void Ad_INCREF(ASTNode*);
void Ad_DECREF(ASTNode*);

void free_memory_ASTNode(ASTNode*);

#endif
