token_types = [
    'ILLEGAL',
    'IDENT',
    'INT',
    'ASSIGN',
    'PLUS',
    'MINUS',
    'SLASH',
    'ASTERICKS',
    'BANG',
    'LET',
    'RETURN',
    'WHILE',
    'LPAREN',
    'RPAREN',
    'LBRACE',
    'RBRACE',
    'COLON',
    'SEMICOLON',
    'LT',
    'GT',
    'EQ',
    'NOT_EQ'
]

if __name__ == '__main__':
    for token in token_types:
        print 'token_type_map.insert(pair<TokenType, string>(' + token + ', "' + token + '"));'
