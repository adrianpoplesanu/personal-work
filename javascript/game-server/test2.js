var canvas = document.getElementById("canvas");
var context = canvas.getContext("2d");

var height = canvas.height;
var width = canvas.width;

var framesPerSecond = 30;
var lumination = 0;
var luminationStep = 0.00;

var board;
var boardWidth = 30;
var boardHeight = 30;

var upArrow = 38;
var downArrow = 40;
var leftArrow = 37;
var rightArrow = 39;
var spaceKey = 32;
var escapeKey = 27;
var movementKey;

var keystate = {};

var playerX, playerY, opponentX, opponentY;

window.addEventListener("keydown", function(e) {
    // space and arrow keys
    if (e.keyCode == escapeKey) {
        e.preventDefault();
        window.location.reload();
    }
    if([spaceKey, leftArrow, upArrow, rightArrow, downArrow].indexOf(e.keyCode) > -1) {
        e.preventDefault();
        //keystate[event.keyCode] = true;
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

function handleInput() {
    if (keystate[downArrow]) {
        moveDown();
    }
    if (keystate[upArrow]) {
        moveUp();
    }
    if (keystate[leftArrow]) {
        moveLeft();
    }
    if (keystate[rightArrow]) {
        moveRight();
    }
}

function canMove(deltaX, deltaY) {
    if (player.state > 0) return false;
    if (board[player.x + deltaX][player.y + deltaY].type == 0) return true;
    return false;
}

function moveDown() {
    if (canMove(0, 1)) {
        //playerY++;
        player.deltaY = 1;
        player.state = 16;
    }
}

function moveUp() {
    if (canMove(0, -1)) {
        //playerY--;
        player.deltaY = -1;
        player.state = 16;
    }
}

function moveLeft() {
    if (canMove(-1, 0)) {
        //playerX--;
        player.deltaX = -1;
        player.state = 16;
    }
}

function moveRight() {
    if (canMove(1, 0)) {
        //playerX++;
        player.deltaX = 1;
        player.state = 16;
    }
}

function clearScreen() {
    context.fillStyle = 'black';
    context.fillRect(0, 0, width, height);
}

function testImageRendering(x, y, alpha) {
    const img = document.getElementById("tile1");
    context.globalAlpha = alpha;
    context.drawImage(img, x, y, 16, 16);
    context.globalAlpha = 1;
}

/*clearScreen();
for (var i = 0; i < 10; i++) {
    for (var j = 0; j < 10; j++) {
        var a = Math.random();
        testImageRendering(i * 10, j * 10, a);
    }
}*/

function generateTile(x, y) {
    if (x == 0 || y == 0 || y == boardWidth - 1 || x == boardHeight - 1) {
        return 27;
    }
    return 0;
}

function generateBoard(boardWidth, boardHeight) {
    board = new Array(boardHeight);
    for (var i = 0; i < boardHeight; i++) {
        board[i] = new Array(boardWidth);
        for (var j = 0; j < boardWidth; j++) {
            board[i][j] = {
                type: generateTile(i, j),
                alpha: 1,
                y: i,
                x: j
            }
        }
    }
    return board;
}

function clearScreen() {
    context.fillStyle = 'black';
    context.fillRect(0, 0, width, height);
}

function drawSquare(element) {
    //...
    var red = 255;
    var green = 140;
    var blue = 0;
    var lumination = element.alpha;
    if (element.type == 27) {
        red = 77;
        green = 77;
        blue = 77;
    }
    if (element.type == 0) {
        red = 0;
        green = 0;
        blue = 0;
    }
    context.fillStyle = "rgba(" + red + ", " + green + ", " + blue + ", " + lumination + ")";
    context.fillRect(element.x * 16, element.y * 16, 16, 16);
}

function drawBoard() {
    for (var i = 0; i < boardHeight; i++) {
        for (var j = 0; j < boardWidth; j++) {
            drawSquare(board[i][j]);
        }
    }
}

function movePlayer() {
    if (player.state > 0) {
        player.state--;
    }
    if (player.state == 0) {
        player.x += player.deltaX;
        player.y += player.deltaY;
        player.deltaX = 0;
        player.deltaY = 0;
    }
}

function drawPlayer() {
    context.fillStyle = "rgba(255, 255, 255, 1)";
    context.fillRect(player.x * 16 + (16 - player.state) * player.deltaX, player.y * 16 + (16 - player.state) * player.deltaY, 16, 16);
}

function Player() {
    this.state = 0;
    this.x = 1;
    this.y = 1;
    this.deltaX = 0;
    this.deltaY = 0;
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
    playerX = 1;
    playerY = 1;
    for (gameObject in game.gameObjects) {
        gameObject.start();
    }
    //generateRandomBoard(boardWidth, boardHeight);
    generateBoard(boardWidth, boardHeight);
    //setInterval(game.update, 1000/framesPerSecond);
    game.update();
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
    handleInput();
    drawBoard();
    movePlayer();
    drawPlayer();
    window.requestAnimationFrame(game.update);
}

var game = new Game();
var player = new Player();
game.start();
