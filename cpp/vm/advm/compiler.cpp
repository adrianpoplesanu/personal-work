#include "compiler.h"
#include <list>

Compiler::Compiler() {
    // ...
}

void Compiler::reset() {
    instructions = Instructions();
    bytecode = Bytecode();
}

void Compiler::compile(ASTNode* node) {
    if (node == NULL) {
        std::cout << "oops! severe error\n";
        return;
    }
    switch(node->type) {
        case AT_PROGRAM: {
            ASTProgram *program = (ASTProgram*) node;
            for (std::vector<ASTNode*>::iterator it = program->statements.begin() ; it != program->statements.end(); ++it) {
                compile(*it);
            }
            break;
        }
        case AT_EXPRESSION_STATEMENT: {
            ASTExpressionStatement *expressionStatement = (ASTExpressionStatement*) node;
            compile(expressionStatement->expression);
            break;
        }
        case AT_INFIX_EXPRESSION: {
            ASTInfixExpression *infixExpression = (ASTInfixExpression*) node;
            compile(infixExpression->left);
            compile(infixExpression->right);
            if (infixExpression->operand == "+") {
                OpAdd opAdd = OpAdd();
                std::list<int> args;
                emit(opAdd, 0, args);
            }
            break;
        }
        case AT_PREFIX_EXPRESSION: {
            break;
        }
        case AT_INTEGER: {
            ASTInteger *integerExpr = (ASTInteger*) node;
            AdObjectInteger *integerObj = new AdObjectInteger(integerExpr->value);
            OpConstant opConstant = OpConstant();
            std::list<int> args;
            args.push_back(addConstant(integerObj));
            emit(opConstant, 1, args);
            break;
        }
        case AT_IDENTIFIER: {
            break;
        }
        case AT_LET_STATEMENT: {
            break;
        }
        case AT_RETURN_STATEMENT: {
            break;
        }
        case AT_FUNCTION_STATEMENT: {
            break;
        }
        case AT_DEF_STATEMENT: {
            break;
        }
        case AT_WHILE_STATEMENT: {
            break;
        }
        case AT_FOR_STATEMENT: {
            break;
        }
        case AT_IF_STATEMENT: {
            break;
        }
    }
}

int Compiler::emit(OpCode opcode, int n, std::list<int> &args) {
    unsigned char *ins = code.make(opcode, n, args);
    int pos = addInstruction(ins);
    return pos;
}

int Compiler::addInstruction(unsigned char *ins) {
    return 0;
}

int Compiler::addConstant(AdObject* obj) {
    constants.push_back(obj);
    return constants.size() - 1;
}

Bytecode Compiler::getBytecode() {
    Bytecode bytecode;
    return bytecode;
}
