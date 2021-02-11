from repl import Repl
from lexer import Lexer


class EchoInterpreter(object):
    def __init__(self):
        pass
    def execute(self, line):
        print line


class BasicInterpreter(object):
    def __init__(self, lexer=None, parser=None):
        self.lexer = lexer
        self.parser = parser

    def execute(self, line):
        self.lexer.new(source=line)
        tok = self.lexer.next_token()
        #while tok.token_type != TokenType.EOF:
        #    print tok
        #    tok = self.lexer.next_token()


if __name__ == '__main__':
    #interpreter = EchoInterpreter()
    lexer = Lexer()
    interpreter = BasicInterpreter(lexer=lexer)
    repl = Repl(interpreter=interpreter)
    repl.loop()
