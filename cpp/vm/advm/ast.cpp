#include "ast.h"

std::string ASTNode::toString() {
    return "unimplemented in subclass";
}

std::string ASTNode::hash() {
    return "unimplemented in subclass";
}

std::string ASTNode::inspect() {
    return "unimplemented in subclass";
}

ASTProgram::ASTProgram() {
    type = AT_PROGRAM;
    ref_count = 0;
}

ASTProgram::~ASTProgram() {
    for(std::vector<ASTNode*>::iterator it = statements.begin() ; it != statements.end(); ++it) {
        ASTNode *node = *it;
        free_memory_ASTNode(node);
    }
}

void ASTProgram::reset() {
    for(std::vector<ASTNode*>::iterator it = statements.begin() ; it != statements.end(); ++it) {
        ASTNode *node = *it;
        free_memory_ASTNode(node);
    }
    statements.clear();
}

std::string ASTProgram::toString() {
    std::string out = "";
    out += "AstProgram\n";
    for (ASTNode* it : statements) {
        out += it->toString();
    }
    return out;
}

std::string ASTProgram::inspect() {
    return "AstProgram\n";
}

ASTExpressionStatement::ASTExpressionStatement() {
    type = AT_EXPRESSION_STATEMENT;
    ref_count = 0;
}

ASTExpressionStatement::ASTExpressionStatement(Token t) {
    type = AT_EXPRESSION_STATEMENT;
    ref_count = 0;
    token = t;
}

ASTExpressionStatement::ASTExpressionStatement(Token t, ASTNode* e) {
    type = AT_EXPRESSION_STATEMENT;
    ref_count = 0;
    token = t;
    expression = e;
}

ASTExpressionStatement::~ASTExpressionStatement() {
    free_memory_ASTNode(expression);
}

std::string ASTExpressionStatement::toString() {
    if (expression == NULL) {
        return "ASTExpressionStatement[None]\n";
    }
    return "ASTExpressionStatement[" + expression->toString() + "]\n";
}

std::string ASTExpressionStatement::inspect() {
    return "ASTExpressionStatement";
}

ASTInfixExpression::ASTInfixExpression() {
    type = AT_INFIX_EXPRESSION;
    ref_count = 0;
}

ASTInfixExpression::ASTInfixExpression(Token t) {
    type = AT_INFIX_EXPRESSION;
    ref_count = 0;
    token = t;
}

ASTInfixExpression::ASTInfixExpression(Token t, ASTNode* l, ASTNode* r, std::string op) {
    type = AT_INFIX_EXPRESSION;
    ref_count = 0;
    token = t;
    left = l;
    right = r;
    _operator = op;
}

ASTInfixExpression::~ASTInfixExpression() {
    free_memory_ASTNode(left);
    free_memory_ASTNode(right);
}

std::string ASTInfixExpression::toString() {
    return "ASTInfixExpression";
}

std::string ASTInfixExpression::inspect() {
    return "ASTInfixExpression";
}

ASTIdentifier::ASTIdentifier() {
    type = AT_IDENTIFIER;
    ref_count = 0;
}

ASTIdentifier::ASTIdentifier(Token t, std::string val) {
    type = AT_IDENTIFIER;
    ref_count = 0;
    token = t;
    value = val;
}

std::string ASTIdentifier::toString() {
    return "ASTIdentifier[" + token.stringLiteral + "]";
}

std::string ASTIdentifier::inspect() {
    return "ASTIdentifier";
}

ASTWhileStatement::ASTWhileStatement() {

}

ASTWhileStatement::ASTWhileStatement(Token t) {

}

std::string ASTWhileStatement::inspect() {
    return "todo: implement this";
}

std::string ASTWhileStatement::toString() {
    return "todo: implement this";
}

ASTInteger::ASTInteger() {
    type = AT_INTEGER;
    ref_count = 0;
}

ASTInteger::ASTInteger(Token t) {
    type = AT_INTEGER;
    ref_count = 0;
    token = t;
}

ASTInteger::ASTInteger(Token t, int v) {
    type = AT_INTEGER;
    ref_count = 0;
    token = t;
    value = v;
}

ASTInteger::~ASTInteger() {
    //...
}

std::string ASTInteger::toString() {
    return "ASTInteger[" + std::to_string(value) + "]";
}

std::string ASTInteger::inspect() {
    return "ASTInteger";
}

