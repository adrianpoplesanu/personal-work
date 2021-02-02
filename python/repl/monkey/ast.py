class Node(object):
    def TokenLiteral(self):
        pass

class Statement(Node):
    def statementNode(self):
        pass

class Expression(Node):
    def expressionNode(self):
        pass

class Program(object):
    statements = []

    def TokenLiteral(self):
        if len(self.statements) > 0:
            return self.statements.TokenLiteral()
        else:
            return ''
