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
        elif node.statement_type == StatementType.EXPRESSION_STATEMENT:
            self.compile(node.expression)
        elif node.statement_type == StatementType.INFIX_EXPRESSION:
            self.compile(node.left)
            self.compile(node.right)
            if node.operator == '+':
                pass
        elif node.statement_type == StatementType.INTEGER_LITERAL:
            pass
        else:
            print("severe error: node type unknown " + statement_type_map[node.statement_type])

    def emit(self) -> int:
        return 0

    def bytecode(self):
        pass
