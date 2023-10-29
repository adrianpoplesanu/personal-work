var canvas = document.getElementById("canvas");
var context = canvas.getContext("2d");

var height = canvas.height;
var width = canvas.width;

var framesPerSecond = 30;

function clearScreen() {
    context.fillStyle = 'black';
    context.fillRect(0, 0, width, height);
}

function GameLoop() {

}

GameLoop.prototype.clear = function () {
    clearScreen();
}

GameLoop.prototype.update = function () {
    this.clear();
}

var gameLoop = new GameLoop();

function Game() {
    this.gameObjects = [];
}

Game.prototype.start = function () {
    console.log("starting game...");
    setInterval(this.update, 1000/framesPerSecond);
}

Game.prototype.update = function () {
    gameLoop.update();
    for (gameObject in this.gameObjects) {
        gameObject.update();
    }
}

var game = new Game();
game.start();
