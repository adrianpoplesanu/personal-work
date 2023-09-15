var canvas = document.getElementById("canvas");
var context = canvas.getContext('2d');
var width = canvas.width;
var height = canvas.height;

function clear() {
    context.beginPath();
    //context.fillStyle = "black"; //"#556655";
    context.fillStyle = "#556655";
    context.rect(0, 0, width, height);
    context.fill();
}

clear();

function GameLoop() {

}

GameLoop.prototype.test = function() {
    console.log("in game loop");
}

var gameLoop = new GameLoop();
gameLoop.test()
