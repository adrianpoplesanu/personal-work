from ast import Program, LetStatement, ReturnStatement, ExpressionStatement, \
                PrefixExpression, InfixExpression, Boolean, IfExpression, \
                BlockStatement, FunctionLiteral, CallExpression, Identifier, \
                IntegerLiteral, Statement, Expression

def print_level(level):
    if level:
        print ' ' * (level - 1),

def print_ast_node(node, level):
    if type(node) == Program:
        print_level(level)
        print 'Program'
        for stmt in node.statements:
            print_ast_node(stmt, level + 2)
    elif type(node) == LetStatement:
        print_level(level)
        print '->LetStatement ' + str(node.token) + ' ' + str(node.name.token)
        print_ast_node(node.value, level + 2)
    elif type(node) == ReturnStatement:
        print_level(level)
        print '->ReturnStatement ' + str(node.token)
    elif type(node) == ExpressionStatement:
        print_level(level)
        print '->ExpressionStatement ' + str(node.token)
    elif type(node) == PrefixExpression:
        print_level(level)
        print '->PrefixExpression ' + str(node.token)
    elif type(node) == InfixExpression:
        print_level(level)
        print '->InfixExpression ' + str(node.token)
    elif type(node) == Boolean:
        print_level(level)
        print '->Boolean ' + str(node.token)
    elif type(node) == IfExpression:
        print_level(level)
        print '->IfExpression ' + str(node.token)
    elif type(node) == BlockStatement:
        print_level(level)
        print '->BlockStatement ' + str(node.token)
    elif type(node) == FunctionLiteral:
        print_level(level)
        print '->FunctionLiteral ' + str(node.token)
    elif type(node) == CallExpression:
        print_level(level)
        print '->CallExpression ' + str(node.token)
    elif type(node) == Identifier:
        print_level(level)
        print '->Identifier ' + str(node.token)
    elif type(node) == IntegerLiteral:
        print_level(level)
        print '->IntegerLiteral ' + str(node.token)
    elif type(node) == Statement:
        print_level(level)
        print '->Statement'
    elif type(node) == Expression:
        print_level(level)
        print '->Expression'
    else:
        pass
