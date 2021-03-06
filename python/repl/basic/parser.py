from token_type import TokenType


class Parser(object):
    def __init__(self, lexer):
        self.lexer = lexer
        self.current_token = None
        self.peek_token = None

    def reset(self, source):
        self.lexer.new(source=source)
        self.next_token()
        self.next_token()

    def next_token(self):
        self.current_token = self.peek_token
        self.peek_token = self.lexer.next_token()

    def current_token_is(self, token_type):
        return self.current_token.token_type == token_type

    def peek_token_is(self, token_type):
        return self.peek_token.token_type == token_type

    def expect_token(self, token_type):
        if self.peek_token_is(token_type):
            self.next_token()
            return True
        return False

    def parse_program(self):
        # this returns a program based on the source of the lexer
        # i shouldn't use this anymore
        pass

    def build_program_statements(self, program):
        # this returns a program based on the source of the lexer, this is better naming for this method
        while self.current_token.token_type != TokenType.EOF:
            statement = self.parse_statement()
            if statement:
                program.statements.append(statement)
            self.next_token()

    def parse_statement(self):
        if self.current_token.token_type == TokenType.LET:
            self.parse_let_statement()
        if self.current_token.token_type == TokenType.RETURN:
            self.parse_return_statement()
        return self.current_token

    def parse_let_statement(self):
        pass

    def parse_return_statement(self):
        pass

    def parse_expression_statement(self):
        pass
