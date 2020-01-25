console.log("snake.js is running...");
var game, player;
var clockTicks;

var canvas, context;

var UpArrow = 38;
var DownArrow = 40;
var LeftArrow = 37;
var RightArrow = 39;
var SpaceKey = 32;

var movementKey;
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
    if (event.keyCode === movementKey) {
        movementKey = false;
    }
    delete keystate[event.keyCode];
});

function Game() {
    var gridX, gridY;
    var offsetX, offsetY;
    var cellSize;
    this.gridX = 18;
    this.gridY = 12;
    this.offsetX = 100;
    this.offsetY = 100;
    this.cellSize = 20;
    this.randomX = 15;
    this.randomY = 11;
}

Game.prototype.loop = function () {
    //console.log("update called...");
    clockTicks++;
    if (clockTicks == 4) {
        clockTicks = 0;
        player.move();
    }
    this.handleInput ();
    this.drawGrid ();
    this.drawRandom ();
    player.draw ();
}

Game.prototype.handleInput = function () {
    if (keystate[UpArrow]) {
        player.directionX = 0;
        player.directionY = -1;
    }
    if (keystate[DownArrow]) {
        player.directionX = 0;
        player.directionY = 1;
    }
    if (keystate[LeftArrow]) {
        player.directionX = -1;
        player.directionY = 0;
    }
    if (keystate[RightArrow]) {
        player.directionX = 1;
        player.directionY = 0;
    }
}

Game.prototype.drawGrid = function () {
    'use strict';
    var i, j;
    for (i = 0; i < this.gridX; i++) {
        for (j = 0; j < this.gridY; j++) {
            if ((i + j) % 2 == 0)
                context.fillStyle = '#1a1a1a';
            else
                context.fillStyle = '#0f0f0f';
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
    context.fillStyle = 'blue';
    context.beginPath();
    context.moveTo(this.offsetX + this.randomX * this.cellSize, this.offsetY + this.randomY * this.cellSize);
    context.lineTo(this.offsetX + this.randomX * this.cellSize + this.cellSize, this.offsetY + this.randomY * this.cellSize);
    context.lineTo(this.offsetX + this.randomX * this.cellSize + this.cellSize, this.offsetY + this.randomY * this.cellSize + this.cellSize);
    context.lineTo(this.offsetX + this.randomX * this.cellSize, this.offsetY + this.randomY * this.cellSize + this.cellSize);
    context.closePath();
    context.fill();
}

function Player() {
    var body, directionX, directionY, headX, headY;
    this.body = [{x:10, y:7}, {x:9, y:7}, {x:8, y:7}, {x:7, y:7}, {x:6, y:7}];
    this.headX = 10;
    this.headY = 7;
    this.directionX = 1;
    this.directionY = 0;
}

Player.prototype.draw = function () {
    'use strict';
    var i;
    for (i = 0; i < this.body.length; i++) {
        context.fillStyle = 'red';
        context.beginPath();
        context.moveTo(game.offsetX + this.body[i].x * game.cellSize, game.offsetY + this.body[i].y * game.cellSize);
        context.lineTo(game.offsetX + this.body[i].x * game.cellSize + game.cellSize, game.offsetY + this.body[i].y * game.cellSize);
        context.lineTo(game.offsetX + this.body[i].x * game.cellSize + game.cellSize, game.offsetY + this.body[i].y * game.cellSize + game.cellSize);
        context.lineTo(game.offsetX + this.body[i].x * game.cellSize, game.offsetY + this.body[i].y * game.cellSize + game.cellSize);
        context.closePath();
        context.fill();
    }
}

Player.prototype.move = function () {
    this.headX += this.directionX;
    this.headY += this.directionY;
    if (this.headX >= game.gridX) this.headX = 0;
    if (this.headY >= game.gridY) this.headY = 0;
    if (this.headX < 0) this.headX = game.gridX - 1;
    if (this.headY < 0) this.headY = game.gridY - 1;
    if (game.randomX == this.headX && game.randomY == this.headY) {
        game.randomX = Math.floor(Math.random() * game.gridX);
        game.randomY = Math.floor(Math.random() * game.gridY);
    } else {
        this.body.pop();
    }
    //if ({x: this.headX, y: this.headY} in this.body) { // asta nu merge inca
    //    console.log(dead);
    //}
    var i;
    for (i = 1; i < this.body.length; i++) {
        if (this.headX == this.body[i].x && this.headY == this.body[i].y) window.location.reload();
    }
    this.body = this.body.reverse();
    this.body.push({x: this.headX, y: this.headY});
    this.body = this.body.reverse();
}

function init() {
    clockTicks = 0;
    player = new Player();
    game = new Game();
}

function update() {
    context.fillStyle = 'black';
    context.fillRect(0, 0, canvas.width, canvas.height);
    game.loop();
}