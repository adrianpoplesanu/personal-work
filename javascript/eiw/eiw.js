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
}

const identifiers = {
    STRING: '???',
    NUMBER: '???'
}

function Parser() {

};

Parser.prototype.buildAbstractSyntaxTree = function(tokens) {
    var abstractSyntaxTree = new AbstractSyntaxTree();
    abstractSyntaxTree.tokens = tokens;
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
                if (token != '') {
                    tokens.push(new Token(keywords.UNKNOWN_KEYWORD, token));
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
                //token += line[pos];
            }
        } else if (line[pos] == '{') {
            if (is_string) {
                token += '{';
            }
        } else if (line[pos] == '}') {
            if (is_string) {
                token += '}';
            }
        } else if (line[pos] == ';') {
            if (is_string) {
                token += ';';
            }
        } else {
            token += line[pos];
        }
        pos++;
    }
    //tokens = line.split(' '); // TODO
    return tokens;
};

function AbstractSyntaxTree() {
    var astNode = {};
};

function Action() {

};

Action.prototype.eval = function () {
    console.log("evaluating action");
};

function PrintAction() {
    Action.call(this);
};

function IfAction() {
    Action.call(this);
};

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
    console.log(abstractSyntaxTree.tokens);
};

$(document).ready(function () {
    $('#run-button').on('click', function () {
        var source = $('#source').val();
        var program = new Program();
        program.traverse(source);
    });
});
