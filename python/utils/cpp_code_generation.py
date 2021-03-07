tokens = [
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

for token in tokens:
    print '    t.SetTokenType(' + token +');'
    print '    cout << t.GetTokenType() << "\\n";'
