from ast import Program
from ast import LetStatement
from ast import ReturnStatement
from ast import Identifier
from lexer import TokenType


class Parser(object):
    def __init__(self, lexer=None):
        self.lexer = lexer
        self.curToken = None
        self.peekToken = None
        #self.nextToken()
        #self.nextToken()

    def new(self, lexer=None):
        self.lexer = lexer # maybe don't do it like that
        self.nextToken()
        self.nextToken()

    def nextToken(self):
        self.curToken = self.peekToken
        self.peekToken = self.lexer.nextToken()

    def ParseProgram(self, program):
        #program = Program()
        while self.curToken.token_type != TokenType.EOF:
            statement = self.parseStatement()
            print statement
            if statement:
                program.statements.append(statement)
            self.nextToken()
        #return program

    def parseStatement(self):
        if self.curToken.token_type == TokenType.LET:
            return self.parseLetStatement()
        elif self.curToken.token_type == TokenType.RETURN:
            return self.parseReturnStatement()
        else:
            return None

    def parseLetStatement(self):
        statement = LetStatement(self.curToken)
        if not self.expectPeek(TokenType.IDENT):
            return None
        statement.name = Identifier(self.curToken, self.curToken.literal)
        if not self.expectPeek(TokenType.ASSIGN):
            return None
        while not self.curTokenIs(TokenType.SEMICOLON):
            self.nextToken()
        return statement

    def parseReturnStatement(self):
        statement = ReturnStatement(self.curToken)
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
            return True
        else:
            return False