/*std::string ASTInteger::hash() {
    return "test";
}*/

ASTPrefixExpression::ASTPrefixExpression(Token t, std::string o) {
    type = AT_PREFIX_EXPRESSION;
    ref_count = 0;
    token = t;
    _operator = o;
}

ASTPrefixExpression::~ASTPrefixExpression() {
    free_memory_ASTNode(right);
}

ASTBoolean::ASTBoolean() {
    type = AT_BOOLEAN;
    ref_count = 0;
}

ASTBoolean::ASTBoolean(Token t) {
    type = AT_BOOLEAN;
    ref_count = 0;
    token = t;
}

ASTBoolean::ASTBoolean(Token t, bool v) {
    type = AT_BOOLEAN;
    ref_count = 0;
    token = t;
    value = v;
}

ASTBoolean::~ASTBoolean() {
    //...
}

std::string ASTBoolean::toString() {
    return "ASTBoolean";
}

std::string ASTBoolean::inspect() {
    return "ASTBoolean";
}

ASTIfStatement::ASTIfStatement() {
    type = AT_IF_STATEMENT;
    ref_count = 0;
    condition = nullptr;
    consequence = nullptr;
    alternative = nullptr;
}

ASTIfStatement::ASTIfStatement(Token t) {
    type = AT_IF_STATEMENT;
    ref_count = 0;
    token = t;
    condition = nullptr;
    consequence = nullptr;
    alternative = nullptr;
}

ASTIfStatement::~ASTIfStatement() {
    free_memory_ASTNode(condition);
    free_memory_ASTNode(consequence);
    free_memory_ASTNode(alternative);
}

std::string ASTIfStatement::inspect() {
    return "todo: implement this";
}

std::string ASTIfStatement::toString() {
    return "ASTIfExpression";
}

ASTBlockStatement::ASTBlockStatement() {
    type = AT_BLOCK_STATEMENT;
    ref_count = 0;
}

ASTBlockStatement::ASTBlockStatement(Token t) {
    type = AT_BLOCK_STATEMENT;
    ref_count = 0;
    token = t;
}

ASTBlockStatement::~ASTBlockStatement() {
    for (auto& it : statements) {
        free_memory_ASTNode(it);
    }
}

std::string ASTBlockStatement::inspect() {
    std::string out = "{";
    for (auto& it : statements) {
        out += it->inspect();
    }
    out += "}";
    return out;
}

std::string ASTBlockStatement::toString() {
    std::string out = "{";
    for (auto& it : statements) {
        out += it->inspect();
    }
    out += "}";
    return out;
}

ASTNullExpression::ASTNullExpression() {
    type = AT_NULL_EXPRESSION;
    ref_count = 0;
}

std::string ASTNullExpression::inspect() {
    return "ASTNullExpression";
}

std::string ASTNullExpression::toString() {
    return "ASTNullExpression";
}

ASTLetStatement::ASTLetStatement() {
    type = AT_LET_STATEMENT;
    ref_count = 0;
}

ASTLetStatement::ASTLetStatement(Token t) {
    type = AT_LET_STATEMENT;
    ref_count = 0;
    token = t;
}

ASTLetStatement::~ASTLetStatement() {
    if (value) {
        free_memory_ASTNode(value);
    }
}

std::string ASTLetStatement::inspect() {
    return "ASTLetStatement";
}

std::string ASTLetStatement::toString() {
    return "ASTLetStatement<" + name.toString() + "> [" + value->toString() + "]\n";
}

ASTReturnStatement::ASTReturnStatement() {
    type = AT_RETURN_STATEMENT;
    ref_count = 0;
}

ASTReturnStatement::ASTReturnStatement(Token t) {
    type = AT_RETURN_STATEMENT;
    ref_count = 0;
    token = t;
}

ASTReturnStatement::~ASTReturnStatement() {
    //...
}

std::string ASTReturnStatement::inspect() {
    return "todo: implement ASTReturnStatement.inspect()";
}

std::string ASTReturnStatement::toString() {
    return "todo: implement ASTReturnStatement.toString()";
}

ASTString::ASTString() {
    type = AT_STRING_LITERAL;
    ref_count = 0;
}

ASTString::ASTString(Token t) {
    type = AT_STRING_LITERAL;
    ref_count = 0;
    token = t;
}

ASTString::ASTString(Token t, std::string v) {
    type = AT_STRING_LITERAL;
    ref_count = 0;
    token = t;
    value = v;
}

