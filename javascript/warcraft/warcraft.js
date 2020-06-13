var canvas = document.getElementById("canvas");
var context = canvas.getContext("2d");

var width = 800;
var height = 600;

var mousex = 50;
var mousey = 50;
var offsetX = 0;
var offsetY = 0;
var accOffsetX = 0;
var accOffsetY = 0;

var game;
// ATENTIE! - formatul unei unitati: 12345100 : 1 - playernum, 2 - unit tyoe, 345 - unit action, 100 - hit points
// example: 1205095: player 1, grunt, doing action 5, having 95 hit points
// player_ nums: 1, 2
// unit_ type: 1 - peon, 2 - grunt, 3 - etc
// unit_ action: 100 - walking up, 200 - walking down ... ; this also gives some stage indicators
// hit_ points: yeah, life
// TODO: store target - maybe each player should have a list of units, so you know which one is targeted
// THIS IS THE MOST IMPORTANT STUFF - THIS MAKES OR BREAKS THE GAME

function drawRectangle (x, y, sizex, sizey, color) {
    context.beginPath();
    context.fillStyle = color;
    context.rect(x, y, sizex, sizey);
    context.fill();
}

function pathFinder (current_point, destination_point) {
    current_point = { x : 1, y : 2};
    destination_point = { x : 4, y : 4};
    next_step = { x : 1, y : 1};
    return next_step;
}

function Game () {
    //var tabla = [[0, 0], [0, 0]];
    this.tabla = [
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 2, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 7, 1, 1, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 6, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 4, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    ];
    var units = [[], []]; // it's just o juxtapunere for tabla
};

Game.prototype.update = function () {

}

Game.prototype.clearScreen = function () {
    drawRectangle (0, 0, width, height, "black");
}

Game.prototype.draw = function () {
    this.clearScreen();
    // syntax: 0, 0 - x, y starting point from the image, 10, 10 - x, y end point from the image, 0, 0 - starting canvas point where to draw, 100, 100 - end point where to draw
    // context.drawImage(terrain, 0, 0, 10, 10, 0, 0, 100, 100);
    // it looks like the tile size is 34, let's test this
    //context.drawImage(terrain, 0, 0, 34, 34, 0, 0, 100, 100);
    var i = 0;
    var j = 0;
    for (i = 0; i < 20; i++) {
        for (j = 0; j < 16; j++) {
            //context.drawImage(terrain, 33 * i + 1, 33 * j + 1, 32, 32, i * 32, j * 32, 32, 32);
            switch (game.tabla[j][i]) {
                case 0:
                    context.drawImage(terrain, 33 * 1 + 1, 33 * 6 + 1, 32, 32, i * 32 + offsetX, j * 32 + offsetY, 32, 32); // done
                break;
                case 1:
                    context.drawImage(terrain, 33 * 24 + 1, 33 * 9 + 1, 32, 32, i * 32, j * 32, 32, 32); // done
                break;
                case 2:
                    context.drawImage(terrain, 33 * 28 + 1, 33 * 7 + 1, 32, 32, i * 32, j * 32, 32, 32);
                break;
                case 3:
                    context.drawImage(terrain, 33 * 29 + 1, 33 * 10 + 1, 32, 32, i * 32, j * 32, 32, 32); // done
                break;
                case 4:
                    context.drawImage(terrain, 33 * 1 + 1, 33 * 6 + 1, 32, 32, i * 32, j * 32, 32, 32);
                break;
                case 5:
                    context.drawImage(terrain, 33 * 24 + 1, 33 * 15 + 1, 32, 32, i * 32, j * 32, 32, 32); // done
                break;
                case 6:
                    context.drawImage(terrain, 33 * 1 + 1, 33 * 6 + 1, 32, 32, i * 32, j * 32, 32, 32);
                break;
                case 7:
                    context.drawImage(terrain, 33 * 1 + 1, 33 * 6 + 1, 32, 32, i * 32, j * 32, 32, 32);
                break;
                case 8:
                    context.drawImage(terrain, 33 * 24 + 1, 33 * 7 + 1, 32, 32, i * 32, j * 32, 32, 32); // done
                break;
                case 9:
                    context.drawImage(terrain, 33 * 28 + 1, 33 * 8 + 1, 32, 32, i * 32, j * 32, 32, 32); // done
                break;
            }
        }
    }
}

