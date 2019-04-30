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
    ADDITION_OPERATOR: 20,
    IDENTIFIER_ : 21,
}

const keywords_to_strings = {
    0: 'PRINT',
    1: 'IF',
    2: 'ELSE',
    3: 'OPEN_BRAKETS',
    4: 'CLOSE_BRAKETS',
    5: 'INSTRUCTION_END',
    6: 'VOID_INSTRUCTION',
    7: 'STRING_DEFINITION',
    8: 'NUMBER_DEFINITION',
    9: 'STRING_VALUE',
    10: 'NUMBER_VALUE',
    11: 'UNKNOWN_KEYWORD',
    12: 'DEFINE_VARIABLE',
    13: 'ATTRIBUTION_OPERATOR',
    14: 'GREATER_THAN',
    15: 'LOWER_THAN',
    16: 'BOOL_TRUE',
    17: 'BOOL_FALSE',
    18: 'OPEN_PAREN',
    19: 'CLOSED_PAREN',
    20: 'ADDITION_OPERATOR',
    21: 'IDENTIFIER_',
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
    ')': keywords.CLOSED_PAREN,
    '+': keywords.ADDITION_OPERATOR,
}

const identifiers = {
    STRING: '???',
    NUMBER: '???'
}

//.var symbolTable = [];
//var codeBlockHeap = 0;

function Parser() {

};

Parser.prototype.buildAbstractSyntaxTree = function(tokens) {
    var abstractSyntaxTree = new AbstractSyntaxTree();
    var i;
    //abstractSyntaxTree.root = new AstNode();
    var current = abstractSyntaxTree.root;
    for (i = 0; i < tokens.length; i++) {
        //console.log(tokens[i]);
        //virtual_machine_output(tokens[i].toString());
        if (tokens[i].keyword == keywords.PRINT) {
            var new_node = new AstNode();
            new_node.parent2 = current;
            new_node.symbolTable = {...current.symbolTable}; // TODO check if this works!!!
            new_node.level = new_node.parent2.level + 1;
            new_node.type2 = 'call_print';
            current.children.push(new_node);
            current = new_node;
            continue;
        }
        if (tokens[i].keyword == keywords.STRING_VALUE) {
            var new_node = new AstNode();
            new_node.parent2 = current;
            new_node.level = new_node.parent2.level + 1;
            new_node.type2 = 'call_string_identifier';
            current.children.push(new_node);
            continue;
        }
        if (tokens[i].keyword == keywords.INSTRUCTION_END) {
            if (current.type2 == 'call_print' || current.type2 == 'call_define_variable') { // nu sunt sigur aici ca e ce trebuie
                var new_node = new AstNode();
                new_node.parent2 = current;
                new_node.level = new_node.parent2.level + 1;
                new_node.type2 = 'call_end_instruction';
                current.children.push(new_node);
                current = current.parent2; // asta pare incorecta
            }
            continue;
        }
        if (tokens[i].keyword == keywords.OPEN_BRAKETS) {
            var new_node = new AstNode();
            new_node.parent2 = current;
            new_node.level = new_node.parent2.level + 1;
            new_node.type2 = 'call_start_code_block';
            current.children.push(new_node);
            current = new_node;
            continue;
        }
        if (tokens[i].keyword == keywords.CLOSE_BRAKETS) {
            if (current.type2 == 'call_start_code_block') {
                var new_node = new AstNode();
                new_node.parent2 = current;
                new_node.level = new_node.parent2.level + 1;
                new_node.type2 = 'call_end_code_block';
                current.children.push(new_node);
                current = current.parent2;
                if (current.type2 == 'call_if') current = current.parent2; // iarasi nu sunt 100% sigur
                //current = new_node;
            }
            continue;
        }
        if (tokens[i].keyword == keywords.DEFINE_VARIABLE) {
            var new_node = new AstNode();
            new_node.parent2 = current;
            new_node.level = new_node.parent2.level + 1;
            new_node.type2 = 'call_define_variable';
            current.children.push(new_node);
            //current = current.parent2;
            current = new_node;
            continue;
        }
        if (tokens[i].keyword == keywords.IDENTIFIER_) {
            var new_node = new AstNode();
            //console.log(tokens[i].value2);
            new_node.parent2 = current;
            new_node.level = new_node.parent2.level + 1;
            new_node.type2 = 'call_identifier_';
            current.children.push(new_node);
            //current = current.parent2;
            //current = new_node;
            continue;
        }
        if (tokens[i].keyword == keywords.IF) {
            var new_node = new AstNode();
            //console.log(tokens[i].value2);
            new_node.parent2 = current;
            new_node.level = new_node.parent2.level + 1;
            new_node.type2 = 'call_if';
            current.children.push(new_node);
            //current = current.parent2;
            current = new_node;
            continue;
        }
        if (tokens[i].keyword == keywords.OPEN_PAREN) {
            if (current.type2 == 'call_if') {
                var new_node = new AstNode();
                //console.log(tokens[i].value2);
                new_node.parent2 = current;
                new_node.level = new_node.parent2.level + 1;
                new_node.type2 = 'call_conditional_begin';
                current.children.push(new_node);
                //current = current.parent2;
                current = new_node;
            }
            continue;
        }
        if (tokens[i].keyword == keywords.CLOSED_PAREN) {
            if (current.type2 == 'call_conditional_begin') {
                var new_node = new AstNode();
                new_node.parent2 = current;
                new_node.level = new_node.parent2.level + 1;
                new_node.type2 = 'call_end_conditional';
                current.children.push(new_node);
                current = current.parent2;
            }
            continue;
        }
        if (tokens[i].keyword == keywords.GREATER_THAN) {
            if (current.type2 == 'call_conditional_begin') {
                var new_node = new AstNode();
                new_node.parent2 = current;
                new_node.level = new_node.parent2.level + 1;
                new_node.type2 = 'call_greater_than';
                current.children.push(new_node);
                //current = current.parent2;
            }
            continue;
        }
        console.log(tokens[i]);
    }
    //abstractSyntaxTree.tokens = tokens;
    console.log(abstractSyntaxTree);
    return abstractSyntaxTree;
};

