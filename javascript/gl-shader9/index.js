console.log("bd engine running...");

var canvas = document.querySelector("#canvas");
var webgl = canvas.getContext("webgl");
var program;
var offset = 0.0;
var positionBuffer;
var positionLocation;
var texcoordLocation;
var texcoordBuffer;
var matrixLocation;
var textureLocation;


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

function loadImageAndCreateTextureInfo(url) {
    var tex = webgl.createTexture();
    webgl.bindTexture(webgl.TEXTURE_2D, tex);
    // Fill the texture with a 1x1 blue pixel.
    webgl.texImage2D(webgl.TEXTURE_2D, 0, webgl.RGBA, 1, 1, 0, webgl.RGBA, webgl.UNSIGNED_BYTE,
                  new Uint8Array([0, 0, 255, 255]));

    // let's assume all images are not a power of 2
    webgl.texParameteri(webgl.TEXTURE_2D, webgl.TEXTURE_WRAP_S, webgl.CLAMP_TO_EDGE);
    webgl.texParameteri(webgl.TEXTURE_2D, webgl.TEXTURE_WRAP_T, webgl.CLAMP_TO_EDGE);
    webgl.texParameteri(webgl.TEXTURE_2D, webgl.TEXTURE_MIN_FILTER, webgl.LINEAR);

    var textureInfo = {
        width: 1,   // we don't know the size until it loads
        height: 1,
        texture: tex,
    };

    var img = new Image();
    //img.crossOrigin = "anonymous";
    img.addEventListener('load', function() {
        console.log("crazyness!");
        textureInfo.width = img.width;
        textureInfo.height = img.height;

        webgl.bindTexture(webgl.TEXTURE_2D, textureInfo.texture);
        webgl.texImage2D(webgl.TEXTURE_2D, 0, webgl.RGBA, webgl.RGBA, webgl.UNSIGNED_BYTE, img);
    });
    //img.crossOrigin = "anonymous";
    img.src = url;

    return textureInfo;
}

var textureInfos = [
    loadImageAndCreateTextureInfo('png/tile.png'),
];

function drawImage(tex, texWidth, texHeight, dstX, dstY) {
    webgl.bindTexture(webgl.TEXTURE_2D, tex);

    // Tell WebGL to use our shader program pair
    webgl.useProgram(program);

    // Setup the attributes to pull data from our buffers
    webgl.bindBuffer(webgl.ARRAY_BUFFER, positionBuffer);
    webgl.enableVertexAttribArray(positionLocation);
    webgl.vertexAttribPointer(positionLocation, 2, webgl.FLOAT, false, 0, 0);
    webgl.bindBuffer(webgl.ARRAY_BUFFER, texcoordBuffer);
    webgl.enableVertexAttribArray(texcoordLocation);
    webgl.vertexAttribPointer(texcoordLocation, 2, webgl.FLOAT, false, 0, 0);


    texcoordBuffer = webgl.createBuffer();
    webgl.bindBuffer(webgl.ARRAY_BUFFER, texcoordBuffer);

    // Put texcoords in the buffer
    var texcoords = [
        0, 0,
        0, 1,
        1, 0,
        1, 0,
        0, 1,
        1, 1,
    ];
    webgl.bufferData(webgl.ARRAY_BUFFER, new Float32Array(texcoords), webgl.STATIC_DRAW);

    // this matrix will convert from pixels to clip space
    var matrix = m4.orthographic(0, webgl.canvas.width, webgl.canvas.height, 0, -1, 1);

    // this matrix will translate our quad to dstX, dstY
    matrix = m4.translate(matrix, dstX, dstY, 0);

    // this matrix will scale our 1 unit quad
    // from 1 unit to texWidth, texHeight units
    matrix = m4.scale(matrix, texWidth, texHeight, 1);

    // Set the matrix.
    webgl.uniformMatrix4fv(matrixLocation, false, matrix);

    // Tell the shader to get the texture from texture unit 0
    webgl.uniform1i(textureLocation, 0);

    // draw the quad (2 triangles, 6 vertices)
    webgl.drawArrays(webgl.TRIANGLES, 0, 6);
}

var drawInfos = [];
var numToDraw = 1;
var speed = 60;
for (var ii = 0; ii < numToDraw; ++ii) {
    var drawInfo = {
        x: 100,
        y: 100,
        dx: 1,
        dy: 1,
        textureInfo: textureInfos[0],
    };
    drawInfos.push(drawInfo);
}
function drawImageOnCanvas() {
    drawInfos.forEach(function(drawInfo) {
        drawImage(
            drawInfo.textureInfo.texture,
            drawInfo.textureInfo.width,
            drawInfo.textureInfo.height,
            drawInfo.x,
            drawInfo.y);
    });
}

function clear() {
    // clear the canvas
    webgl.clearColor(0.1, 0.1, 0.1, 1.0);
    webgl.clear(webgl.COLOR_BUFFER_BIT);
}

function init() {
    //var vertexShaderSource = document.querySelector("#vertex-shader-2d").text;
    //var fragmentShaderSource = document.querySelector("#fragment-shader-2d").text;

    var drawImageVertexShaderSource = document.querySelector("#drawImage-vertex-shader").text;
    var drawImageFragmentShaderSource = document.querySelector("#drawImage-fragment-shader").text;

    //var vertexShader = createShader(webgl, webgl.VERTEX_SHADER, vertexShaderSource);
    //var fragmentShader = createShader(webgl, webgl.FRAGMENT_SHADER, fragmentShaderSource);

    var drawImageVertexShader = createShader(webgl, webgl.VERTEX_SHADER, drawImageVertexShaderSource);
    var drawImageFragmentShader = createShader(webgl, webgl.FRAGMENT_SHADER, drawImageFragmentShaderSource);
    console.log("draw image shaders loaded!");

    //program = createProgram(webgl, vertexShader, fragmentShader);
    program = createProgram(webgl, drawImageVertexShader, drawImageFragmentShader);

    //var positionAttributeLocation = webgl.getAttribLocation(program, "a_position");
    positionLocation = webgl.getAttribLocation(program, "a_position");
    texcoordLocation = webgl.getAttribLocation(program, "a_texcoord");

    matrixLocation = webgl.getUniformLocation(program, "u_matrix");
    textureLocation = webgl.getUniformLocation(program, "u_texture");

    positionBuffer = webgl.createBuffer();
    webgl.bindBuffer(webgl.ARRAY_BUFFER, positionBuffer);

    // Put a unit quad in the buffer
    var positions = [
        0, 0,
        0, 1,
        1, 0,
        1, 0,
        0, 1,
        1, 1,
    ];
    webgl.bufferData(webgl.ARRAY_BUFFER, new Float32Array(positions), webgl.STATIC_DRAW);

    texcoordBuffer = webgl.createBuffer();
    webgl.bindBuffer(webgl.ARRAY_BUFFER, texcoordBuffer);

    // Put texcoords in the buffer
    var texcoords = [
        0, 0,
        0, 1,
        1, 0,
        1, 0,
        0, 1,
        1, 1,
    ];
    webgl.bufferData(webgl.ARRAY_BUFFER, new Float32Array(texcoords), webgl.STATIC_DRAW);

    // END init
}

function update() {
    clear();
    drawImageOnCanvas();
    requestAnimationFrame(update);
}

init();
update();
