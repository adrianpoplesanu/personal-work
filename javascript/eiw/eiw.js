/*
    EIW - Everything is wrong
    Programming language
*/
console.log('running eiw.js...');

const keywords = {
    PRINT: 0,
    IF: 1,
    ELSE: 2,
    OPEN_BRAKETS: 3,
    CLOSE_BRAKETS: 4,
    INSTRUCTION_END: 5,
    VOID_INSTRUCTION: 6,
    STRING_DEFINITION: 7,
    NUMBER_DEFINITION: 8,
    STRING_VALUE: 9,
    NUMBER_VALUE: 10,
    UNKNOWN_KEYWORD: 11,
    DEFINE_VARIABLE: 12,
    ATTRIBUTION_OPERATOR: 13,
    GREATER_THAN: 14,
    LOWER_THAN: 15,
    BOOL_TRUE: 16,
    BOOL_FALSE: 17,
    OPEN_PAREN: 18,
    CLOSED_PAREN: 19,
}

const tokens_to_keywords = {
    'print': keywords.PRINT,
    'if': keywords.IF,
    'else': keywords.ELSE,
    '{': keywords.OPEN_BRAKETS,
    '}': keywords.CLOSE_BRAKETS,
    ';': keywords.INSTRUCTION_END,
    'string': keywords.STRING_DEFINITION,
    'number': keywords.NUMBER_DEFINITION,
    'define': keywords.DEFINE_VARIABLE,
    '=': keywords.ATTRIBUTION_OPERATOR,
    '>': keywords.GREATER_THAN,
    '<': keywords.LOWER_THAN,
    'true': keywords.BOOL_TRUE,
    'false': keywords.BOOL_FALSE,
    '(': keywords.OPEN_PAREN,
    ')':keywords.CLOSED_PAREN,
}

const identifiers = {
    STRING: '???',
    NUMBER: '???'
}

var symbolTable = [];
var codeBlockHeap = 0;

function Parser() {

};

Parser.prototype.buildAbstractSyntaxTree = function(tokens) {
    var abstractSyntaxTree = new AbstractSyntaxTree();
    var i;
    for (i = 0; i < tokens.length; i++) {
        console.log(tokens[i]);
    }
    //abstractSyntaxTree.tokens = tokens;
    return abstractSyntaxTree;
};

function Token(keyword, value2) {
    this.keyword = keyword;
    this.value2 = value2;
}

function Lexer() {

};

Lexer.prototype.getLineTokens = function (line) {
    var tokens = [];
    var pos = 0;
    var is_string = false;
    var is_number = false;
    var token = '';
    while (pos < line.length) {
        if (line[pos] == ' ') {
            if (is_string) {
                token += ' ';
            } else {
                if (token) {
                    if (token in tokens_to_keywords) {
                        tokens.push(new Token(tokens_to_keywords[token], token));
                    } else {
                        tokens.push(new Token(keywords.UNKNOWN_KEYWORD, token));
                    }
                }
                token = '';
            }
        } else if (line[pos] == '"') {
            if (is_string) {
                is_string = false;
                tokens.push(new Token(keywords.STRING_VALUE, token));
                token = '';
            } else {
                is_string = true;
            }
        } else if (line[pos] == '{') {
            if (is_string) {
                token += '{';
            } else {
                if (token) {
                    console.log('possible compiler error');
                    tokens.push(new Token(keywords.UNKNOWN_KEYWORD, token));
                    token = '';
                }
                tokens.push(new Token(keywords.OPEN_BRAKETS, '{'));
            }
        } else if (line[pos] == '}') {
            if (is_string) {
                token += '}';
            } else {
                if (token) {
                    console.log('possible compiler error');
                    tokens.push(new Token(keywords.UNKNOWN_KEYWORD, token));
                    token = '';
                }
                tokens.push(new Token(keywords.CLOSE_BRAKETS, '}'));
            }
        } else if (line[pos] == '(') {
            if (is_string) {
                token += '(';
            } else {
                if (token) {
                    console.log('possible compiler error');
                    tokens.push(new Token(keywords.UNKNOWN_KEYWORD, token));
                    token = '';
                }
                tokens.push(new Token(keywords.OPEN_PAREN, '('));
            }
        } else if (line[pos] == ')') {
            if (is_string) {
                token += ')';
            } else {
                if (token) {
                    console.log('possible compiler error');
                    tokens.push(new Token(keywords.UNKNOWN_KEYWORD, token));
                    token = '';
                }
                tokens.push(new Token(keywords.CLOSED_PAREN, ')'));
            }
        } else if (line[pos] == ';') {
            if (is_string) {
                token += ';';
            } else {
                if (token) {
                    tokens.push(new Token(keywords.UNKNOWN_KEYWORD, token));
                    token = '';
                }
                tokens.push(new Token(keywords.INSTRUCTION_END, ';'));
            }
        } else {
            token += line[pos];
        }
        pos++;
    }
    if (token) { // TODO: fix this
        console.log('possible compiler error');
        tokens.push(new Token(keywords.UNKNOWN_KEYWORD, token));
        token = '';
    }
    return tokens;
};

function AbstractSyntaxTree() {
    var root = null;
};

function AstNode() {

}

function Statement() {

};

Statement.prototype.eval = function () {
    console.log("evaluating statement");
};

function PrintStatement() {
    Statement.call(this);
};

function IfStatement() {
    Statement.call(this);
};

function DefineStatement() {
    Statement.call(this);
}

function Program() {

};

function evaluateExpression() {

};

Program.prototype.traverse = function (source) {
    console.log('traversing...');
    var lexer = new Lexer();
    var parser = new Parser();
    var abstractSyntaxTree;
    var lines = source.split('\n');
    var i, tokens = [];
    for (i = 0; i < lines.length; i++) {
        const new_tokens = lexer.getLineTokens(lines[i]);
        tokens.push(...new_tokens);
    }
    abstractSyntaxTree = parser.buildAbstractSyntaxTree(tokens);
    //console.log(abstractSyntaxTree.tokens);
};

$(document).ready(function () {
    $('#run-button').on('click', function () {
        var source = $('#source').val();
        var program = new Program();
        program.traverse(source);
    });
});
