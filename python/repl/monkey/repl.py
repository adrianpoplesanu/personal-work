from lexer import Lexer
from lexer import TokenType


class Repl(object):
    def __init__(self, filename=None):
        self.lexer = Lexer()
        self.filename = filename

    def loop(self):
        if self.filename:
            data = open(self.filename, 'r').read()
            print data
            self.lexer.New(data)
            tok = self.lexer.nextToken()
            while tok.token_type != TokenType.EOF:
                print tok
                tok = self.lexer.nextToken()
        else:
            while True:
                line = raw_input('>> ')
                #self.lexer = Lexer(line)
                self.lexer.New(line)
                tok = self.lexer.nextToken()
                while tok.token_type != TokenType.EOF:
                    print tok
                    tok = self.lexer.nextToken()
