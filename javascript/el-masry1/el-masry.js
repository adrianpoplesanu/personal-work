console.log("el-masry.js is running...");
var game;
var clockTicks;

var canvas, context;

var UpArrow = 38;
var DownArrow = 40;
var LeftArrow = 37;
var RightArrow = 39;
var SpaceKey = 32;

var keystate = {};

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
    clockTicks++;
    if (clockTicks == 20) {
        clockTicks = 0;
    }

    this.handleInput ();
}

Game.prototype.handleInput = function () {
    if (keystate[UpArrow]) {

    }
    if (keystate[DownArrow]) {

    }
    if (keystate[LeftArrow]) {

    }
    if (keystate[RightArrow]) {

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

function init() {
    clockTicks = 0;
    game = new Game();
}

function update() {
    context.fillStyle = 'black';
    context.fillRect(0, 0, canvas.width, canvas.height);
    game.loop();
}