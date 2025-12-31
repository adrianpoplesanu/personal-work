import sys

from compiler import Compiler
from opcode_ad import OpCodeByte, op_get_local, op_add, op_constant
from parser import Parser
from ad_ast import ASTProgram
from repl import Repl
from vm import VM


def main(args):
    parser = Parser()
    program = ASTProgram()
    evaluator = None
    compiler = Compiler()
    # START test compiler
    # result1 = compiler.emit(op_add, 0, [])
    # result2 = compiler.emit(op_get_local, 1, [255])
    # result3 = compiler.emit(op_constant, 1, [2])
    # result4 = compiler.emit(op_constant, 1, [65535])
    # print(result1)
    # print(result2)
    # print(result3)
    # print(result4)
    # bytecode = compiler.get_bytecode()
    # compiler.code.instructions = bytecode.instructions
    # compiler.code.instructions.size = len(bytecode.instructions.bytes)
    # print(compiler.code.to_string(), end='')
    # STOP test compiler
    vm = VM()
    repl = Repl(parser=parser, program=program, evaluator=evaluator, compiler=compiler, vm=vm)
    if len(args) > 0:
        for filename in args:
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
