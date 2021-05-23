import signal
import sys
from lexer import Lexer
from lexer import TokenType
from parser import Parser
from ast import Program
from evaluator import Eval
from environment import NewEnvironment


def signal_ctrl_c_handler(sig, frame):
    print "\nleaving repl, bye bye!"
    sys.exit(0)


class Repl(object):
    def __init__(self, filename=None):
        self.lexer = Lexer()
        self.filename = filename
        self.parser = Parser()
        self.program = Program()

    def loop(self):
        signal.signal(signal.SIGINT, signal_ctrl_c_handler)
        if self.filename:
            data = open(self.filename, 'r').read()
            self.lexer.New(data)

            self.parser.new(self.lexer)
            self.program.reset()
            self.parser.ParseProgram(self.program)
            env = NewEnvironment()
            evaluated = Eval(self.program, env)
            if evaluated:
                evaluated.Inspect() # this prints only the last evaluation, i need to find a way to print all evaluations
        else:
            env = NewEnvironment()
            while True:
                line = raw_input('>> ')
                self.lexer.New(line)

                self.parser.new(self.lexer)
                self.program.reset()
                self.parser.ParseProgram(self.program)
                evaluated = Eval(self.program, env)
                if evaluated:
                    evaluated.Inspect()

