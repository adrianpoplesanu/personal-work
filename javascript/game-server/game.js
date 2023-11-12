var canvas = document.getElementById("canvas");
var context = canvas.getContext("2d");

var height = canvas.height;
var width = canvas.width;

var framesPerSecond = 30;
var lumination = 0;
var luminationStep = 0.00;

var board;
var boardWidth = 60;
var boardHeight = 30;

function generateRandomTile() {
    return Math.floor(Math.random() * 3);
}

function generateRandomAlpha() {
    return Math.random();
}

function drawSquare(element) {
    //...
    var red = 255;
    var green = 140;
    var blue = 0;
    var lumination = element.alpha;
    context.fillStyle = "rgba(" + red + ", " + green + ", " + blue + ", " + lumination + ")";
    context.fillRect(element.x * 10, element.y * 10, 10, 10);
}

function generateRandomBoard(boardWidth, boardHeight) {
    board = new Array(boardHeight);
    for (var i = 0; i < boardHeight; i++) {
        board[i] = new Array(boardWidth);
        for (var j = 0; j < boardWidth; j++) {
            board[i][j] = {
                type: generateRandomTile(),
                alpha: generateRandomAlpha(),
                y: i,
                x: j
            }
        }
    }
    return board;
}

function drawBoard() {
    for (var i = 0; i < boardHeight; i++) {
        for (var j = 0; j < boardWidth; j++) {
            drawSquare(board[i][j]);
        }
    }
}

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
    generateRandomBoard(boardWidth, boardHeight);
    setInterval(game.update, 1000/framesPerSecond);
}

Game.prototype.update = function () {
    game.gameLoop.update();
    for (gameObject in game.gameObjects) {
        gameObject.update();
    }

    /*context.fillStyle = 'orange';
    lumination += luminationStep;
    if (lumination > 0.99) luminationStep = -0.01;
    if (lumination < 0.01) luminationStep = 0.01;

    context.fillStyle = "rgba(255, 140, 0, " + lumination + ")";
    context.fillRect(10, 10, 20, 20);*/
    drawBoard();
}

var game = new Game();
game.start();
