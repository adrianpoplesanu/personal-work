console.log("tetris.js is running...");
var game, piece;
var clockTicks;

var canvas, context;

var UpArrow = 38;
var DownArrow = 40;
var LeftArrow = 37;
var RightArrow = 39;
var SpaceKey = 32;

var keystate = {};

var PiecesEnum = {
  RR: 0,
  RL: 1,
  I: 2,
  LR: 3,
  LL: 4,
  S: 5,
  P: 6,
  properties: {
    0: [{x: 0, y: 0}, {x: 0, y: 1}, {x: 1, y: 1}, {x: 1, y: 2}],
    1: [{x: 1, y: 0}, {x: 0, y: 1}, {x: 1, y: 1}, {x: 0, y: 2}],
    2: [{x: 0, y: 0}, {x: 0, y: 1}, {x: 0, y: 2}, {x: 0, y: 3}],
    3: [{x: 0, y: 0}, {x: 0, y: 1}, {x: 0, y: 2}, {x: 1, y: 2}],
    4: [{x: 1, y: 0}, {x: 1, y: 1}, {x: 1, y: 2}, {x: 0, y: 2}],
    5: [{x: 0, y: 0}, {x: 0, y: 1}, {x: 1, y: 0}, {x: 1, y: 1}],
    6: [{x: 0, y: 0}, {x: 1, y: 0}, {x: 2, y: 0}, {x: 1, y: 1}]
  }
};

window.onload = function () {
    canvas = document.getElementById("canvas");
    context = canvas.getContext("2d");

    init();
    setInterval(update, 1000/30);
}

window.addEventListener("keydown", function(e) {
    // space and arrow keys
    if (e.keyCode == 27) {
        window.location.reload();
    }
    if([32, 37, 38, 39, 40].indexOf(e.keyCode) > -1) {
        e.preventDefault();
    }
}, false);

document.addEventListener("keydown", function (event) {
    keystate[event.keyCode] = true;
});

document.addEventListener("keyup", function (event) {
    if (event.keyCode === UpArrow) {
        piece.rotate = false;
    }
    delete keystate[event.keyCode];
});

function generateMatrix(x, y) {
    var matrix = new Array(x);
    for (var i = 0; i < x; i++) {
        matrix[i] = new Array(y);
        for (var j = 0; j < y; j++) {
            matrix[i][j] = 0;
        }
    }
    return matrix;
}

function Game() {
    var gridX, gridY;
    var offsetX, offsetY;
    var cellSize;
    this.gridX = 10;
    this.gridY = 22;
    this.offsetX = 50;
    this.offsetY = 50;
    this.cellSize = 20;
    this.board = generateMatrix(24, 10);
}

Game.prototype.loop = function () {
    //console.log("update called...");
    clockTicks++;
    piece.adjustCooldown();
    if (clockTicks == 20) {
        clockTicks = 0;
        // need to move current piece ???
        //this.moveCurrentPiece();
    }
    if (clockTicks % 4 == 0) {
        piece.move();
    }
    if (clockTicks % 10 == 0 || (keystate[DownArrow])) {
        piece.lands();
        piece.gravity(); // astea doua trebuie inversate
    }
    if (clockTicks % 1 == 0) {
        piece.flip();
    }
    this.clearLines ();
    this.handleInput ();
    this.drawGrid ();
    this.drawRandom ();
    piece.draw();
    // need to draw current piece
}

Game.prototype.handleInput = function () {
    if (keystate[UpArrow]) {
        piece.rotate = true;
    }
    if (keystate[DownArrow]) {

    }
    if (keystate[LeftArrow]) {
        piece.dx = -1;
    }
    if (keystate[RightArrow]) {
        piece.dx = 1;
    }
}

Game.prototype.drawGrid = function () {
    'use strict';
    var i, j;
    for (i = 0; i < this.gridX; i++) {
        for (j = 0; j < this.gridY; j++) {
            if ((i + j) % 2 == 0)
                context.fillStyle = '#0f0f0f';
            else
                context.fillStyle = '#0a0a0a';

            //console.log (this.board[j][i]);
            if (this.board[j][i] == 1) context.fillStyle = 'red';
            if (this.board[j][i] == 2) context.fillStyle = 'darkred';
            if (this.board[j][i] == 3) context.fillStyle = 'yellow';
            if (this.board[j][i] == 4) context.fillStyle = 'cyan';
            if (this.board[j][i] == 5) context.fillStyle = 'grey';
            if (this.board[j][i] == 6) context.fillStyle = 'purple';
            if (this.board[j][i] == 7) context.fillStyle = 'green';
            context.beginPath();
            context.moveTo(this.offsetX + i * this.cellSize, this.offsetY + j * this.cellSize);
            context.lineTo(this.offsetX + i * this.cellSize + this.cellSize, this.offsetY + j * this.cellSize);
            context.lineTo(this.offsetX + i * this.cellSize + this.cellSize, this.offsetY + j * this.cellSize + this.cellSize);
            context.lineTo(this.offsetX + i * this.cellSize, this.offsetY + j * this.cellSize + this.cellSize);
            context.closePath();
            context.fill();
        }
    }
}

