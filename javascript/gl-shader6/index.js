console.log("bd engine running...");

var canvas = document.querySelector("#canvas");
var webgl = canvas.getContext("webgl");
var program;
var offset = 0.0;

function createShader(webgl, type, source) {
    var shader = webgl.createShader(type);
    webgl.shaderSource(shader, source);
    webgl.compileShader(shader);
    var success = webgl.getShaderParameter(shader, webgl.COMPILE_STATUS);
    if (success) {
        return shader;
    }

    console.log(webgl.getShaderInfoLog(shader));
    webgl.deleteShader(shader);
}

function createProgram(webgl, vertexShader, fragmentShader) {
    var program = webgl.createProgram();
    webgl.attachShader(program, vertexShader);
    webgl.attachShader(program, fragmentShader);
    webgl.linkProgram(program);
    var success = webgl.getProgramParameter(program, webgl.LINK_STATUS);
    if (success) {
        return program;
    }

  console.log(webgl.getProgramInfoLog(program));
  webgl.deleteProgram(program);
}

function clear() {
    // clear the canvas
    webgl.clearColor(0.1, 0.1, 0.1, 1.0);
    webgl.clear(webgl.COLOR_BUFFER_BIT);
}

function init() {
    var vertexShaderSource = document.querySelector("#vertex-shader-2d").text;
    var fragmentShaderSource = document.querySelector("#fragment-shader-2d").text;

    var vertexShader = createShader(webgl, webgl.VERTEX_SHADER, vertexShaderSource);
    var fragmentShader = createShader(webgl, webgl.FRAGMENT_SHADER, fragmentShaderSource);

    program = createProgram(webgl, vertexShader, fragmentShader);

    var positionAttributeLocation = webgl.getAttribLocation(program, "a_position");

    var positionBuffer = webgl.createBuffer();

    webgl.bindBuffer(webgl.ARRAY_BUFFER, positionBuffer);

    // END init

    webgl.viewport(0, 0, webgl.canvas.width, webgl.canvas.height);

    webgl.useProgram(program);

    webgl.enableVertexAttribArray(positionAttributeLocation);

    webgl.bindBuffer(webgl.ARRAY_BUFFER, positionBuffer);

    var size = 2;             // 2 components per iteration
    var type = webgl.FLOAT;   // the data is 32bit floats
    var normalize = false;    // don't normalize the data
    var stride = 0;           // 0 = move forward size * sizeof(type) each iteration to get the next position
    var offset = 0;           // start at the beginning of the buffer
    webgl.vertexAttribPointer(
        positionAttributeLocation, size, type, normalize, stride, offset);
}

function render() {
    var primitiveType = webgl.TRIANGLES;
    var offset = 0;
    var count = 3;
    webgl.drawArrays(primitiveType, offset, count);
}

function add_draw_positions() {
    var positions = [
        0 + offset, 0,
        0 + offset, 0.5,
        0.7 + offset, 0,
    ];

    webgl.bufferData(webgl.ARRAY_BUFFER, new Float32Array(positions), webgl.STATIC_DRAW);
}

function update() {
    offset += 0.01;
    if (offset >= 1.0) offset = -1.0;

    add_draw_positions();
    clear();
    render();
    requestAnimationFrame(update);
}

init();
update();
