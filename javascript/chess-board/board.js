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
                $('#chooser-square-' + square).append('<div class="piece"><img src="' + image + '"></img></div>');
            }
        }
    }
}

Board.prototype.flipBoard = function () {
    this.flipped = !this.flipped;
    this.draw();
}

Board.prototype.draw = function () {
    if (!this.flipped) {
        console.log("draw board normal");
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
                    $('#square-' + square).append('<div class="piece"><img src="' + image + '"></img></div>');
                }
            }
        }
    } else {
        console.log("draw board flipped");
    }
    this.drawDefaultPieces();
}