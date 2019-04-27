console.log('running mylanguage.js...');

const keywords = {
   PRINT: 'print',
   IF: 'if',
   OPEN_BRAKETS: '{',
   CLOSE_BRAKETS: '}'
}

const identifiers = {
    STRING: '???,
    NUMBER: '???'
}

function Parser() {
}

function Lexer() {

}

function AbstractSyntaxTree() {

}

function StatementEvaluator() {

}

function Program() {

}

Program.prototype.traverse = function () {
    console.log('traversing...');
}

$(document).ready(function () {
    $('#run-button').on('click', function () {
        console.log($('#source').val());
        var program = new Program();
        program.traverse();
    });
});
