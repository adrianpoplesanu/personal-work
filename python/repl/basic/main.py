from repl import Repl
from lexer import Lexer
from parser import Parser
from ast import Program
from token_type import TokenType


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
        while tok.token_type != TokenType.EOF:
            print tok
            tok = self.lexer.next_token()


if __name__ == '__main__':
    #interpreter = EchoInterpreter()
    lexer = Lexer()
    parser = Parser(lexer)
    program = Program()
    interpreter = BasicInterpreter(lexer=lexer, parser=parser)
    repl = Repl(interpreter=interpreter, program=program)
    repl.loop()
