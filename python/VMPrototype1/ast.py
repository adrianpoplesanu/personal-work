class ASTNode:
    pass


class ASTProgram(ASTNode):
    def __init__(self):
        self.statements = []

    def reset(self):
        self.statements = []


class AstExpressionStatement(ASTNode):
    pass
