class Parser(object):
    def __init__(self, lexer=None)
        self.lexer = lexer
        self.curToken = None
        self.peekToken = None

    def new(self, lexer=None):
        self.lexer = lexer # maybe don't do it like that
        self.nextToken()
        self.nextToken()

    def.nextToken(self):
        self.curToken = self.peekToken
        self.peekToken = self.lexer.NextToken()

    def ParseProgram(self):
        pass
