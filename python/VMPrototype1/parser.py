from typing import Optional

from ad_ast import ASTProgram, ASTNode, ASTExpressionStatement, ASTInteger, ASTInfixExpression, ASTPrefixExpression, \
    ASTBoolean, ASTIfExpression, ASTBlockStatement, ASTNullExpression, ASTLetStatement, ASTIdentifier, ASTString, \
    ASTList, ASTIndexExpression, ASTHash, ASTFunctionLiteral, ASTCallExpression, StatementType, ASTReturnStatement, \
    ASTClassStatement, ASTDefStatement, ASTAssignStatement, ASTWhileExpression, ASTMemberAccess, ASTThisExpression
from lexer import Lexer
from precedence_type import PrecedenceType, precedences
from token_type import TokenType


class Parser:
    def __init__(self):
        self.source = None
        self.lexer = Lexer()
        self.current_token = None
        self.peek_token = None
        self.statement_parse_fns = {
            TokenType.IF: self.parse_if_statement,
            TokenType.DEF: self.parse_def_statement
        }

        self.prefix_parse_fns = {
            TokenType.IDENT: self.parse_identifier,
            TokenType.INT: self.parse_integer_literal,
            TokenType.TRUE: self.parse_boolean,
            TokenType.FALSE: self.parse_boolean,
            TokenType.BANG: self.parse_prefix_expression,
            TokenType.MINUS: self.parse_prefix_expression,
            TokenType.LPAREN: self.parse_grouped_expression,
            TokenType.IF: self.parse_if_statement,
            TokenType.NULL: self.parse_null_expression,
            TokenType.STRING: self.parse_string_literal,
            TokenType.LBRACKET: self.parse_list_literal,
            TokenType.LBRACE: self.parse_hash_literal,
            TokenType.FUNC: self.parse_func_literal,
            TokenType.DEF: self.parse_def_statement,
            TokenType.CLASS: self.parse_class_statement,
            TokenType.WHILE: self.parse_while_expression,
            TokenType.THIS: self.parse_this_expression
        }

        self.infix_parse_fns = {
            TokenType.PLUS: self.parse_infix_expression,
            TokenType.MINUS: self.parse_infix_expression,
            TokenType.ASTERISK: self.parse_infix_expression,
            TokenType.SLASH: self.parse_infix_expression,
            TokenType.EQ: self.parse_infix_expression,
            TokenType.NOT_EQ: self.parse_infix_expression,
            TokenType.GT: self.parse_infix_expression,
            TokenType.LT: self.parse_infix_expression,
            TokenType.GTE: self.parse_infix_expression,
            TokenType.LTE: self.parse_infix_expression,
            TokenType.LBRACKET: self.parse_index_expression,
            TokenType.LPAREN: self.parse_call_expression,
            TokenType.ASSIGN: self.parse_assign_expression,
            TokenType.DOT: self.parse_member_access
        }

    def load(self, source):
        self.source = source
        self.lexer.load(source)
        self.next_token()
        self.next_token()

    def build_program_statements(self, program: ASTProgram):
        while self.current_token.token_type != TokenType.EOF:
            # print(self.current_token)
            stmt = self.parse_statement()
            if stmt:
                program.statements.append(stmt)
            self.next_token()

    def next_token(self):
        self.current_token = self.peek_token
        self.peek_token = self.lexer.next_token()

    def current_token_is(self, token_type : TokenType):
        return self.current_token.token_type == token_type

    def peek_token_is(self, token_type: TokenType):
        return self.peek_token.token_type == token_type

    def expect_peek(self, token_type: TokenType) -> bool:
        if self.peek_token_is(token_type):
            self.next_token()
            return True
        else:
            #self.errors.append('ERROR: i was expecting a different token here: ' + token_type)
            print('ERROR: i was expecting a different token here: ' + str(token_type))
            return False

    def peek_precedence(self):
        if self.peek_token.token_type in precedences:
            return precedences[self.peek_token.token_type]
        return PrecedenceType.LOWEST

    def current_precedence(self):
        if self.current_token.token_type in precedences:
            return precedences[self.current_token.token_type]
        return PrecedenceType.LOWEST

    def parse_statement(self) -> Optional[ASTNode]:
        #if self.current_token.token_type in self.statement_parse_fns:
        #    return self.statement_parse_fns[self.current_token.token_type]()
        if self.current_token.token_type == TokenType.LET:
            return self.parse_let_expression()
        if self.current_token.token_type == TokenType.RETURN:
            return self.parse_return_statement()
        return self.parse_expression_statement()

    def parse_identifier(self) -> ASTNode:
        stmt = ASTIdentifier(token=self.current_token, value=self.current_token.literal)
        return stmt

    def parse_integer_literal(self) -> ASTNode:
        stmt = ASTInteger(token=self.current_token, value=int(self.current_token.literal))
        return stmt

    def parse_boolean(self) -> ASTNode:
        stmt = ASTBoolean(token=self.current_token, value=bool(self.current_token.token_type == TokenType.TRUE))
        return stmt

    def parse_expression_statement(self) -> Optional[ASTNode]:
        stmt = ASTExpressionStatement(token=self.current_token)
        stmt.expression = self.parse_expression(PrecedenceType.LOWEST)
        if self.peek_token_is(TokenType.SEMICOLON):
            self.next_token()
        return stmt

    def parse_prefix_expression(self) -> ASTNode:
        expr = ASTPrefixExpression(token=self.current_token, operator=self.current_token.literal)
        self.next_token()
        expr.right = self.parse_expression(PrecedenceType.PREFIX)
        return expr

    def parse_grouped_expression(self) -> Optional[ASTNode]:
        self.next_token()
        expr = self.parse_expression(PrecedenceType.LOWEST)
        if not self.expect_peek(TokenType.RPAREN):
            return None
        return expr

    def parse_if_statement(self) -> Optional[ASTNode]:
        expr = ASTIfExpression(token=self.current_token)
        if not self.expect_peek(TokenType.LPAREN):
            return None
        self.next_token()
        expr.condition = self.parse_expression(PrecedenceType.LOWEST)
        if not self.expect_peek(TokenType.RPAREN):
            return None
        if not self.expect_peek(TokenType.LBRACE):
            expr.consequence = self.parse_single_block_statement()
        else:
            expr.consequence = self.parse_block_statement()
        if self.peek_token_is(TokenType.ELSE):
            self.next_token()
            if not self.expect_peek(TokenType.LBRACE):
                expr.alternative = self.parse_single_block_statement()
            else:
                expr.alternative = self.parse_block_statement()
        return expr

    def parse_block_statement(self):
        block = ASTBlockStatement(token=self.current_token)
        self.next_token()
        while (not self.current_token_is(TokenType.RBRACE)) and (not self.current_token_is(TokenType.EOF)):
            stmt = self.parse_statement()
            if stmt:
                block.statements.append(stmt)
            self.next_token()
        return block

    def parse_single_block_statement(self):
        block = ASTBlockStatement(token=self.current_token)
        self.next_token()
        stmt = self.parse_statement()
        block.statements.append(stmt)
        return block

    def parse_while_expression(self):
        expr = ASTWhileExpression(token=self.current_token)
        if not self.expect_peek(TokenType.LPAREN):
            return None
        self.next_token()
        expr.condition = self.parse_expression(PrecedenceType.LOWEST)
        if not self.expect_peek(TokenType.RPAREN):
            return None
        if not self.expect_peek(TokenType.LBRACE):
            expr.block = self.parse_single_block_statement()
        else:
            expr.block = self.parse_block_statement()
        return expr

    def parse_null_expression(self) -> ASTNode:
        expr = ASTNullExpression(token=self.current_token)
        self.next_token()
        return expr

    def parse_this_expression(self):
        expr = ASTThisExpression(token=self.current_token)
        return expr

    def parse_string_literal(self) -> ASTNode:
        return ASTString(token=self.current_token, value=str(self.current_token.literal))

    def parse_list_literal(self) -> ASTNode:
        expr = ASTList(self.current_token)
        expr.elements = self.parse_expression_list()
        return expr

    def parse_hash_literal(self) -> Optional[ASTNode]:
        node = ASTHash(token=self.current_token)
        node.pairs = {}
        while not self.peek_token_is(TokenType.RBRACE):
            self.next_token()
            key = self.parse_expression(PrecedenceType.LOWEST)
            if not self.expect_peek(TokenType.COLON):
                return None
            self.next_token()
            value = self.parse_expression(PrecedenceType.LOWEST)
            node.pairs[key] = value
            if not self.peek_token_is(TokenType.RBRACE) and not self.expect_peek(TokenType.COMMA):
                return None
        if not self.expect_peek(TokenType.RBRACE):
            return None
        return node

    def parse_expression_list(self):
        elements = []
        if self.peek_token_is(TokenType.RBRACKET):
            self.next_token()
            return elements
        self.next_token()
        elements.append(self.parse_expression(PrecedenceType.LOWEST))
        while self.peek_token_is(TokenType.COMMA):
            self.next_token()
            self.next_token()
            elements.append(self.parse_expression(PrecedenceType.LOWEST))
        if not self.expect_peek(TokenType.RBRACKET):
            return None
        return elements

    def parse_call_expression(self, left: ASTNode) -> Optional[ASTNode]:
        expr = ASTCallExpression(self.current_token, left)
        res = self.parse_call_arguments()
        expr.arguments = res[0]
        expr.kw_args = res[1]
        return expr

    def parse_call_arguments(self):
        args = []
        kw_args = []
        if self.peek_token_is(TokenType.RPAREN):
            self.next_token()
            return args, kw_args
        self.next_token()
        expr1 = self.parse_expression(PrecedenceType.LOWEST)
        if expr1.statement_type == StatementType.ASSIGN_STATEMENT:
            kw_args.append(expr1)
        else:
            args.append(expr1)
        while self.peek_token_is(TokenType.COMMA):
            self.next_token()
            self.next_token()
            if self.peek_token_is(TokenType.ASSIGN):
                kw_args.append(self.parse_expression(PrecedenceType.LOWEST))
            else:
                args.append(self.parse_expression(PrecedenceType.LOWEST))
        if not self.expect_peek(TokenType.RPAREN):
            return [], {}
        return args, kw_args

    def parse_index_expression(self, left: ASTNode) -> Optional[ASTNode]:
        expr = ASTIndexExpression(token=self.current_token, left=left)
        self.next_token()
        expr.index = self.parse_expression(PrecedenceType.LOWEST)
        if not self.expect_peek(TokenType.RBRACKET):
            return None
        return expr

    def parse_assign_expression(self, left: ASTNode) -> ASTNode:
        stmt = ASTAssignStatement(token=self.current_token)
        stmt.name = left
        self.next_token()
        stmt.value = self.parse_expression(PrecedenceType.LOWEST)
        if self.current_token_is(TokenType.SEMICOLON):
            self.next_token()
        return stmt

    def parse_member_access(self, left: ASTNode) -> ASTNode:
        member_access = ASTMemberAccess(token=self.current_token)
        self.next_token()
        right = ASTIdentifier(token=self.current_token, value=self.current_token.literal)
        member_access.owner = left
        member_access.member = right

        if self.peek_token_is(TokenType.LPAREN):
            self.next_token()
            res = self.parse_call_arguments()
            member_access.arguments = res[0]
            member_access.kw_args = res[1]
            member_access.is_method = True
        else:
            member_access.arguments = []
            member_access.kw_args = []
            member_access.is_method = False
        return member_access

    def parse_let_expression(self):
        stmt = ASTLetStatement(token=self.current_token)
        if not self.expect_peek(TokenType.IDENT):
            return None
        stmt.name = ASTIdentifier(token=self.current_token, value=self.current_token.literal)
        if not self.expect_peek(TokenType.ASSIGN):
            return None
        self.next_token()
        stmt.value = self.parse_expression(PrecedenceType.LOWEST)
        if stmt.value.statement_type == StatementType.FUNCTION_LITERAL:
            stmt.value.name = stmt.name.value
        if self.current_token_is(TokenType.SEMICOLON):
            self.next_token()
        return stmt

    def parse_func_literal(self):
        func = ASTFunctionLiteral(token=self.current_token)
        if not self.expect_peek(TokenType.LPAREN):
            return None
        res = self.parse_function_parameters()
        func.parameters, func.default_params = res[0], res[1]
        if not self.expect_peek(TokenType.LBRACE):
            return None
        func.body = self.parse_block_statement()
        return func

    def parse_def_statement(self):
        stmt = ASTDefStatement(token=self.current_token)
        self.next_token()
        name = ASTIdentifier(token=self.current_token, value=self.current_token.literal)
        stmt.name = name
        if not self.expect_peek(TokenType.LPAREN):
            # this should return an error object
            return None
        res = self.parse_function_parameters()
        stmt.parameters, stmt.default_params = res[0], res[1]
        if not self.expect_peek(TokenType.LBRACE):
            return None
        stmt.body = self.parse_block_statement()
        return stmt

    def parse_class_statement(self):
        expr = ASTClassStatement(token=self.current_token)
        self.next_token()
        name = self.parse_identifier()
        expr.name = name
        self.next_token()
        expr.attributes = []
        expr.methods = []
        expr.inherit_from = []

        if self.current_token_is(TokenType.COLON):
            self.next_token()
            while not self.current_token_is(TokenType.LBRACE):
                parent = self.parse_identifier()
                expr.inherit_from.append(parent)
                self.next_token()

        while not self.current_token_is(TokenType.RBRACE):
            if self.current_token_is(TokenType.DEF):
                stmt = self.parse_def_statement()
                expr.methods.append(stmt)
            if self.current_token_is(TokenType.FUN):
                stmt = self.parse_def_statement()
                expr.methods.append(stmt)
            if self.current_token_is(TokenType.METHOD):
                stmt = self.parse_def_statement()
                expr.methods.append(stmt)
            elif self.current_token_is(TokenType.IDENT):
                stmt = self.parse_expression_statement()
                expr.attributes.append(stmt)
            self.next_token()
        return expr

    def parse_function_parameters(self):
        identifiers = []
        default_params = []
        if self.peek_token_is(TokenType.RPAREN):
            self.next_token()
            return identifiers, default_params
        self.next_token()
        ident = ASTIdentifier(token=self.current_token, value=self.current_token.literal)
        identifiers.append(ident)
        if self.peek_token_is(TokenType.ASSIGN):
            self.next_token()
            self.next_token()
            value = self.parse_expression(PrecedenceType.LOWEST)
            default_params.append(value)
        while self.peek_token_is(TokenType.COMMA):
            self.next_token()
            self.next_token()
            ident = ASTIdentifier(token=self.current_token, value=self.current_token.literal)
            identifiers.append(ident)
            if self.peek_token_is(TokenType.ASSIGN):
                self.next_token()
                self.next_token()
                value = self.parse_expression(PrecedenceType.LOWEST)
                default_params.append(value)
            else:
                if len(default_params) > 0 and default_params[-1] is not None:
                    raise Exception("problem!!!")
                #default_params.append(None)
        if not self.expect_peek(TokenType.RPAREN):
            return [], []
        return identifiers, default_params

    def parse_return_statement(self):
        stmt = ASTReturnStatement(token=self.current_token)
        self.next_token()
        stmt.value = self.parse_expression(PrecedenceType.LOWEST)
        if self.peek_token_is(TokenType.SEMICOLON) or self.peek_token_is(TokenType.RBRACE) or self.peek_token_is(TokenType.EOF):
            return stmt
        while not self.current_token_is(TokenType.SEMICOLON) and not self.current_token_is(TokenType.RBRACE) and not self.current_token_is(TokenType.EOF):
            self.next_token()
        return stmt

    def parse_infix_expression(self, left: ASTNode) -> ASTNode:
        expr = ASTInfixExpression(token=self.current_token, operator=self.current_token.literal, left=left)
        precedence = self.current_precedence()
        self.next_token()
        expr.right = self.parse_expression(precedence)
        return expr

    def parse_expression(self, precedence) -> Optional[ASTNode]:
        if self.current_token.token_type not in self.prefix_parse_fns:
            return None
        prefix = self.prefix_parse_fns[self.current_token.token_type]
        left_exp: Optional[ASTNode] = prefix()
        while (not self.peek_token_is(TokenType.SEMICOLON)) and precedence < self.peek_precedence():
            if self.peek_token.token_type not in self.infix_parse_fns:
                return left_exp
            infix = self.infix_parse_fns[self.peek_token.token_type]
            self.next_token()
            left_exp = infix(left_exp)
        return left_exp
