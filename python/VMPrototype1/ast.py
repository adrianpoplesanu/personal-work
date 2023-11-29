class ASTNode:
    pass


class ASTProgram(ASTNode):
    def __init__(self):
        self.statements = []

    def reset(self):
        self.statements = []


class AstExpressionStatement(ASTNode):
    def __init__(self, expression: ASTNode):
        self.expression = expression


class AstInteger(ASTNode):
    def __init__(self, value: int):
        self.value = value
