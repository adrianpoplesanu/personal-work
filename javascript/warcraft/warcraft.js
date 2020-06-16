var canvas = document.getElementById("canvas");
var context = canvas.getContext("2d");

//var fog = document.getElementById("fog");
//var ctx_fog = fog.getContext("2d");

var width = 800;
var height = 600;

var mousex = 50;
var mousey = 50;
var offsetX = 0;
var offsetY = 0;
var accOffsetX = 0;
var accOffsetY = 0;

var game;
var player1, player2;
// ATENTIE!!! TREBUIE SA MA GANDESC CA LUMEA LA ASTA
// ATENTIE! - formatul unei unitati: 12345100 : 1 - playernum, 2 - unit tyoe, 345 - unit action, 100 - hit points
// example: 1205095: player 1, grunt, doing action 5, having 95 hit points
// player_ nums: 1, 2
// unit_ type: 1 - peon, 2 - grunt, 3 - etc
// unit_ action: 100 - walking up, 200 - walking down ... ; this also gives some stage indicators
// hit_ points: yeah, life
// TODO: store target - maybe each player should have a list of units, so you know which one is targeted
// THIS IS THE MOST IMPORTANT STUFF - THIS MAKES OR BREAKS THE GAME

//VARIANTA 2
// sa fie o "tabla" cu unitati - numarul playerului si id-ul unitatii
// id-ul unitatii este indexul din lista de unitati
// lista de unitati e formata obiecte care au mai multe informatii

//VARIANTA 3
// sa fie o tabla cu format: 1234567890123
// 1 - player
// 2 - unit type
// 34 - index
// 56 - target
// NU CRED CA MERGE

function drawRectangle (x, y, sizex, sizey, color) {
    context.beginPath();
    context.fillStyle = color;
    context.rect(x, y, sizex, sizey);
    context.fill();
}

function drawFog (x, y, sizex, sizey, color) {
    ctx_fog.beginPath();
    ctx_fog.fillStyle = color;
    ctx_fog.rect(x, y, sizex, sizey);
    ctx_fog.fill();
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
        /*[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
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
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],*/
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    ];
    this.units = [
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    ];
    //var units = [[], []]; // it's just o juxtapunere for tabla
};

Game.prototype.update = function () {

}

Game.prototype.clearScreen = function () {
    drawRectangle (0, 0, width, height, "black");
}

Game.prototype.draw = function (playerNum) {
    this.clearScreen();
    // syntax: 0, 0 - x, y starting point from the image, 10, 10 - x, y end point from the image, 0, 0 - starting canvas point where to draw, 100, 100 - end point where to draw
    // context.drawImage(terrain, 0, 0, 10, 10, 0, 0, 100, 100);
    // it looks like the tile size is 34, let's test this
    //context.drawImage(terrain, 0, 0, 34, 34, 0, 0, 100, 100);
    var i = 0;
    var j = 0;
    for (i = 0; i < 25; i++) {
        for (j = 0; j < 21; j++) {
            //context.drawImage(terrain, 33 * i + 1, 33 * j + 1, 32, 32, i * 32, j * 32, 32, 32);
            if (playerNum == 1) {
                if (player1.fieldOfViewMatrix[j][i] == 0) {
                    drawRectangle(offsetX + 32 * i, offsetY + 32 * j, 32, 32, "black");
                    continue;
                }
            }
            if (playerNum == 2) {
                if (player2.fieldOfViewMatrix[j][i] == 0) {
                    drawRectangle(offsetX + 32 * i, offsetY + 32 * j, 32, 32, "black");
                    continue;
                }
            }
            switch (game.tabla[j][i]) {
                case 0:
                    context.drawImage(terrain, 33 * 1 + 1, 33 * 6 + 1, 32, 32, i * 32 + offsetX, j * 32 + offsetY, 32, 32); // done
                break;
                case 1:
                    context.drawImage(terrain, 33 * 24 + 1, 33 * 9 + 1, 32, 32, i * 32 + offsetX, j * 32 + offsetY, 32, 32); // done
                break;
                case 2:
                    context.drawImage(terrain, 33 * 28 + 1, 33 * 7 + 1, 32, 32, i * 32 + offsetX, j * 32 + offsetY, 32, 32);
                break;
                case 3:
                    context.drawImage(terrain, 33 * 29 + 1, 33 * 10 + 1, 32, 32, i * 32 + offsetX, j * 32 + offsetY, 32, 32); // done
                break;
                case 4:
                    context.drawImage(terrain, 33 * 1 + 1, 33 * 6 + 1, 32, 32, i * 32 + offsetX, j * 32 + offsetY, 32, 32);
                break;
                case 5:
                    context.drawImage(terrain, 33 * 24 + 1, 33 * 15 + 1, 32, 32, i * 32 + offsetX, j * 32 + offsetY, 32, 32); // done
                break;
                case 6:
                    context.drawImage(terrain, 33 * 1 + 1, 33 * 6 + 1, 32, 32, i * 32 + offsetX, j * 32 + offsetY, 32, 32);
                break;
                case 7:
                    context.drawImage(terrain, 33 * 1 + 1, 33 * 6 + 1, 32, 32, i * 32 + offsetX, j * 32 + offsetY, 32, 32);
                break;
                case 8:
                    context.drawImage(terrain, 33 * 24 + 1, 33 * 7 + 1, 32, 32, i * 32 + offsetX, j * 32 + offsetY, 32, 32); // done
                break;
                case 9:
                    context.drawImage(terrain, 33 * 28 + 1, 33 * 8 + 1, 32, 32, i * 32 + offsetX, j * 32 + offsetY, 32, 32); // done
                break;
            }
        }
    }
    if (playerNum == 1) {
        var i;
        for (i = 0; i < player1.units.length; i++) {
            context.drawImage(archer, 8, 4, 20, 20, player1.units[i].x * 32 + offsetX, player1.units[i].y * 32 + offsetY, 32, 32);
        }
    }
    if (playerNum == 2) {

    }
}