ASTString::~ASTString() {
    //...
}

std::string ASTString::inspect() {
    return "ASTString.inspect()";
}

std::string ASTString::toString() {
    return "ASTString[" + value + "]";
}

ASTList::ASTList() {
    type = AT_LIST_LITERAL;
    ref_count = 0;
}

ASTList::ASTList(Token t) {
    type = AT_LIST_LITERAL;
    ref_count = 0;
    token = t;
}

ASTList::ASTList(Token t, std::vector<ASTNode*> e) {
    type = AT_LIST_LITERAL;
    ref_count = 0;
    token = t;
    elements = e;
}

ASTList::~ASTList() {
    for (auto& it : elements) {
        free_memory_ASTNode(it);
    }
}

std::string ASTList::inspect() {
    return "ASTList.inspect()";
}

std::string ASTList::toString() {
    std::string out = "ASTList[";
    int i = 0, size = elements.size();
    for (auto el : elements) {
        if (i < size - 1) {
            out += el->inspect() + ", ";
        } else {
            out += el->inspect();
        }
        ++i;
    }
    out += "]";
    return out;
}

ASTIndexExpression::ASTIndexExpression() {
    type = AT_INDEX_EXPRESSION;
    ref_count = 0;
}

ASTIndexExpression::ASTIndexExpression(Token t) {
    type = AT_INDEX_EXPRESSION;
    ref_count = 0;
    token = t;
}

ASTIndexExpression::ASTIndexExpression(Token t, ASTNode *l) {
    type = AT_INDEX_EXPRESSION;
    ref_count = 0;
    token = t;
    left = l;
}

ASTIndexExpression::~ASTIndexExpression() {
    //...
}

std::string ASTIndexExpression::inspect() {
    return "ASTIndexExpression.inspect()";
}

std::string ASTIndexExpression::toString() {
    std::string out = "ASTIndexExpression[";
    out += "<" + left->toString() + ">";
    out += "<" + index->toString() + ">";
    if (indexEnd) {
        out += "<" + indexEnd->toString() + ">";
    }
    if (step) {
        out += "<" + step->toString() + ">";
    }
    out += "]";
    return out;
}

ASTHash::ASTHash() {
    type = AT_HASH_LITERAL;
    ref_count = 0;
}

ASTHash::ASTHash(Token t) {
    type = AT_HASH_LITERAL;
    ref_count = 0;
    token = t;
}

ASTHash::ASTHash(Token t, std::unordered_map<ASTNode*, ASTNode*> p) {
    type = AT_HASH_LITERAL;
    ref_count = 0;
    token = t;
    pairs = p;
}

ASTHash::~ASTHash() {
    for (auto& it : pairs) {
        free_memory_ASTNode(it.first);
        free_memory_ASTNode(it.second);
    }
}

std::string ASTHash::inspect() {
    return "TODO: implement ASTHash.inspect()";
}

std::string ASTHash::toString() {
    std::string out = "ASTHashLiteral[";
    for (auto& it: pairs) {
        out += "<" + it.first->toString() + ": " + it.second->toString() + ">";
    }
    out += "]";
    return out;
}

ASTFunctionLiteral::ASTFunctionLiteral() {
    type = AT_FUNCTION_LITERAL;
    ref_count = 0; // poate aici ar trebui sa fie 1
}

ASTFunctionLiteral::ASTFunctionLiteral(Token t) {
    type = AT_FUNCTION_LITERAL;
    ref_count = 0; // poate aici ar trebui sa fie 1
    token = t;
}

ASTFunctionLiteral::~ASTFunctionLiteral() {
    if (body) {
        Ad_DECREF(body); // asta merge si e super cool
        free_memory_ASTNode(body);
    }
    for (std::vector<ASTNode*>::iterator it = parameters.begin() ; it != parameters.end(); ++it) {
        ASTNode *node = *it;
        Ad_DECREF(node); // asta merge si e super cool
        free_memory_ASTNode(node);
    }
    for (std::vector<ASTNode*>::iterator it = default_params.begin() ; it != default_params.end(); ++it) {
        ASTNode *node = *it;
        Ad_DECREF(node); // asta merge si e super cool
        free_memory_ASTNode(node);
    }
}

std::string ASTFunctionLiteral::inspect() {
    return "TODO: implement ASTFunctionLiteral.inspect()";
}

