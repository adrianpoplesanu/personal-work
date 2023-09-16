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

class Sprite {
    constructor(name) {
        console.log(name);
    }
}

var sprite = new Sprite("bebe dex");

class GameLoop {
    test() {
        console.log("in game loop");
    }

    update() {
        console.log("gameloop.update");
    }
}

var gameLoop = new GameLoop();
gameLoop.test();

function animate() {
    window.requestAnimationFrame(animate);
    //console.log("go");
}

animate();
