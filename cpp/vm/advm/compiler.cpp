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
        std::cout << "severe error: node is null\n";
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

            if (infixExpression->_operator == "<") {
                compile(infixExpression->right);
                compile(infixExpression->left);
                OpGreaterThan opGreaterThan = OpGreaterThan();
                std::vector<int> args;
                emit(opGreaterThan, 0, args);
                return;
            }

            if (infixExpression->_operator == "<=") {
                compile(infixExpression->right);
                compile(infixExpression->left);
                OpGreaterThanEquals opGreaterThanEquals = OpGreaterThanEquals();
                std::vector<int> args;
                emit(opGreaterThanEquals, 0, args);
                return;
            }

            if (infixExpression->_operator == "==") {
                compile(infixExpression->left);
                compile(infixExpression->right);
                OpEquals opEquals = OpEquals();
                std::vector<int> args;
                emit(opEquals, 0, args);
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
                OpSub opSub = OpSub();
                std::vector<int> args;
                emit(opSub, 0, args);
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
            if (infixExpression->_operator == ">") {
                OpGreaterThan opGreaterThan = OpGreaterThan();
                std::vector<int> args;
                emit(opGreaterThan, 0, args);
            }
            if (infixExpression->_operator == ">=") {
                OpGreaterThanEquals opGreaterThanEquals = OpGreaterThanEquals();
                std::vector<int> args;
                emit(opGreaterThanEquals, 0, args);
            }
            break;
        }
        case AT_PREFIX_EXPRESSION: {
            ASTPrefixExpression *stmt = (ASTPrefixExpression*) node;
            compile(stmt->right);
            if (stmt->_operator == "!") {
                OpBang opBang;
                std::vector<int> args;
                emit(opBang, 0, args);
            }
            if (stmt->_operator == "-") {
                OpMinus opMinus;
                std::vector<int> args;
                emit(opMinus, 0, args);
            }
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
            ASTIfStatement *stmt = (ASTIfStatement*) node;
            compile(stmt->condition);
            OpJumpNotTruthy opJumpNotTruthy = OpJumpNotTruthy();
            std::vector<int> args;
            // bogus 9999 value
            args.push_back(9999);
            int jump_not_truthy_pos = emit(opJumpNotTruthy, 1, args);

            compile(stmt->consequence);

            if (isLastInstructionPop()) {
                removeLastInstruction();
            }

            int after_consequence_pos = instructions.size;
            changeOperand(jump_not_truthy_pos, after_consequence_pos);

            break;
        }
        case AT_BLOCK_STATEMENT: {
            ASTBlockStatement *stmt = (ASTBlockStatement*) node;
            for (auto& it : stmt->statements) {
                compile(it);
            }
            break;
        }
        default: {
            std::cout << "ERROR: unhndled ast type compiled\n";
            break;
        }
    }
}

int Compiler::emit(OpCode opcode, int n, std::vector<int> &args) {
    int size;
    unsigned char *ins = code.make(opcode, n, args, size);
    int pos = addInstruction(size, ins);
    delete[] ins; // am mutat asta din addInstruction aici pentru ca aici se primeste adresa, aici e responsabilitatea de dezalocare
    setLastInstruction(opcode, pos);
    return pos;
}

int Compiler::addInstruction(int size, unsigned char *ins) {
    int posNewInstruction = instructions.size;
    for (int i = 0; i < size; i++) {
        instructions.add(ins[i]);
    }
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

void Compiler::setLastInstruction(OpCode opcode, int pos) {
    EmittedInstruction previous = lastInstruction;
    EmittedInstruction last = EmittedInstruction(opcode, pos);

    previousInstruction = previous;
    lastInstruction = last;
}

bool Compiler::isLastInstructionPop() {
    return lastInstruction.opcode.byteCode == OP_POP;
}

void Compiler::removeLastInstruction() {
    instructions.removeLast();
    lastInstruction = previousInstruction;
}

void Compiler::replaceInstruction(int pos, unsigned char *new_instruction, int size) {
    for (int i = 0; i < size; i++) {
        instructions.bytes[pos + i] = new_instruction[i];
    }
}

void Compiler::changeOperand(int opPos, int operand) {
    OpCode op = OpCode();
    op.byteCode = static_cast<OpCodeByte>(instructions.bytes[opPos]);
    int size;
    std::vector<int> args;
    args.push_back(operand);
    unsigned char * new_instruction = code.make(op, 1, args, size);
    replaceInstruction(opPos, new_instruction, size);
}
