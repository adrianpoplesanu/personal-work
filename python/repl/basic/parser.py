class Parser(object):
    def __init__(self, lexer):
        self.lexer = lexer

    def parse_program(self):
        # this returns a program based on the source of the lexer
        # i shouldn't use this anymore
        pass

    def build_program_statements(self, program):
        # this returns a program based on the source of the lexer, this is better naming for this method
        pass

    def parse_statement(self):
        pass

    def parse_let_statement(self):
        pass

    def parse_return_statement(self):
        pass
