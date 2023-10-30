var canvas = document.getElementById("canvas");
var context = canvas.getContext("2d");

var height = canvas.height;
var width = canvas.width;

var framesPerSecond = 30;
var lumination = 0;
var luminationStep = 0.00;

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

function Game() {
    this.gameObjects = [];
    this.gameLoop = new GameLoop();
}

Game.prototype.start = function () {
    console.log("starting game...");
    for (gameObject in game.gameObjects) {
        gameObject.start();
    }
    setInterval(game.update, 1000/framesPerSecond);
}

Game.prototype.update = function () {
    game.gameLoop.update();
    for (gameObject in game.gameObjects) {
        gameObject.update();
    }

    //context.fillStyle = 'orange';
    lumination += luminationStep;
    //if (lumination > 0.99) luminationStep = -0.01;
    //if (lumination < 0.01) luminationStep = 0.01;

    context.fillStyle = "rgba(255, 140, 0, " + lumination + ")";
    context.fillRect(10, 10, 20, 20);
}

var game = new Game();
game.start();
