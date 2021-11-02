precedences = {
    'LOWEST': 1,
    'PLUS': 2,
    'MINUS': 2,
    'ASTERISK': 3,
    'SLASH': 3,
    'PREFIX': 4,
    'LPAREN': 5
}

def is_digit(ch):
    return '0' <= ch <= '9'

def read_char(line, pos):
    if pos < len(line):
        return line[pos]
    return 0

def generate_tokens(line):
    tokens = []
    pos = 0
    ch = read_char(line, pos)
    while ch != 0:
        if is_digit(ch):
            start = pos
            while is_digit(ch):
                pos += 1
                ch = read_char(line, pos)
            tokens.append({'type': 'INT', 'val': line[start:pos]})
            pos -= 1
        elif ch == '+':
            tokens.append({'type': 'PLUS', 'val': '+'})
        elif ch == '-':
            tokens.append({'type': 'MINUS', 'val': '-'})
        elif ch == '*':
            tokens.append({'type': 'ASTERISK', 'val': '*'})
        elif ch == '/':
            tokens.append({'type': 'SLASH', 'val': '/'})
        elif ch == '(':
            tokens.append({'type': 'LPAREN', 'val': '('})
        elif ch == ')':
            tokens.append({'type': 'RPAREN', 'val': ')'})
        pos += 1
        ch = read_char(line, pos)
    tokens.append({'type': 'EOF', 'val': 'EOF'})
    return tokens

def parse_tokens(tokens):
    parser = Parser()
    parser.load(tokens)
    parser.parse_program_statement()


class ASTInteger(object):
    def __init__(self, token):
        self.token = token

    def __str__(self):
        return self.token['val']


class ASTPrefixExpression(object):
    def __str__(self):
        return 'bbb'


class ASTExpressionStatement(object):
    def __str__(self):
        return str(self.expression)


class ASTInfixExpression(object):
    def __str__(self):
        return '(' + str(self.left) + self.operator + str(self.right) + ')'


class Parser(object):
    def __init__(self):
        self.prefixFns = {}
        self.infixFns = {}
        self.prefixFns['INT'] = self.parse_integer
        self.prefixFns['MINUS'] = self.parse_prefix_expression
        self.prefixFns['LPAREN'] = self.parse_grouped_expression
        self.infixFns['PLUS'] = self.parse_infix_expression
        self.infixFns['MINUS'] = self.parse_infix_expression
        self.infixFns['ASTERISK'] = self.parse_infix_expression
        self.infixFns['SLASH'] = self.parse_infix_expression

    def load(self, tokens):
        self.tokens = tokens
        self.index = 0
        self.current_token = self.tokens[self.index]
        self.peek_token = self.tokens[self.index + 1]

    def next_token(self):
        self.index += 1
        try:
            self.current_token = self.tokens[self.index]
        except:
            self.current_token = None
        try:
            self.peek_token = self.tokens[self.index + 1]
        except:
            self.peek_token = None

    def peek_precedence(self):
        if self.peek_token['type'] in precedences:
            return precedences[self.peek_token['type']]
        return precedences['LOWEST']

    def current_precedence(self):
        if self.current_token['type'] in precedences:
            return precedences[self.current_token['type']]
        return precedences['LOWEST']

    def parse_integer(self):
        return ASTInteger(self.current_token)

    def parse_prefix_expression(self):
        expr = ASTPrefixExpression()
        self.next_token()
        expr.right = self.parse_expression(precedences['PREFIX'])
        return expr

    def parse_grouped_expression(self):
        self.next_token()
        expr = self.parse_expression(precedences['LOWEST'])
        if self.peek_token['type'] == 'RPAREN':
            self.next_token()
        return expr

    def parse_infix_expression(self, left):
        expr = ASTInfixExpression()
        expr.left = left
        expr.operator = self.current_token['val']
        precedence = self.current_precedence()
        self.next_token()
        expr.right = self.parse_expression(precedence)
        return expr

    def parse_expression(self, precedence):
        if self.current_token['type'] not in self.prefixFns:
            return None
        prefix = self.prefixFns[self.current_token['type']]
        left = prefix()
        while precedence < self.peek_precedence():
            if self.peek_token['type'] not in self.infixFns:
                return left
            infix = self.infixFns[self.peek_token['type']]
            self.next_token()
            left = infix(left)
        return left

    def parse_expression_statement(self):
        stmt = ASTExpressionStatement()
        stmt.expression = self.parse_expression(precedences['LOWEST'])
        return stmt

    def parse_program_statement(self):
        while self.current_token['type'] != 'EOF':
            stmt = self.parse_expression_statement()
            self.next_token()
            print stmt

def run():
    while(True):
        line = raw_input('>> ')
        if line.strip() == 'exit()':
            break
        elif line:
            tokens = generate_tokens(line)
            parse_tokens(tokens)
        else:
            pass

if __name__ == '__main__':
    run()
