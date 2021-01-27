from lexer import Lexer
from lexer import TokenType


class Repl(object):
    def __init__(self):
        self.lexer = Lexer()
        #self.lexer = None

    def loop(self):
        while True:
            line = raw_input('>> ')
            #self.lexer = Lexer(line)
            self.lexer.New(line)
            tok = self.lexer.nextToken()
            while tok.token_type != TokenType.EOF:
                print tok
                tok = self.lexer.nextToken()
            #lexing = True
            #while lexing:
            #    tok = self.lexer.nextToken(line[0])
            #    print tok
            #    if tok.token_type == TokenType.EOF:
            #        lexing = False
            #print self.lexer.nextToken(line[0])
