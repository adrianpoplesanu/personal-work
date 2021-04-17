import signal
import sys
from lexer import Lexer
from lexer import TokenType
from parser import Parser
from ast import Program
from evaluator import Eval


def signal_ctrl_c_handler(sig, frame):
    print "\nleving repl, bye bye!"
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
            print data
            self.lexer.New(data)

            self.parser.new(self.lexer)
            self.program.reset()
            self.parser.ParseProgram(self.program)
            #print self.program
            print self.parser.errors
            #if self.parser.errors:
            #    print "ERRORS!!!"
            #    for error in self.parser.errors:
            #        print "\t" + error
            self.program.String()

            #tok = self.lexer.nextToken()
            #while tok.token_type != TokenType.EOF:
            #    print tok
            #    tok = self.lexer.nextToken()
        else:
            while True:
                line = raw_input('>> ')
                #self.lexer = Lexer(line)
                self.lexer.New(line)

                self.parser.new(self.lexer)
                self.program.reset()
                self.parser.ParseProgram(self.program)
                #print self.program
                #print self.parser.errors
                #self.program.String()
                evaluated = Eval(self.program)
                if evaluated:
                    #print evaluated.Inspect()
                    evaluated.Inspect()

                #tok = self.lexer.nextToken()
                #while tok.token_type != TokenType.EOF:
                #    print tok
                #    tok = self.lexer.nextToken()
