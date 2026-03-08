/**
 * Dead Cells–style level generation: graph/path structure
 * - Rooms as nodes, corridors as edges
 * - Same tiling: 20x20, blocked (0) or traversable with N/E/S/W openings
 * - Same drawing: blocked = red fill, traversable = dark fill + red blocked edges
 */

const BOARD_SIZE = 20;
const TILE_SIZE = 30;

const N = 1;
const E = 2;
const S = 4;
const W = 8;

const canvas = document.getElementById("gameCanvas2");
const ctx = canvas.getContext("2d");

let board = [];

function init() {
  board = generateWorld();
  draw();
}

/**
 * Key for set of cells: "row,col"
 */
function key(r, c) {
  return `${r},${c}`;
}

/**
 * Generate world using graph structure:
 * 1. Place rooms (rectangular blobs) at random positions
 * 2. Build a connection graph (spanning tree + optional extra edges)
 * 3. Carve corridors between connected rooms
 * 4. Build 20x20 board: traversable cells get openings from neighbors; rest blocked
 */
function generateWorld() {
  const traversable = new Set();

  // --- 1. Room parameters and placement ---
  const minRooms = 5;
  const maxRooms = 8;
  const numRooms = minRooms + Math.floor(Math.random() * (maxRooms - minRooms + 1));
  const padding = 2;
  const margin = 1;

  const rooms = [];
  for (let i = 0; i < numRooms; i++) {
    const w = 2 + Math.floor(Math.random() * 2); // 2 or 3
    const h = 2 + Math.floor(Math.random() * 2);
    const maxR = BOARD_SIZE - padding - h;
    const maxC = BOARD_SIZE - padding - w;
    const r = padding + Math.floor(Math.random() * Math.max(1, maxR - padding));
    const c = padding + Math.floor(Math.random() * Math.max(1, maxC - padding));
    rooms.push({ r, c, w, h });
  }

  // Add all room cells to traversable
  for (const room of rooms) {
    for (let dr = 0; dr < room.h; dr++) {
      for (let dc = 0; dc < room.w; dc++) {
        traversable.add(key(room.r + dr, room.c + dc));
      }
    }
  }

  // --- 2. Graph: which rooms are connected (spanning tree + branches) ---
  const edges = []; // list of [roomIndexA, roomIndexB]
  const connected = new Set([0]);

  while (connected.size < numRooms) {
    const a = [...connected][Math.floor(Math.random() * connected.size)];
    let b = Math.floor(Math.random() * numRooms);
    if (connected.has(b)) continue;
    edges.push([a, b]);
    connected.add(b);
  }

  // Optional extra edges for more loops (branching paths)
  const extraEdges = Math.floor(Math.random() * 2);
  for (let i = 0; i < extraEdges; i++) {
    const a = Math.floor(Math.random() * numRooms);
    let b = Math.floor(Math.random() * numRooms);
    if (a === b) continue;
    const sorted = [a, b].sort((x, y) => x - y);
    if (edges.some(([x, y]) => (x === sorted[0] && y === sorted[1]))) continue;
    edges.push([a, b]);
  }

  // --- 3. Carve corridors between connected rooms ---
  function roomCenter(room) {
    return {
      r: room.r + Math.floor(room.h / 2),
      c: room.c + Math.floor(room.w / 2),
    };
  }

  function carveCorridor(r0, c0, r1, c1) {
    let r = r0;
    let c = c0;
    // L-shaped: first horizontal then vertical (or random order)
    const goHorizontalFirst = Math.random() < 0.5;
    if (goHorizontalFirst) {
      while (c !== c1) {
        c += c1 > c ? 1 : -1;
        traversable.add(key(r, c));
      }
      while (r !== r1) {
        r += r1 > r ? 1 : -1;
        traversable.add(key(r, c));
      }
    } else {
      while (r !== r1) {
        r += r1 > r ? 1 : -1;
        traversable.add(key(r, c));
      }
      while (c !== c1) {
        c += c1 > c ? 1 : -1;
        traversable.add(key(r, c));
      }
    }
  }

  for (const [i, j] of edges) {
    const A = roomCenter(rooms[i]);
    const B = roomCenter(rooms[j]);
    carveCorridor(A.r, A.c, B.r, B.c);
  }

  // --- 4. Build 20x20 board: tile = 0 blocked, else bitmask of open directions ---
  const grid = [];
  for (let row = 0; row < BOARD_SIZE; row++) {
    grid[row] = [];
    for (let col = 0; col < BOARD_SIZE; col++) {
      if (!traversable.has(key(row, col))) {
        grid[row][col] = 0;
        continue;
      }
      let openings = 0;
      if (row > 0 && traversable.has(key(row - 1, col))) openings |= N;
      if (col < BOARD_SIZE - 1 && traversable.has(key(row, col + 1))) openings |= E;
      if (row < BOARD_SIZE - 1 && traversable.has(key(row + 1, col))) openings |= S;
      if (col > 0 && traversable.has(key(row, col - 1))) openings |= W;
      grid[row][col] = openings;
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

function drawMazeTile(x, y, tile) {
  const cellColor = "#1e293b";
  const edgeColor = "#dc2626";
  const edgeWidth = 2;

  ctx.fillStyle = cellColor;
  ctx.fillRect(x, y, TILE_SIZE, TILE_SIZE);

  ctx.strokeStyle = edgeColor;
  ctx.lineWidth = edgeWidth;
  ctx.lineCap = "square";

  if (!(tile & N)) {
    ctx.beginPath();
    ctx.moveTo(x, y);
    ctx.lineTo(x + TILE_SIZE, y);
    ctx.stroke();
  }
  if (!(tile & E)) {
    ctx.beginPath();
    ctx.moveTo(x + TILE_SIZE, y);
    ctx.lineTo(x + TILE_SIZE, y + TILE_SIZE);
    ctx.stroke();
  }
  if (!(tile & S)) {
    ctx.beginPath();
    ctx.moveTo(x + TILE_SIZE, y + TILE_SIZE);
    ctx.lineTo(x, y + TILE_SIZE);
    ctx.stroke();
  }
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