Game.prototype.drawMouse = function () {
    //context.fillStyle = "#f00";
    //context.beginPath();
    //context.arc(mousex, mousey, RADIUS, 0, degToRad(360), true);
    context.drawImage(cursors, 3, 5 * 32 + 12, 31, 31, mousex, mousey, 20, 20);
    //context.fill();
}

Game.prototype.calculateOffset = function () {
    if (mousex == 0) {
        if (accOffsetX < 30) accOffsetX++;
        offsetX += accOffsetX;
    } else if (mousex >= canvas.width - 16) {
        if (accOffsetX < 30) accOffsetX++;
        offsetX -= accOffsetX;
    } else {
        accOffsetX = 5;
    }
    if (mousey == 0) {
        if (accOffsetY < 30) accOffsetY++;
        offsetY += accOffsetY;
    } else if (mousey >= canvas.height - 16) {
        if (accOffsetY < 30) accOffsetY++;
        offsetY -= accOffsetY;
    } else {
        accOffsetY = 5;
    }
}

function Player () {
    this.playerName = "UnknownPlayer";
    this.number = 0; // 1 or 2; 0 not instantiated
    this.fieldOfViewMatrix = [
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    ];
    this.units = [];
    this.selectedUnits = [];
    var u = new Unit();
    this.units.push(u);
}

Player.prototype.drawUnits = function () {

}

Player.prototype.drawBuildings = function () {

}

function Unit () {
    this.x = 5;
    this.y = 5;
    this.type = 1;
    this.hp = 100;
    this.speed = 1;
    this.damage_min = 2;
    this.damage_max = 4;
    this.target = {x: -1, y: -1};
    this.index = 0;
    this.owner = 0; // player 1 or player 2
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
        console.log("s-a dat un click x: " + mousex + "y: " + mousey);
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
    if (mousex + e.movementX >= canvas.width - 16) {
        mousex = canvas.width - 16;
        limitedx = true;
        // i need to adjust the offset
        //offsetX -= 5; // this needs to be done in a different place
    }
    if (mousey + e.movementY >= canvas.height - 16) {
        mousey = canvas.height - 16;
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

// fog of war
function FogOfWar () {
    drawFog (0, 0, width, height, "black");
}
// end fog of war

function init() {
    game = new Game();
    player1 = new Player();
    player1.playerName = "Adrianus";
    player2 = new Player();
    player1.playerName = "Ner'zhul";
}

function loop() {
    game.update();
    game.draw(1);
    //FogOfWar ();
    game.calculateOffset();
    game.drawMouse(); // this probably needs to be moved to draw() function
}

init();
setInterval(loop, 1000/30);