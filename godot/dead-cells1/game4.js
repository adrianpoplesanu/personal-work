/**
 * Dead Cells–style level generation: same graph + L-corridors as game2.js,
 * but rooms and corridors live in continuous (float) space — not aligned to
 * a tile grid. Rasterization to canvas pixels is only for drawing (same look).
 */

const N = 1;
const E = 2;
const S = 4;
const W = 8;

const canvas = document.getElementById("gameCanvas4");
const ctx = canvas.getContext("2d");

let board = [];
let boardW = 0;
let boardH = 0;

function init() {
  const data = generateWorld();
  board = data.grid;
  boardW = data.width;
  boardH = data.height;
  if (data.levelSpec) {
    console.log(JSON.stringify(data.levelSpec));
  }
  draw();
}

function rectsOverlap(a, b) {
  return (
    a.x < b.x + b.w &&
    a.x + a.w > b.x &&
    a.y < b.y + b.h &&
    a.y + a.h > b.y
  );
}

function roomCenter(room) {
  return {
    x: room.x + room.w / 2,
    y: room.y + room.h / 2,
  };
}

/** Point-in-union of axis-aligned rects (half-open on max edge). */
function pointInRects(px, py, rects) {
  for (const r of rects) {
    if (px >= r.x && px < r.x + r.w && py >= r.y && py < r.y + r.h) return true;
  }
  return false;
}

function emptyGrid(Wpx, Hpx) {
  const grid = [];
  for (let row = 0; row < Hpx; row++) {
    grid[row] = [];
    for (let col = 0; col < Wpx; col++) grid[row][col] = 0;
  }
  return { grid, width: Wpx, height: Hpx, levelSpec: null };
}

/**
 * Generate world: float rooms + float corridor strips; graph is same as game2.
 * Returns pixel bitmask grid sampled at cell centers (col+0.5, row+0.5).
 */
