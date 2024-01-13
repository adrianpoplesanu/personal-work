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

function loadImageAndCreateTextureInfo(url) {
    var tex = gl.createTexture();
    gl.bindTexture(gl.TEXTURE_2D, tex);
    // Fill the texture with a 1x1 blue pixel.
    gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, 1, 1, 0, gl.RGBA, gl.UNSIGNED_BYTE,
                  new Uint8Array([0, 0, 255, 255]));

    // let's assume all images are not a power of 2
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);

    var textureInfo = {
      width: 1,   // we don't know the size until it loads
      height: 1,
      texture: tex,
    };
    var img = new Image();
    img.addEventListener('load', function() {
      textureInfo.width = img.width;
      textureInfo.height = img.height;

      gl.bindTexture(gl.TEXTURE_2D, textureInfo.texture);
      gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, img);
    });
    img.src = url;

    return textureInfo;
}

function clear() {
    // clear the canvas
    webgl.clearColor(0.1, 0.1, 0.1, 1.0);
    webgl.clear(webgl.COLOR_BUFFER_BIT);
}

function init() {
    var vertexShaderSource = document.querySelector("#vertex-shader-2d").text;
    var fragmentShaderSource = document.querySelector("#fragment-shader-2d").text;

    var drawImageVertexShaderSource = document.querySelector("#drawImage-vertex-shader").text;
    var drawImageFragmentShaderSource = document.querySelector("#drawImage-fragment-shader").text;

    var vertexShader = createShader(webgl, webgl.VERTEX_SHADER, vertexShaderSource);
    var fragmentShader = createShader(webgl, webgl.FRAGMENT_SHADER, fragmentShaderSource);

    var drawImageVertexShader = createShader(webgl, webgl.VERTEX_SHADER, drawImageVertexShaderSource);
    var drawImageFragmentShader = createShader(webgl, webgl.FRAGMENT_SHADER, drawImageFragmentShaderSource);
    console.log("draw image shaders loaded!");

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
