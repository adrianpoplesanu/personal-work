#include "compiler.h"

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
            OpPop opPop = OpPop();
            std::vector<int> args;
            emit(opPop, 0, args); // emmiting a pop when there's a parsing error is wrong
            break;
        }
        case AT_INFIX_EXPRESSION: {
            ASTInfixExpression *infixExpression = (ASTInfixExpression*) node;
            if (infixExpression->left == NULL || infixExpression->right == NULL) {
                std::cout << "error: null operand in infix expression\n";
                return;
            }

        if (infixExpression->_operator == ">") {
            compile(infixExpression->left);
            compile(infixExpression->right);
            OpGreaterThan opGreaterThan = OpGreaterThan();
            std::vector<int> args;
            emit(opGreaterThan, 0, args);
            return;
        }

            compile(infixExpression->left);
            compile(infixExpression->right);
            if (infixExpression->_operator == "+") {
                OpAdd opAdd = OpAdd();
                std::vector<int> args;
                emit(opAdd, 0, args);
            }
            if (infixExpression->_operator == "-") {
                OpMinus opMinus = OpMinus();
                std::vector<int> args;
                emit(opMinus, 0, args);
            }
            if (infixExpression->_operator == "*") {
                OpMultiply opMultiply = OpMultiply();
                std::vector<int> args;
                emit(opMultiply, 0, args);
            }
            if (infixExpression->_operator == "/") {
                OpDivide opDivide = OpDivide();
                std::vector<int> args;
                emit(opDivide, 0, args);
            }
            break;
        }
        case AT_PREFIX_EXPRESSION: {
            break;
        }
        case AT_INTEGER: {
            ASTInteger *integerExpr = (ASTInteger*) node;
            AdObjectInteger *integerObj = new AdObjectInteger(integerExpr->value);
            gc->addObject(integerObj);
            OpConstant opConstant = OpConstant();
            std::vector<int> args;
            args.push_back(addConstant(integerObj));
            emit(opConstant, 1, args);
            break;
        }
        case AT_BOOLEAN: {
            ASTBoolean *booleanExpr = (ASTBoolean*) node;
            if (booleanExpr->value) {
                OpTrue opTrue = OpTrue();
                std::vector<int> args;
                emit(opTrue, 0, args);
            } else {
                OpFalse opFalse = OpFalse();
                std::vector<int> args;
                emit(opFalse, 0, args);
            }
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

int Compiler::emit(OpCode opcode, int n, std::vector<int> &args) {
    int size;
    unsigned char *ins = code.make(opcode, n, args, size);
    int pos = addInstruction(size, ins);
    return pos;
}

int Compiler::addInstruction(int size, unsigned char *ins) {
    int posNewInstruction = size;
    for (int i = 0; i < size; i++) {
        instructions.add(ins[i]);
    }
    delete[] ins; // aici a mers delete-ul asta, dar ma intreb daca asta e momentul oportun sa sterg pointerii astia
    return posNewInstruction;
}

int Compiler::addConstant(AdObject* obj) {
    constants.push_back(obj);
    return constants.size() - 1;
}

Bytecode Compiler::getBytecode() {
    Bytecode bytecode;
    bytecode.instructions = instructions;
    bytecode.constants = constants;
    return bytecode;
}