Game.prototype.drawRandom = function () {

}

Game.prototype.clearLines = function () {
    var i, j, k;
    for (i = 22; i > 0; i--) {
        var clear = true;
        for (j = 0; j < 10; j++) {
            if (this.board[i][j] == 0) clear = false;
        }
        if (clear) {
            for (k = i - 1; k > 0; k--) {
                for (j = 0; j < 10; j++) {
                    this.board[k+1][j] = this.board[k][j];
                }
            }
            i++;
        }
    }
}

function Piece() {
    this.rotate = false;
    this.body = [];
    this.dx = 0;
    this.dy = 0; // sau +1
    this.x = 4;
    this.y = 0;
    this.color = 0;
    this.type = 0;
    this.cooldown = 0;
    this.reset(4, 0);
}

Piece.prototype.reset = function (x, y) {
    this.x = x;
    this.y = y;
    //this.body = [{x: 0, y: 0}, {x: 0, y: 1}, {x: 1, y: 1}, {x: 1, y: 2}]
    this.type = Math.floor(Math.random() * 7);
    this.color = this.type;
    this.body = PiecesEnum.properties[this.type];
    if (this.type == PiecesEnum.I || this.type == PiecesEnum.P) this.y += 1;
}

Piece.prototype.move = function () {
    if (!this.validateMove()) {
        return;
    }
    this.x = this.x + this.dx;
    this.dx = 0;
}

Piece.prototype.validateMove = function () {
    var i;
    for (i = 0; i < this.body.length; i++) {
        if ((this.x + this.body[i].x + this.dx < 0) || (this.x + this.body[i].x + this.dx > 9)) {
            return false;
        }
        if (game.board[this.y + this.body[i].y][this.x + this.body[i].x + this.dx] != 0) {
            return false;
        }
    }
    return true;
}

Piece.prototype.flip = function () {
    if (this.rotate && this.cooldown == 0) {
        this.rotate = false;
        this.cooldown = 10;
        var p = {x: this.body[1].x, y: this.body[1].y};
        var i, x, y;
        for (i = 0; i < this.body.length; i++) {
            x = this.body[i].y - p.y;
            y = this.body[i].x - p.x;
            this.body[i].x = p.x - x;
            this.body[i].y = p.y + y;
        }
    }

    for (i = 0; i < this.body.length; i++) {
        if (this.x + this.body[i].x < 0) {
            this.x += 1;
            return;
        }
        if (this.x + this.body[i].x > 9) {
            this.x -= 1;
            return;
        }
    }
}

Piece.prototype.adjustCooldown = function () {
    this.cooldown--;
    if (this.cooldown <= 0) this.cooldown = 0;
}

Piece.prototype.gravity = function () {
    this.y = this.y + this.dy;
    this.dy = 1;
}

Piece.prototype.lands = function () {
    var i;
    for (i = 0; i < this.body.length; i++) {
        if ((this.y + this.body[i].y == 21 ) || (game.board[this.y + this.body[i].y + 1][this.x + this.body[i].x] != 0)) {
            //this.y = 0;
            var j;
            for (j = 0; j < this.body.length; j++) {
                game.board[this.y + this.body[j].y][this.x + this.body[j].x] = this.color + 1;
            }
            this.reset(4, -1);
            return;
        }
    }
}

Piece.prototype.draw = function () {
    var i;
    for (i = 0; i < this.body.length; i++) {
        if (this.color == 0) context.fillStyle = 'red';
        if (this.color == 1) context.fillStyle = 'darkred';
        if (this.color == 2) context.fillStyle = 'yellow';
        if (this.color == 3) context.fillStyle = 'cyan';
        if (this.color == 4) context.fillStyle = 'grey';
        if (this.color == 5) context.fillStyle = 'purple';
        if (this.color == 6) context.fillStyle = 'green';
        context.beginPath();
        context.moveTo(game.offsetX + (this.x + this.body[i].x) * game.cellSize, game.offsetY + (this.y + this.body[i].y) * game.cellSize);
        context.lineTo(game.offsetX + (this.x + this.body[i].x + 1) * game.cellSize, game.offsetY + (this.y + this.body[i].y) * game.cellSize);
        context.lineTo(game.offsetX + (this.x + this.body[i].x + 1) * game.cellSize, game.offsetY + (this.y + this.body[i].y + 1) * game.cellSize);
        context.lineTo(game.offsetX + (this.x + this.body[i].x) * game.cellSize, game.offsetY + (this.y + this.body[i].y + 1) * game.cellSize);
        context.closePath();
        context.fill();
    }
}

function init() {
    clockTicks = 0;
    game = new Game();
    piece = new Piece();
}

function update() {
    context.fillStyle = 'black';
    context.fillRect(0, 0, canvas.width, canvas.height);
    game.loop();
}