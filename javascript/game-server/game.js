var canvas = document.getElementById("canvas");
var context = canvas.getContext("2d");

function clearScreen() {
    context.fillStyle = 'black';
    context.fillRect(0, 0, canvas.width, canvas.height);
}

clearScreen();