function generateWorld() {
  const Wpx = canvas.width;
  const Hpx = canvas.height;
  const margin = 8;
  const minRooms = 5;
  const maxRooms = 8;
  const numRooms = minRooms + Math.floor(Math.random() * (maxRooms - minRooms + 1));

  const minRoomW = 28;
  const maxRoomW = 110;
  const minRoomH = 28;
  const maxRoomH = 110;

  const corridorW = 10 + Math.random() * 10; // float, not tied to any tile module

  const rooms = [];
  const maxTotalTries = 8000;
  let tries = 0;
  while (rooms.length < numRooms && tries < maxTotalTries) {
    tries++;
    const rw = minRoomW + Math.random() * (maxRoomW - minRoomW);
    const rh = minRoomH + Math.random() * (maxRoomH - minRoomH);
    const rx = margin + Math.random() * Math.max(0.001, Wpx - 2 * margin - rw);
    const ry = margin + Math.random() * Math.max(0.001, Hpx - 2 * margin - rh);
    const candidate = { x: rx, y: ry, w: rw, h: rh };

    let ok = true;
    for (const other of rooms) {
      if (rectsOverlap(candidate, other)) {
        ok = false;
        break;
      }
    }
    if (ok) rooms.push(candidate);
  }

  const n = rooms.length;
  if (n < 2) {
    return emptyGrid(Wpx, Hpx);
  }

  const rects = rooms.map((r) => ({ x: r.x, y: r.y, w: r.w, h: r.h }));

  const edges = [];
  const connected = new Set([0]);

  while (connected.size < n) {
    const a = [...connected][Math.floor(Math.random() * connected.size)];
    let b = Math.floor(Math.random() * n);
    if (connected.has(b)) continue;
    edges.push([a, b]);
    connected.add(b);
  }

  const extraEdges = Math.floor(Math.random() * 2);
  for (let i = 0; i < extraEdges; i++) {
    const a = Math.floor(Math.random() * n);
    let b = Math.floor(Math.random() * n);
    if (a === b) continue;
    const sorted = [a, b].sort((x, y) => x - y);
    if (edges.some(([x, y]) => x === sorted[0] && y === sorted[1])) continue;
    edges.push([a, b]);
  }

  function addHorizontalRun(x0, y0, x1, y1, cw) {
    const xMin = Math.min(x0, x1);
    const xMax = Math.max(x0, x1);
    const w = xMax - xMin;
    if (w < 1e-6) return;
    rects.push({
      x: xMin,
      y: y0 - cw / 2,
      w,
      h: cw,
    });
  }

  function addVerticalRun(x0, y0, x1, y1, cw) {
    const yMin = Math.min(y0, y1);
    const yMax = Math.max(y0, y1);
    const h = yMax - yMin;
    if (h < 1e-6) return;
    rects.push({
      x: x0 - cw / 2,
      y: yMin,
      w: cw,
      h,
    });
  }

  function carveLCorridor(ax, ay, bx, by, cw, horizontalFirst) {
    if (horizontalFirst) {
      addHorizontalRun(ax, ay, bx, ay, cw);
      addVerticalRun(bx, ay, bx, by, cw);
    } else {
      addVerticalRun(ax, ay, ax, by, cw);
      addHorizontalRun(ax, by, bx, by, cw);
    }
  }

  const edgeHorizontalFirst = [];
  for (const [i, j] of edges) {
    const horizontalFirst = Math.random() < 0.5;
    edgeHorizontalFirst.push(horizontalFirst);
    const A = roomCenter(rooms[i]);
    const B = roomCenter(rooms[j]);
    carveLCorridor(A.x, A.y, B.x, B.y, corridorW, horizontalFirst);
  }

  function traversableAtSample(col, row) {
    const px = col + 0.5;
    const py = row + 0.5;
    return pointInRects(px, py, rects);
  }

  const grid = [];
  for (let row = 0; row < Hpx; row++) {
    grid[row] = [];
    for (let col = 0; col < Wpx; col++) {
      if (!traversableAtSample(col, row)) {
        grid[row][col] = 0;
        continue;
      }
      let openings = 0;
      if (row > 0 && traversableAtSample(col, row - 1)) openings |= N;
      if (col < Wpx - 1 && traversableAtSample(col + 1, row)) openings |= E;
      if (row < Hpx - 1 && traversableAtSample(col, row + 1)) openings |= S;
      if (col > 0 && traversableAtSample(col - 1, row)) openings |= W;
      grid[row][col] = openings;
    }
  }

  const levelSpec = {
    version: 1,
    width: Wpx,
    height: Hpx,
    corridorWidth: corridorW,
    rooms: rooms.map((r) => ({ x: r.x, y: r.y, w: r.w, h: r.h })),
    edges: edges.map((e) => [...e]),
    edgeHorizontalFirst,
  };

  return { grid, width: Wpx, height: Hpx, levelSpec };
}

function draw() {
  ctx.fillStyle = "#0d1117";
  ctx.fillRect(0, 0, canvas.width, canvas.height);

  const cell = 1;
  for (let row = 0; row < boardH; row++) {
    for (let col = 0; col < boardW; col++) {
      const x = col * cell;
      const y = row * cell;
      const tile = board[row][col];

      if (tile === 0) {
        drawBlockedTile(x, y, cell);
      } else {
        drawMazeTile(x, y, tile, cell);
      }
    }
  }
}

function drawBlockedTile(x, y, size) {
  ctx.fillStyle = "#dc2626";
  ctx.fillRect(x, y, size, size);
  ctx.strokeStyle = "#991b1b";
  ctx.lineWidth = 1;
  ctx.strokeRect(x, y, size, size);
}

function drawMazeTile(x, y, tile, size) {
  const cellColor = "#1e293b";
  const edgeColor = "#dc2626";
  const edgeWidth = 2;

  ctx.fillStyle = cellColor;
  ctx.fillRect(x, y, size, size);

  ctx.strokeStyle = edgeColor;
  ctx.lineWidth = edgeWidth;
  ctx.lineCap = "square";

  if (!(tile & N)) {
    ctx.beginPath();
    ctx.moveTo(x, y);
    ctx.lineTo(x + size, y);
    ctx.stroke();
  }
  if (!(tile & E)) {
    ctx.beginPath();
    ctx.moveTo(x + size, y);
    ctx.lineTo(x + size, y + size);
    ctx.stroke();
  }
  if (!(tile & S)) {
    ctx.beginPath();
    ctx.moveTo(x + size, y + size);
    ctx.lineTo(x, y + size);
    ctx.stroke();
  }
  if (!(tile & W)) {
    ctx.beginPath();
    ctx.moveTo(x, y + size);
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
