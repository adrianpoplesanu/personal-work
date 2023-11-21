var canvas = document.getElementById("canvas");
var context = canvas.getContext("2d");

var height = canvas.height;
var width = canvas.width;

function clearScreen() {
    context.fillStyle = 'black';
    context.fillRect(0, 0, width, height);
}

function testImageRendering(x, y, alpha) {
    const img = document.getElementById("tile1");
    context.globalAlpha = alpha;
    context.drawImage(img, x, y, 10, 10);
    context.globalAlpha = 1;
}

clearScreen();
for (var i = 0; i < 10; i++) {
    for (var j = 0; j < 10; j++) {
        var a = Math.random();
        testImageRendering(i * 10, j * 10, a);
    }
}
