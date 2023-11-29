from lexer import Lexer


class Parser:
    def __init__(self):
        self.source = None
        self.lexer = Lexer()

    def load(self, source):
        self.source = source