function Token(keyword, value2) {
    this.keyword = keyword;
    this.value2 = value2;
}

Token.prototype.toString = function () {
    return "Token [<" + this.keyword + "> : <" + keywords_to_strings[this.keyword] + "> : <" + this.value2 + ">]";
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
                        //tokens.push(new Token(keywords.UNKNOWN_KEYWORD, token));
                        tokens.push(new Token(keywords.IDENTIFIER_, token)); // nu sunt asa convins de asta
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
                    //tokens.push(new Token(keywords.UNKNOWN_KEYWORD, token));
                    tokens.push(new Token(keywords.IDENTIFIER_, token)); // nu sunt asa convins de asta
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
        } else if (line[pos] == '=') {
            if (is_string) {
                token += '=';
            } else {
                if (token) {
                    tokens.push(new Token(keywords.IDENTIFIER_, token));
                    token = '';
                }
                tokens.push(new Token(keywords.ATTRIBUTION_OPERATOR, '='));
            }
        } else if (line[pos] == '+') {
            if (is_string) {
                token += '=';
            } else {
                if (token) {
                    tokens.push(new Token(keywords.UNKNOWN_KEYWORD, token));
                    token = '';
                }
                tokens.push(new Token(keywords.ATTRIBUTION_OPERATOR, '+'));
            }
        } else if (line[pos] == '>') {
            if (is_string) {
                token += '>';
            } else {
                console.log('possible compiler error');
                if (token) {
                    tokens.push(new Token(keywords.IDENTIFIER_, token));
                    token = '';
                }
                tokens.push(new Token(keywords.GREATER_THAN, '>'));
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
    this.root = new AstNode();
};

function AstNode() {
    this.parent2 = null;
    this.children = [];
    this.symbolTable = {};
    this.level = 0;
    this.type2 = "program";
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

function virtual_machine_output(message) {
    if ($('#output').val()) {
        $('#output').val($('#output').val() + '\n' + message);
    } else {
        $('#output').val(message);
    }
    virtual_macine_scroll_bottom();
};

function virtual_macine_scroll_bottom() {
    var $textarea = $('#output');
    $textarea.scrollTop($textarea[0].scrollHeight);
}

function virtual_machine_clear_screen() {
    var $textarea = $('#output');
    $textarea.val('');
}

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
    $('#clear-button').on('click', function () {
        virtual_machine_clear_screen();
    });
});
