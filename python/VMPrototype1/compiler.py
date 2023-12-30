from ast import ASTNode, StatementType, statement_type_map
from bytecode import Bytecode
from instructions import Instructions


class Compiler:
    def __init__(self):
        self.instructions = None
        self.bytecode = None

    def reset(self):
        self.instructions = Instructions()
        self.bytecode = Bytecode()

    def compile(self, node: ASTNode):
        if node is None:
            print("severe error")
        elif node.statement_type == StatementType.PROGRAM:
            for stmt in node.statements:
                self.compile(stmt)
        else:
            print("severe error: node type unknown " + statement_type_map[node.statement_type])


    def bytecode(self):
        pass
