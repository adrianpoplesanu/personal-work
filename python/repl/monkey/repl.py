from lexer import Lexer

class Repl(object):
    def __init__(self):
        #self.lexer = Lexer()
        self.lexer = None

    def loop(self):
        while True:
            line = raw_input('>> ')
            self.lexer = Lexer(line)
            print self.lexer.nextToken(line[0])
