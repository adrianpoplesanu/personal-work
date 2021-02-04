from ast import Program
from ast import LetStatement
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

    def parseStatement(self):
        if self.curToken.token_type == TokenType.LET:
            return self.parseLetStatement()
        else:
            return None

    def parseLetStatement(self):
        stamement = LetStatement(self.curToken)
        if not self.expectPeek(TokenType.IDENT):
            return None
        statement.Name = Identifier(self.curToken, self.curToken.literal)
        if not self.expectPeek(TokenType.ASSIGN):
            return None
        while not self.curTokenIs(TokenType.SEMICOLON):
            self.nextToken()
        return statement

    def curTokenIs(self, token_type):
        return self.curToken.token_type == token_type

    def peekTokenIs(self, token_type):
        return self.peekToken.token_type == token_type

    def expectPeek(self, token_type):
        if self.peekTokenIs(token_type):
            self.nextToken()
            return true
        else:
            return false