Game.prototype.drawMouse = function () {
    context.fillStyle = "#f00";
    context.beginPath();
    context.arc(mousex, mousey, RADIUS, 0, degToRad(360), true);
    context.fill();
}

Game.prototype.calculateOffset = function () {
    if (mousex == 0) {
        if (accOffsetX < 20) accOffsetX++;
        offsetX += accOffsetX;
    } else if (mousex >= canvas.width) {
        if (accOffsetX < 20) accOffsetX++;
        offsetX -= accOffsetX;
    } else {
        accOffsetX = 5;
    }
    if (mousey == 0) {
        if (accOffsetY < 20) accOffsetY++;
        offsetY += accOffsetY;
    } else if (mousey >= canvas.height) {
        if (accOffsetY < 20) accOffsetY++;
        offsetY -= accOffsetY;
    } else {
        accOffsetY = 5;
    }
}

function Player () {
    this.playerName = "UnknownPlayer";
    this.number = 0; // 1 or 2; 0 not instantiated
    this.fieldOfViewMatrix = [[], []]; // tabla size
}

Player.prototype.drawUnits = function () {

}

Player.prototype.drawBuildings = function () {

}

// MOUSE HANDLING START
const RADIUS = 20;

function degToRad(degrees) {
  var result = Math.PI / 180 * degrees;
  return result;
}

canvas.requestPointerLock = canvas.requestPointerLock || canvas.mozRequestPointerLock;

document.exitPointerLock = document.exitPointerLock || document.mozExitPointerLock;

canvas.onclick = function() {
    canvas.requestPointerLock();
};

// pointer lock event listeners

// Hook pointer lock state change events for different browsers
document.addEventListener('pointerlockchange', lockChangeAlert, false);
document.addEventListener('mozpointerlockchange', lockChangeAlert, false);

function lockChangeAlert() {
    if (document.pointerLockElement === canvas || document.mozPointerLockElement === canvas) {
        console.log('The pointer lock status is now locked');
        document.addEventListener("mousemove", updatePosition, false);
    } else {
        console.log('The pointer lock status is now unlocked');
        document.removeEventListener("mousemove", updatePosition, false);
    }
}

function updatePosition(e) {
    //mousex += e.movementX; // do the add only if it needs to
    //mousey += e.movementY; // do the add only if it needs to
    var limitedx = false;
    var limitedy = false;
    if (mousex + e.movementX >= canvas.width) {
        mousex = canvas.width;
        limitedx = true;
        // i need to adjust the offset
        //offsetX -= 5; // this needs to be done in a different place
    }
    if (mousey + e.movementY >= canvas.height) {
        mousey = canvas.height;
        limitedy = true;
        // i need to adjust the offset
        //offsetY -= 5; // this needs to be done in a different place
    }
    if (mousex + e.movementX <= 0) {
        mousex = 0;
        limitedx = true;
        // i need to adjust the offset
        //offsetX += 5; // this needs to be done in a different place
    }
    if (mousey + e.movementY <= 0) {
        mousey = 0;
        limitedy = true;
        // i need to adjust the offset
        //offsetY += 5; // this needs to be done in a different place
    }
    if (!limitedx) mousex += e.movementX;
    if (!limitedy) mousey += e.movementY;
}
// MOUSE HANDLING STOP

function init() {
    game = new Game();
}

function loop() {
    game.update();
    game.draw();
    game.calculateOffset();
    game.drawMouse(); // this probably needs to be moved to draw() function
}

init();
setInterval(loop, 1000/30);