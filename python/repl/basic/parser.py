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
        return 

    def parse_program(self):
        # this returns a program based on the source of the lexer
        # i shouldn't use this anymore
        pass

    def build_program_statements(self, program):
        # this returns a program based on the source of the lexer, this is better naming for this method
        while self.current_token.token_type != TokenType.EOF:
            statement = self.current_token
            program.statements.append(statement)
            self.next_token()

    def parse_statement(self):
        pass

    def parse_let_statement(self):
        pass

    def parse_return_statement(self):
        pass
