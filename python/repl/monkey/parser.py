from ast import Program
from ast import LetStatement
from ast import ReturnStatement
from ast import Identifier
from ast import IntegerLiteral
from ast import ExpressionStatement
from ast import PrefixExpression
from ast import InfixExpression
from ast import Boolean
from ast import IfExpression
from ast import BlockStatement
from ast import FunctionLiteral
from ast import CallExpression
from ast import StringLiteral
from ast import ArrayLiteral
from ast import IndexExpression
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
            TokenType.ASTERISK: ParseType.PRODUCT,
            TokenType.LPAREN: ParseType.CALL,
            TokenType.LBRACKET: ParseType.INDEX
        }

    def new(self, lexer=None):
        self.lexer = lexer # maybe don't do it like that
        self.nextToken()
        self.nextToken()
        self.errors = []
        self.prefixParseFns = {}
        self.infixParseFns = {}
        self.registerPrefix(TokenType.IDENT, self.parseIdentifier)
        self.registerPrefix(TokenType.INT, self.parseIntegerLiteral)
        self.registerPrefix(TokenType.BANG, self.pasrsePrefixExpression)
        self.registerPrefix(TokenType.MINUS, self.pasrsePrefixExpression)
        self.registerPrefix(TokenType.TRUE, self.parseBoolean)
        self.registerPrefix(TokenType.FALSE, self.parseBoolean)
        self.registerPrefix(TokenType.LPAREN, self.parseGroupedExpression)
        self.registerPrefix(TokenType.IF, self.parseIfExpression)
        self.registerPrefix(TokenType.FUNCTION, self.parseFunctionLiteral)
        self.registerPrefix(TokenType.STRING, self.parseStringLiteral)
        self.registerPrefix(TokenType.LBRACKET, self.parseArrayLiteral)
        self.registerInfix(TokenType.PLUS, self.parseInfixExpression)
        self.registerInfix(TokenType.MINUS, self.parseInfixExpression)
        self.registerInfix(TokenType.SLASH, self.parseInfixExpression)
        self.registerInfix(TokenType.ASTERISK, self.parseInfixExpression)
        self.registerInfix(TokenType.EQ, self.parseInfixExpression)
        self.registerInfix(TokenType.NOT_EQ, self.parseInfixExpression)
        self.registerInfix(TokenType.LT, self.parseInfixExpression)
        self.registerInfix(TokenType.GT, self.parseInfixExpression)
        self.registerInfix(TokenType.LPAREN, self.parseCallExpression)
        self.registerInfix(TokenType.LBRACKET, self.parseIndexExpression)

    def nextToken(self):
        self.curToken = self.peekToken
        self.peekToken = self.lexer.nextToken()

    def registerPrefix(self, token_type, fn):
        self.prefixParseFns[token_type] = fn

    def registerInfix(self, token_type, fn):
        self.infixParseFns[token_type] = fn

    def ParseProgram(self, program):
        while self.curToken.token_type != TokenType.EOF:
            statement = self.parseStatement()
            if statement:
                program.statements.append(statement)
            self.nextToken()

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
        self.nextToken()
        statement.value = self.parseExpression(ParseType.LOWEST)
        if self.curTokenIs(TokenType.SEMICOLON):
            self.nextToken()
        return statement

    def parseReturnStatement(self):
        statement = ReturnStatement(self.curToken)
        self.nextToken()
        statement.returnValue = self.parseExpression(ParseType.LOWEST)
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
            self.peekError(token_type)
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
            infix = self.infixParseFns[self.peekToken.token_type]
            if not infix:
                return leftExp
            self.nextToken()
            leftExp = infix(leftExp)
        return leftExp

    def parseIdentifier(self):
        return Identifier(token = self.curToken, value=self.curToken.literal)

    def parseIntegerLiteral(self):
        lit = IntegerLiteral(token = self.curToken)
        val = int(self.curToken.literal)
        lit.value = val
        return lit

    def noPrefixParseFnError(self, token_type):
        if token_type == ';':
            # do nothing with ;
            # TODO: create an ast node for EmptyInstruction for ;
            return
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

    def peekError(self, token_type):
        msg = "expected next token to be {0}, got {1} instead".format(token_type, self.peekToken.token_type)
        self.errors.append(msg)

    def parseInfixExpression(self, left):
        expression = InfixExpression(token=self.curToken, operator=self.curToken.literal, left=left)
        preced = self.curPrecedence()
        self.nextToken()
        expression.right = self.parseExpression(preced)
        return expression

    def parseBoolean(self):
        return Boolean(token=self.curToken, value=self.curTokenIs(TokenType.TRUE))

    def parseGroupedExpression(self):
        self.nextToken()
        exp = self.parseExpression(ParseType.LOWEST)
        if not self.expectPeek(TokenType.RPAREN):
            return None
        return exp

    def parseIfExpression(self):
        expression = IfExpression(token=self.curToken)
        if not self.expectPeek(TokenType.LPAREN):
            return None
        self.nextToken()
        expression.condition = self.parseExpression(ParseType.LOWEST)
        if not self.expectPeek(TokenType.RPAREN):
            return None
        if not self.expectPeek(TokenType.LBRACE):
            return None
        expression.consequence = self.parseBlockStatement()

        if self.peekTokenIs(TokenType.ELSE):
            self.nextToken()
            if not self.expectPeek(TokenType.LBRACE):
                return None
            expression.alternative = self.parseBlockStatement()

        return expression

    def parseBlockStatement(self):
        block = BlockStatement(token=self.curToken, statements=None)
        block.statements = []
        self.nextToken()
        while not self.curTokenIs(TokenType.RBRACE) and not self.curTokenIs(TokenType.EOF):
            statement = self.parseStatement()
            if statement:
                block.statements.append(statement)
            self.nextToken()
        return block

    def parseFunctionLiteral(self):
        function_literal = FunctionLiteral(self.curToken)
        if not self.expectPeek(TokenType.LPAREN):
            return None
        function_literal.parameters = self.parseFunctionParameters()
        if not self.expectPeek(TokenType.LBRACE):
            return None
        function_literal.body = self.parseBlockStatement()
        return function_literal

    def parseFunctionParameters(self):
        identifiers = []
        if self.peekTokenIs(TokenType.RPAREN):
            self.nextToken()
            return identifiers
        self.nextToken()
        ident = Identifier(token=self.curToken, value=self.curToken.literal)
        identifiers.append(ident)
        while self.peekTokenIs(TokenType.COMMA):
            self.nextToken()
            self.nextToken()
            ident = Identifier(token=self.curToken, value=self.curToken.literal)
            identifiers.append(ident)
        if not self.expectPeek(TokenType.RPAREN):
            return None
        return identifiers

    def parseCallExpression(self, function):
        exp = CallExpression(self.curToken, function=function)
        exp.arguments = self.parseCallArguments()
        return exp

    def parseCallArguments(self):
        args = []
        if self.peekTokenIs(TokenType.RPAREN):
            self.nextToken()
            return args
        self.nextToken()
        args.append(self.parseExpression(ParseType.LOWEST))
        while self.peekTokenIs(TokenType.COMMA):
            self.nextToken()
            self.nextToken()
            args.append(self.parseExpression(ParseType.LOWEST))
        if not self.expectPeek(TokenType.RPAREN):
            return None
        return args

    def parseStringLiteral(self):
        return StringLiteral(token=self.curToken, value=self.curToken.literal)

    def parseArrayLiteral(self):
        arr = ArrayLiteral(token=self.curToken)
        arr.elements = self.parseExpressionList(TokenType.RBRACKET)
        return arr

    def parseExpressionList(self, end):
        result = []
        if self.peekTokenIs(end):
            self.nextToken()
            return result
        self.nextToken()
        result.append(self.parseExpression(ParseType.LOWEST))
        while self.peekTokenIs(TokenType.COMMA):
            self.nextToken()
            self.nextToken()
            result.append(self.parseExpression(ParseType.LOWEST))
        if not self.expectPeek(end):
            return None
        return result

    def parseIndexExpression(self, left):
        exp = IndexExpression(token=self.curToken, left=left)
        self.nextToken()
        exp.index = self.parseExpression(ParseType.LOWEST)
        if not self.expectPeek(TokenType.RBRACKET):
            return None
        return exp


class ParseType(object):
    LOWEST = 1
    EQUALS = 2
    LESSGREATER = 3
    SUM = 4
    PRODUCT = 5
    PREFIX = 6
    CALL = 7
    INDEX = 8
