var canvas = document.getElementById("canvas");
var context = canvas.getContext("2d");

var width = 800;
var height = 600;

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
    var tabla = [[0, 0], [0, 0]];
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
            context.drawImage(terrain, 33 * i + 1, 33 * j + 1, 32, 32, i * 32, j * 32, 32, 32);
        }
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

function init() {
    game = new Game();
}

function loop() {
    game.update();
    game.draw();
}

init();
setInterval(loop, 1000/30);