std::string ASTFunctionLiteral::toString() {
    std::string out = "[FunctionLiteral] <";
    for (std::vector<ASTNode*>::iterator it = parameters.begin() ; it != parameters.end(); ++it) {
        ASTNode *current = *it;
        if (it != parameters.begin()) out += ", ";
        out += current->toString();
    }
    out += "><";
    out += body->toString();
    out += ">";
    return out;
}

ASTCallExpression::ASTCallExpression() {
    type = AT_CALL_EXPRESSION;
}

ASTCallExpression::ASTCallExpression(Token t) {
    type = AT_CALL_EXPRESSION;
    token = t;
}

ASTCallExpression::ASTCallExpression(Token t, ASTNode* f) {
    type = AT_CALL_EXPRESSION;
    token = t;
    function = f;
}

ASTCallExpression::~ASTCallExpression() {
    free_memory_ASTNode(function);
    for (std::vector<ASTNode*>::iterator it = arguments.begin() ; it != arguments.end(); ++it) {
        ASTNode *node = *it;
        free_memory_ASTNode(node);
    }
    for (std::vector<ASTNode*>::iterator it = kw_args.begin() ; it != kw_args.end(); ++it) {
        ASTNode *node = *it;
        free_memory_ASTNode(node);
    }
}

std::string ASTCallExpression::inspect() {
    return "todo: implement ASTCallExpression.inspect()";
}

std::string ASTCallExpression::toString() {
    return "todo: implement ASTCallExpression.toString()";
}

ASTNode* ASTCallExpression::copy() {
    return nullptr;
}

void Ad_INCREF(ASTNode* node) {
    if (node) {
        node->ref_count++;
    }
}

void Ad_DECREF(ASTNode* node) {
    if (node) {
        node->ref_count--;
    }
}

void free_memory_ASTNode(ASTNode* node) {
    if (node == NULL) return;
    if (node->ref_count > 0) return;
    switch(node->type)  {
        case AT_PROGRAM: {
            delete (ASTProgram*) node;
            break;
        }
        case AT_EXPRESSION_STATEMENT: {
            delete (ASTExpressionStatement*) node;
            break;
        }
        case AT_IDENTIFIER: {
            delete (ASTIdentifier*) node;
            break;
        }
        case AT_INTEGER: {
            delete (ASTInteger*) node;
            break;
        }
        case AT_BOOLEAN: {
            delete (ASTBoolean*) node;
            break;
        }
        case AT_INFIX_EXPRESSION: {
            delete (ASTInfixExpression*) node;
            break;
        }
        case AT_PREFIX_EXPRESSION: {
            delete (ASTPrefixExpression*) node;
            break;
        }
        case AT_LET_STATEMENT: {
            delete (ASTLetStatement*) node;
            break;
        }
        case AT_RETURN_STATEMENT: {
            delete (ASTReturnStatement*) node;
            break;
        }
        case AT_FUNCTION_STATEMENT: {
            delete (ASTFunctionStatement*) node;
            break;
        }
        case AT_DEF_STATEMENT: {
            delete (ASTDefStatement*) node;
            break;
        }
        case AT_WHILE_STATEMENT: {
            delete (ASTWhileStatement*) node;
            break;
        }
        case AT_FOR_STATEMENT: {
            delete (ASTForStatement*) node;
            break;
        }
        case AT_IF_STATEMENT: {
            delete (ASTIfStatement*) node;
            break;
        }
        case AT_BLOCK_STATEMENT: {
            delete (ASTBlockStatement*) node;
            break;
        }
        case AT_NULL_EXPRESSION: {
            delete (ASTNullExpression*) node;
            break;
        }
        case AT_STRING_LITERAL: {
            delete (ASTString*) node;
            break;
        }
        case AT_LIST_LITERAL: {
            delete (ASTList*) node;
            break;
        }
        case AT_HASH_LITERAL: {
            delete (ASTHash*) node;
            break;
        }
        case AT_INDEX_EXPRESSION: {
            delete (ASTIndexExpression*) node;
            break;
        }
        case AT_FUNCTION_LITERAL: {
            delete (ASTFunctionLiteral*) node;
            break;
        }
        case AT_CALL_EXPRESSION: {
            delete (ASTCallExpression*) node;
            break;
        }
        default: {
            std::cout << "SEVERE MEMORY ERROR: " << ast_type_map[node->type] << "!!!\n";
            break;
        }
    }
}