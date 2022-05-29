function Board() {
    var flipped;
    var tabla;
}

Board.prototype.init = function() {
    this.fliped = false;
    this.tabla = Array(8).fill().map(()=>Array(8).fill('-'));
}

Board.prototype.drawDefaultPieces = function () {
    var i, j;
    var pieces = ['pnbrqk', 'PNBRQK'];
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 6; j++) {
            var image = '';
            var square = i * 6 + j;

            if ('prnbkq'.indexOf(pieces[i][j]) != -1) {
                image = 'assets/b' + pieces[i][j].toUpperCase() + '.png';
            }
            if ('PRNBKQ'.indexOf(pieces[i][j]) != -1) {
                image = 'assets/w' + pieces[i][j] + '.png';
            }

            if (image !== '') {
                $('#chooser-square-' + square).append('<div class="piece" ondrop="drop(event)"><img src="' + image + '"></img></div>');
            }
        }
    }
}

Board.prototype.flipBoard = function () {
    this.flipped = !this.flipped;
    this.draw();
}

function get_i(POSITION, level) {
    var result = 0;
    while(POSITION >= level) {
        POSITION -= level;
        result++;
    }
    return result;
}

function get_j(POSITION, level) {
    while(POSITION >= level) {
        POSITION -= level;
    }
    return POSITION;
}

Board.prototype.placePiece = function (START_POSITION, END_POSITION, START_PIECE) {
    if ('prnbkqPRNBKQ'.indexOf(START_PIECE) != -1) {
        var start_i = -1;
        var start_j = -1;
        if (START_POSITION.indexOf('chooser') != -1) {
            start_i = get_i(parseInt(START_POSITION.replace('chooser-square-', '')), 6);
            start_j = get_j(parseInt(START_POSITION.replace('chooser-square-', '')), 6);
        } else {
            start_i = get_i(parseInt(START_POSITION.replace('square-', '')), 8);
            start_j = get_j(parseInt(START_POSITION.replace('square-', '')), 8);
        }
        if (END_POSITION.indexOf('chooser') == -1) {
            var end_i = get_i(parseInt(END_POSITION.replace('square-', '')), 8);
            var end_j = get_j(parseInt(END_POSITION.replace('square-', '')), 8);
            this.tabla[end_i][end_j] = START_PIECE;

            if (START_POSITION.indexOf('chooser') == -1) {
                this.tabla[start_i][start_j] = '-';
            }
        }
    }
}

Board.prototype.draw = function () {
    $("#board .piece").remove();
    if (!this.flipped) {
        var i, j;
        for (i = 0; i < 8; i++) {
            for (j= 0; j < 8; j++) {
                var image = '';
                var square = i * 8 + j;
                if ('prnbkq'.indexOf(this.tabla[i][j]) != -1) {
                    image = 'assets/b' + this.tabla[i][j].toUpperCase() + '.png';
                }
                if ('PRNBKQ'.indexOf(this.tabla[i][j]) != -1) {
                    image = 'assets/w' + this.tabla[i][j] + '.png';
                }
                if (image !== '') {
                    $('#square-' + square).append('<div class="piece" ondrop="drop(event)"><img src="' + image + '"></img></div>');
                }
            }
        }
    } else {
        console.log("draw board flipped");
    }
}

Board.prototype.deletePiece = function (START_POSITION) {
    if (START_POSITION.indexOf('chooser') == -1) {
        start_i = get_i(parseInt(START_POSITION.replace('square-', '')), 8);
        start_j = get_j(parseInt(START_POSITION.replace('square-', '')), 8);
        this.tabla[start_i][start_j] = '-';
    }
    this.draw();
}

function drop(ev) {
    ev.preventDefault();
}