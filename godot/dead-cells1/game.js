/**
 * Maze World - Phase 1: Board & World Generation
 * 20x20 matrix, each tile: 0 = blocked, 1-15 = maze cell (4 bits: N, E, S, W openings)
 */

const BOARD_SIZE = 20;
const TILE_SIZE = 30; // 20 * 30 = 600px canvas

// Bit flags for maze cell openings (which edge is open to neighbor)
const N = 1;  // North (up)
const E = 2;  // East (right)
const S = 4;  // South (down)
const W = 8;  // West (left)

const canvas = document.getElementById("gameCanvas");
const ctx = canvas.getContext("2d");

// 20x20 board: 0 = blocked, 1-15 = maze cell with openings encoded in bits
let board = [];

function init() {
  board = generateWorld();
  draw();
}

/**
 * Generate random world: each tile is either blocked (0) or a maze cell (1-15).
 * Maze cell value = bitmask of open sides (N|E|S|W).
 */
function generateWorld() {
  const grid = [];
  for (let row = 0; row < BOARD_SIZE; row++) {
    grid[row] = [];
    for (let col = 0; col < BOARD_SIZE; col++) {
      // ~30% blocked, ~70% maze cells
      const isBlocked = Math.random() < 0.3;
      if (isBlocked) {
        grid[row][col] = 0;
      } else {
        // Random subset of open directions (each direction 50% chance)
        let openings = 0;
        if (Math.random() < 0.5) openings |= N;
        if (Math.random() < 0.5) openings |= E;
        if (Math.random() < 0.5) openings |= S;
        if (Math.random() < 0.5) openings |= W;
        // Ensure at least one opening so it's not drawn like a full block
        if (openings === 0) openings = N | E;
        grid[row][col] = openings;
      }
    }
  }
  return grid;
}

function draw() {
  ctx.fillStyle = "#0d1117";
  ctx.fillRect(0, 0, canvas.width, canvas.height);

  for (let row = 0; row < BOARD_SIZE; row++) {
    for (let col = 0; col < BOARD_SIZE; col++) {
      const x = col * TILE_SIZE;
      const y = row * TILE_SIZE;
      const tile = board[row][col];

      if (tile === 0) {
        drawBlockedTile(x, y);
      } else {
        drawMazeTile(x, y, tile);
      }
    }
  }
}

function drawBlockedTile(x, y) {
  ctx.fillStyle = "#dc2626";
  ctx.fillRect(x, y, TILE_SIZE, TILE_SIZE);
  ctx.strokeStyle = "#991b1b";
  ctx.lineWidth = 1;
  ctx.strokeRect(x, y, TILE_SIZE, TILE_SIZE);
}

/**
 * Draw maze cell: fill with dark color, draw red edges where access is blocked.
 * tile is a bitmask: N=1, E=2, S=4, W=8. If bit is set, that side is open (no red edge).
 */
function drawMazeTile(x, y, tile) {
  const cellColor = "#1e293b";
  const edgeColor = "#dc2626";
  const edgeWidth = 2;

  ctx.fillStyle = cellColor;
  ctx.fillRect(x, y, TILE_SIZE, TILE_SIZE);

  ctx.strokeStyle = edgeColor;
  ctx.lineWidth = edgeWidth;
  ctx.lineCap = "square";

  // Top edge: red if no connection to north
  if (!(tile & N)) {
    ctx.beginPath();
    ctx.moveTo(x, y);
    ctx.lineTo(x + TILE_SIZE, y);
    ctx.stroke();
  }
  // Right edge: red if no connection to east
  if (!(tile & E)) {
    ctx.beginPath();
    ctx.moveTo(x + TILE_SIZE, y);
    ctx.lineTo(x + TILE_SIZE, y + TILE_SIZE);
    ctx.stroke();
  }
  // Bottom edge: red if no connection to south
  if (!(tile & S)) {
    ctx.beginPath();
    ctx.moveTo(x + TILE_SIZE, y + TILE_SIZE);
    ctx.lineTo(x, y + TILE_SIZE);
    ctx.stroke();
  }
  // Left edge: red if no connection to west
  if (!(tile & W)) {
    ctx.beginPath();
    ctx.moveTo(x, y + TILE_SIZE);
    ctx.lineTo(x, y);
    ctx.stroke();
  }
}

init();

document.addEventListener("keydown", (e) => {
  if (e.key === "r" || e.key === "R") {
    init();
  }
});
