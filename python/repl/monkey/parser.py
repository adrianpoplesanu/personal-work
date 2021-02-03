from ast import Program
from lexer import TokenType


class Parser(object):
    def __init__(self, lexer=None):
        self.lexer = lexer
        self.curToken = None
        self.peekToken = None

    def new(self, lexer=None):
        self.lexer = lexer # maybe don't do it like that
        self.nextToken()
        self.nextToken()

    def nextToken(self):
        self.curToken = self.peekToken
        self.peekToken = self.lexer.NextToken()

    def ParseProgram(self):
        program = Program()
        while self.curToken != TokenType.EOF:
            statement = self.parseStatement()
            if statement:
                program.statements.append(statement)
            self.nextToken()
        return program

    def parseStatement():
        pass
