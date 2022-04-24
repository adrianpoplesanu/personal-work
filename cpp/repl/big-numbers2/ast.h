#ifndef __AST_H
#define __AST_H

#include <iostream>
#include <map>
#include <vector>
#include "big_number.h"
#include "token.h"

enum AstNodeType {
    AT_UNDEFINED,
    AT_PROGRAM,
    AT_BIGNUMBER,
    AT_PREFIX_EXPRESSION,
    AT_INFIX_EXPRESSION,
    AT_IDENTIFIER,
    AT_ASSIGN_STATEMENT,
    AT_IF_STATEMENT,
    AT_LET_STATEMENT
};

std::map<AstNodeType, std::string> ast_node_type_converter = {
    {AT_UNDEFINED, "AstUndefined"},
    {AT_PROGRAM, "AstProgram"},
    {AT_BIGNUMBER, "AstBigNumber"},
    {AT_PREFIX_EXPRESSION, "AstPrefixExpression"},
    {AT_INFIX_EXPRESSION, "AstInfixExpression"},
    {AT_IDENTIFIER, "AstIdentifier"},
    {AT_ASSIGN_STATEMENT, "AstAssignStatement"},
    {AT_IF_STATEMENT, "AstIfStatement"},
    {AT_LET_STATEMENT, "AstLetStatement"}
};

class AstNode {
    public:
        AstNodeType type;
        int ref_count;

        virtual std::string tokenLiteral();
        virtual std::string toString();
};

class AstProgram : AstNode {
    public:
        std::vector<AstNode*> statements;

        AstProgram();
        ~AstProgram();
        virtual std::string tokenLiteral();
        virtual std::string toString();
        void reset();
};

class AstExpressionStatement : AstNode {
    public:
        Token token;
        AstNode* expression;

        AstExpressionStatement();
        AstExpressionStatement(Token);
        ~AstExpressionStatement();
        virtual std::string tokenLiteral();
        virtual std::string toString();
};

class AstBigNumber : AstNode {
    public:
        Token token;
        BigNumber number;

        AstBigNumber();
        AstBigNumber(Token, BigNumber);
        ~AstBigNumber();
        virtual std::string tokenLiteral();
        virtual std::string toString();
};

#endif