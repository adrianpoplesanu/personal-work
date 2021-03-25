from ast import Program
from ast import LetStatement
from ast import ReturnStatement
from ast import Identifier
from ast import IntegerLiteral
from ast import ExpressionStatement
from ast import PrefixExpression
from ast import InflixExpression
from lexer import TokenType


class Parser(object):
    prefixParseFns = {}
    infixParseFns = {}
    errors = []
    precedences = {}

    def __init__(self, lexer=None):
        self.lexer = lexer
        self.curToken = None
        self.peekToken = None
        self.errors = []
        self.precedences = {
            TokenType.EQ: ParseType.EQUALS,
            TokenType.NOT_EQ: ParseType.EQUALS,
            TokenType.LT: ParseType.LESSGREATER,
            TokenType.GT: ParseType.LESSGREATER,
            TokenType.PLUS: ParseType.SUM,
            TokenType.MINUS: ParseType.SUM,
            TokenType.SLASH: ParseType.PRODUCT,
            TokenType.ASTERISK: ParseType.PRODUCT
        }
        #self.nextToken()
        #self.nextToken()

    def new(self, lexer=None):
        self.lexer = lexer # maybe don't do it like that
        self.nextToken()
        self.nextToken()
        self.errors = []
        self.prefixParseFns = {}
        self.inflixParseFns = {}
        self.registerPrefix(TokenType.IDENT, self.parseIdentifier)
        self.registerPrefix(TokenType.INT, self.parseIntegerLiteral)
        self.registerPrefix(TokenType.BANG, self.pasrsePrefixExpression)
        self.registerPrefix(TokenType.MINUS, self.pasrsePrefixExpression)
        self.registerInflix(TokenType.PLUS, self.parseInflixExpression)
        self.registerInflix(TokenType.MINUS, self.parseInflixExpression)
        self.registerInflix(TokenType.SLASH, self.parseInflixExpression)
        self.registerInflix(TokenType.ASTERISK, self.parseInflixExpression)
        self.registerInflix(TokenType.EQ, self.parseInflixExpression)
        self.registerInflix(TokenType.NOT_EQ, self.parseInflixExpression)
        self.registerInflix(TokenType.LT, self.parseInflixExpression)
        self.registerInflix(TokenType.GT, self.parseInflixExpression)

    def nextToken(self):
        self.curToken = self.peekToken
        self.peekToken = self.lexer.nextToken()

    def registerPrefix(self, token_type, fn):
        self.prefixParseFns[token_type] = fn

    def registerInflix(self, token_type, fn):
        self.inflixParseFns[token_type] = fn

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
            return self.parseExpressionStatement()

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

    def parseExpressionStatement(self):
        statement = ExpressionStatement(self.curToken)
        statement.expression = self.parseExpression(ParseType.LOWEST)
        if self.peekTokenIs(TokenType.SEMICOLON):
            self.nextToken()
        return statement

    def parseExpression(self, precedence):
        prefix = self.prefixParseFns.get(self.curToken.token_type)
        if not prefix:
            self.noPrefixParseFnError(self.curToken.token_type)
            return None
        leftExp = prefix()

        while not self.peekTokenIs(TokenType.SEMICOLON) and precedence < self.peekPrecedence():
            inflix = self.inflixParseFns[self.peekToken.token_type]
            if not inflix:
                return leftExp
            self.nextToken()
            leftExp = inflix(leftExp)
        return leftExp

    def parseIdentifier(self):
        return Identifier(token = self.curToken, value=self.curToken.literal)

    def parseIntegerLiteral(self):
        lit = IntegerLiteral(token = self.curToken)
        val = int(self.curToken.literal)
        lit.value = val
        return lit

    def noPrefixParseFnError(self, token_type):
        self.errors.append('no prefix parse function for ' + token_type)
        print 'no prefix parse function for ' + token_type

    def pasrsePrefixExpression(self):
        expression = PrefixExpression(token=self.curToken, operator=self.curToken.literal)
        self.nextToken()
        expression.right = self.parseExpression(ParseType.PREFIX)
        return expression

    def peekPrecedence(self):
        preced = self.precedences.get(self.peekToken.token_type)
        if preced:
            return preced
        return ParseType.LOWEST

    def curPrecedence(self):
        preced = self.precedences.get(self.curToken.token_type)
        if preced:
            return preced
        return ParseType.LOWEST

    def parseInflixExpression(self, left):
        expression = InflixExpression(token=self.curToken, operator=self.curToken.literal, left=left)
        preced = self.curPrecedence()
        self.nextToken()
        expression.right = self.parseExpression(preced)
        return expression


class ParseType(object):
    LOWEST = 1
    EQUALS = 2
    LESSGREATER = 3
    SUM = 4
    PRODUCT = 5
    PREFIX = 6
    CALL = 7
