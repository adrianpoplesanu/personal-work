import sys

from compiler import Compiler
from parser import Parser
from ast import ASTProgram
from repl import Repl
from vm import VM


def main(args):
    filename = ''

    if len(args) == 1:
        filename = args[0]

    parser = Parser()
    program = ASTProgram()
    evaluator = None
    compiler = Compiler()
    vm = VM()
    repl = Repl(parser=parser, program=program, evaluator=evaluator, compiler=compiler, vm=vm)
    if filename:
        try:
            data = open(filename, "r")
        except FileNotFoundError as err:
            print("empty or missing ad source file")
            sys.exit(0)
        source = data.read()
        repl.execute_file(source=source)
    else:
        repl.loop()


if __name__ == '__main__':
    main(sys.argv[1:])
