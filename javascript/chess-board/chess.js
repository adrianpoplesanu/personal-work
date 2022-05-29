var board = new Board();
var START_POSITION = '';
var END_POSITION = '';
var START_PIECE = '';
var END_PIECE = '';

function addEvents() {
    $('.square').mousedown(function () {
        START_POSITION = $(this).attr('id');
        START_PIECE = $(this).data('piece');
    });
    $('.square').mouseup(function () {
        END_POSITION = $(this).attr('id');
        END_PIECE = $(this).data('piece');

        if (START_POSITION === END_POSITION) {
            return false;
        }

        if (START_PIECE == '') {
            return false;
        }

        if (END_POSITION.indexOf('chooser') == -1) {
            $(this).data('piece', START_PIECE);
        }

        board.placePiece(START_POSITION, END_POSITION, START_PIECE);
        board.draw();

        if (START_POSITION.indexOf('chooser') == -1) {
            $("#" + START_POSITION).data('piece', '');
        }

    });
    $('body').mouseup(function () {
        if (START_POSITION == '') {
            return false;
        }
        if (START_POSITION.indexOf('chooser') == -1) {
            $("#" + START_POSITION).data('piece', '');
        }
        board.deletePiece(START_POSITION);
    });
    $('#flip-board').on('click', function () {
        board.flipBoard();
    });
}

$(document).ready(function () {
    console.log("loaded");
    board.init();
    board.drawDefaultPieces();
    board.draw();
    addEvents();
});