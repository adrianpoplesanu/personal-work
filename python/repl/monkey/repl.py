import signal
import sys
from lexer import Lexer
from lexer import TokenType


def signal_ctrl_c_handler(sig, frame):
    print "\nleving repl, bye bye!"
    sys.exit(0)


class Repl(object):
    def __init__(self, filename=None):
        self.lexer = Lexer()
        self.filename = filename

    def loop(self):
        signal.signal(signal.SIGINT, signal_ctrl_c_handler)
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
