/*
    EIW - Everything is wrong
    Programming language
*/
console.log('running eiw.js...');

const keywords = {
    PRINT: 'print',
    IF: 'if',
    ELSE: 'else',
    OPEN_BRAKETS: '{',
    CLOSE_BRAKETS: '}',
    INSTRUCTION_END: ';'
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
}

function Lexer() {

};

Lexer.prototype.getLineTokens = function (line) {
    var tokens = [];
    tokens = line.split(' '); // TODO
    return tokens;
}

function AbstractSyntaxTree() {

};

function Action() {

};

Action.prototype.execute = function () {
    console.log("executing instruction");
}

function PrintAction() {
    Action.call(this);
};

function IfAction() {
    Action.call(this);
}

function Program() {

};

function evaluateExpression() {

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
    console.log(abstractSyntaxTree.tokens);
};

$(document).ready(function () {
    $('#run-button').on('click', function () {
        var source = $('#source').val();
        var program = new Program();
        program.traverse(source);
    });
});
