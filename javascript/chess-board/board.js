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
    this.updateMarkings();
    this.draw();
}

Board.prototype.updateMarkings = function () {
    if (this.flipped) {
        $('#square-7 .letter').html('h');
        $('#square-6 .letter').html('g');
        $('#square-5 .letter').html('f');
        $('#square-4 .letter').html('e');
        $('#square-3 .letter').html('d');
        $('#square-2 .letter').html('c');
        $('#square-1 .letter').html('b');
        $('#square-0 .letter').html('a');
        $('#square-7 .numeric').html('8');
        $('#square-15 .numeric').html('7');
        $('#square-23 .numeric').html('6');
        $('#square-31 .numeric').html('5');
        $('#square-39 .numeric').html('4');
        $('#square-47 .numeric').html('3');
        $('#square-55 .numeric').html('2');
        $('#square-63 .numeric').html('1');
    } else {
        $("#square-7 .letter").html('a');
        $('#square-6 .letter').html('b');
        $('#square-5 .letter').html('c');
        $('#square-4 .letter').html('d');
        $('#square-3 .letter').html('e');
        $('#square-2 .letter').html('f');
        $('#square-1 .letter').html('g');
        $('#square-0 .letter').html('h');
        $('#square-7 .numeric').html('1');
        $('#square-15 .numeric').html('2');
        $('#square-23 .numeric').html('3');
        $('#square-31 .numeric').html('4');
        $('#square-39 .numeric').html('5');
        $('#square-47 .numeric').html('6');
        $('#square-55 .numeric').html('7');
        $('#square-63 .numeric').html('8');
    }
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

Board.prototype.get_piece = function (POSITION, level) {
    var i, j;
    if (this.flipped) {
        if (POSITION.indexOf('chooser') != -1) {
            i = get_i(63 - parseInt(POSITION.replace('chooser-square-', '')), 6);
            j = get_j(63 - parseInt(POSITION.replace('chooser-square-', '')), 6);
        } else {
            i = get_i(63 - parseInt(POSITION.replace('square-', '')), 8);
            j = get_j(63 - parseInt(POSITION.replace('square-', '')), 8);
        }
    } else {
        if (POSITION.indexOf('chooser') != -1) {
            i = get_i(parseInt(POSITION.replace('chooser-square-', '')), 6);
            j = get_j(parseInt(POSITION.replace('chooser-square-', '')), 6);
        } else {
            i = get_i(parseInt(POSITION.replace('square-', '')), 8);
            j = get_j(parseInt(POSITION.replace('square-', '')), 8);
        }
    }
    return this.tabla[i][j];
}

Board.prototype.placePiece = function (START_POSITION, END_POSITION, START_PIECE) {
    if (this.flipped) {
        if ('prnbkqPRNBKQ'.indexOf(START_PIECE) != -1) {
            var start_i = -1;
            var start_j = -1;
            if (START_POSITION.indexOf('chooser') != -1) {
                start_i = get_i(63 - parseInt(START_POSITION.replace('chooser-square-', '')), 6);
                start_j = get_j(63 - parseInt(START_POSITION.replace('chooser-square-', '')), 6);
            } else {
                start_i = get_i(63 - parseInt(START_POSITION.replace('square-', '')), 8);
                start_j = get_j(63 - parseInt(START_POSITION.replace('square-', '')), 8);
            }
            if (END_POSITION.indexOf('chooser') == -1) {
                var end_i = get_i(63 - parseInt(END_POSITION.replace('square-', '')), 8);
                var end_j = get_j(63 - parseInt(END_POSITION.replace('square-', '')), 8);
                this.tabla[end_i][end_j] = START_PIECE;

                if (START_POSITION.indexOf('chooser') == -1) {
                    this.tabla[start_i][start_j] = '-';
                }
            }
        }
    } else {
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
                    $('#square-' + (63 - square)).append('<div class="piece" ondrop="drop(event)"><img src="' + image + '"></img></div>');
                }
            }
        }
    }
}

Board.prototype.deletePiece = function (START_POSITION) {
    if (this.flipped) {
        if (START_POSITION.indexOf('chooser') == -1) {
            start_i = get_i(63 - parseInt(START_POSITION.replace('square-', '')), 8);
            start_j = get_j(63 - parseInt(START_POSITION.replace('square-', '')), 8);
            this.tabla[start_i][start_j] = '-';
        }
    } else {
        if (START_POSITION.indexOf('chooser') == -1) {
            start_i = get_i(parseInt(START_POSITION.replace('square-', '')), 8);
            start_j = get_j(parseInt(START_POSITION.replace('square-', '')), 8);
            this.tabla[start_i][start_j] = '-';
        }
    }
    this.draw();
}

function drop(ev) {
    ev.preventDefault();
}