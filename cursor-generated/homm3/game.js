(() => {
    "use strict";

    // ── Tile types ──
    const TILE = {
        GRASS: 0, FOREST: 1, WATER: 2, MOUNTAIN: 3,
        ROAD: 4, CASTLE: 5, GOLD_MINE: 6, TREASURE: 7
    };

    const TILE_COLORS = {
        [TILE.GRASS]:     "#4a7c3f",
        [TILE.FOREST]:    "#2d5a27",
        [TILE.WATER]:     "#2a6496",
        [TILE.MOUNTAIN]:  "#6b6b6b",
        [TILE.ROAD]:      "#8b7d5e",
        [TILE.CASTLE]:    "#7c3a3a",
        [TILE.GOLD_MINE]: "#9e8a3c",
        [TILE.TREASURE]:  "#4a7c3f",
    };

    const TILE_ICONS = {
        [TILE.FOREST]:    "🌲",
        [TILE.MOUNTAIN]:  "⛰️",
        [TILE.CASTLE]:    "🏰",
        [TILE.GOLD_MINE]: "⛏️",
        [TILE.TREASURE]:  "💰",
    };

    const PASSABLE = new Set([TILE.GRASS, TILE.ROAD, TILE.CASTLE, TILE.GOLD_MINE, TILE.TREASURE, TILE.FOREST]);

    const MOVE_COST = {
        [TILE.GRASS]: 2, [TILE.ROAD]: 1, [TILE.FOREST]: 3,
        [TILE.CASTLE]: 1, [TILE.GOLD_MINE]: 1, [TILE.TREASURE]: 1,
    };

    // ── Unit definitions ──
    const UNIT_DEFS = {
        swordsman: { name: "Swordsman", icon: "⚔️", hp: 10, atk: 3, def: 2, cost: 50 },
        archer:    { name: "Archer",    icon: "🏹", hp: 7,  atk: 4, def: 1, cost: 75 },
        knight:    { name: "Knight",    icon: "🐴", hp: 20, atk: 5, def: 4, cost: 150 },
        griffin:   { name: "Griffin",   icon: "🦅", hp: 25, atk: 6, def: 3, cost: 200 },
        skeleton:  { name: "Skeleton",  icon: "💀", hp: 5,  atk: 2, def: 1, cost: 0 },
        zombie:    { name: "Zombie",    icon: "🧟", hp: 15, atk: 3, def: 2, cost: 0 },
        demon:     { name: "Demon",     icon: "👹", hp: 30, atk: 7, def: 5, cost: 0 },
    };

    // ── Map config ──
    const MAP_W = 30;
    const MAP_H = 22;
    const MAX_MOVE = 20;

    // ── Game state ──
    const state = {
        map: [],
        enemies: [],
        hero: { x: 1, y: 1, move: MAX_MOVE },
        resources: { gold: 500, wood: 10, ore: 10, gems: 5 },
        army: [
            { type: "swordsman", count: 10 },
            { type: "archer", count: 5 },
        ],
        day: 1,
        heroLevel: 1,
        heroAtk: 2,
        heroDef: 2,
        castlePos: { x: 1, y: 1 },
        goldMines: [],
        ownedMines: new Set(),
        visitedTreasures: new Set(),
        gameOver: false,
    };

    // ── Camera ──
    const camera = { x: 0, y: 0 };
    let tileSize = 40;

    // ── Canvas ──
    const canvas = document.getElementById("map-canvas");
    const ctx = canvas.getContext("2d");

    // ── DOM refs ──
    const $ = id => document.getElementById(id);
    const resGold  = $("res-gold");
    const resWood  = $("res-wood");
    const resOre   = $("res-ore");
    const resGems  = $("res-gems");
    const dayEl    = $("day-counter");
    const moveEl   = $("move-points");
    const moveMaxEl = $("move-max");
    const heroLevelEl = $("hero-level");
    const heroAtkEl   = $("hero-atk");
    const heroDefEl   = $("hero-def");
    const armyPreview = $("army-preview");

    // ── Map generation ──
    function generateMap() {
        const map = [];
        for (let y = 0; y < MAP_H; y++) {
            const row = [];
            for (let x = 0; x < MAP_W; x++) {
                const edge = x === 0 || y === 0 || x === MAP_W - 1 || y === MAP_H - 1;
                if (edge) { row.push(TILE.WATER); continue; }
                const r = Math.random();
                if (r < 0.05) row.push(TILE.MOUNTAIN);
                else if (r < 0.15) row.push(TILE.WATER);
                else if (r < 0.30) row.push(TILE.FOREST);
                else row.push(TILE.GRASS);
            }
            map.push(row);
        }

        map[1][1] = TILE.CASTLE;
        state.castlePos = { x: 1, y: 1 };

        for (let x = 2; x < 7; x++) map[1][x] = TILE.ROAD;
        for (let y = 2; y < 5; y++) map[y][1] = TILE.ROAD;

        placeFeatures(map);
        return map;
    }

    function placeFeatures(map) {
        let minesPlaced = 0;
        let treasuresPlaced = 0;
        const attempts = 600;

        for (let i = 0; i < attempts && (minesPlaced < 4 || treasuresPlaced < 8); i++) {
            const x = 3 + Math.floor(Math.random() * (MAP_W - 6));
            const y = 3 + Math.floor(Math.random() * (MAP_H - 6));
            if (map[y][x] !== TILE.GRASS) continue;

            if (minesPlaced < 4) {
                map[y][x] = TILE.GOLD_MINE;
                state.goldMines.push({ x, y });
                minesPlaced++;
            } else if (treasuresPlaced < 8) {
                map[y][x] = TILE.TREASURE;
                treasuresPlaced++;
            }
        }

        let enemiesPlaced = 0;
        for (let i = 0; i < attempts && enemiesPlaced < 6; i++) {
            const x = 5 + Math.floor(Math.random() * (MAP_W - 10));
            const y = 5 + Math.floor(Math.random() * (MAP_H - 10));
            if (map[y][x] !== TILE.GRASS && map[y][x] !== TILE.ROAD) continue;
            if (Math.abs(x - state.hero.x) + Math.abs(y - state.hero.y) < 6) continue;

            const strength = Math.random();
            let army;
            if (strength < 0.4)
                army = [{ type: "skeleton", count: 5 + Math.floor(Math.random() * 10) }];
            else if (strength < 0.7)
                army = [
                    { type: "skeleton", count: 8 + Math.floor(Math.random() * 8) },
                    { type: "zombie", count: 3 + Math.floor(Math.random() * 5) },
                ];
            else
                army = [
                    { type: "zombie", count: 5 + Math.floor(Math.random() * 5) },
                    { type: "demon", count: 1 + Math.floor(Math.random() * 3) },
                ];

            state.enemies.push({ x, y, army, icon: "☠️" });
            enemiesPlaced++;
        }
    }

    // ── Drawing ──
    function resize() {
        canvas.width = canvas.parentElement.clientWidth;
        canvas.height = canvas.parentElement.clientHeight;
    }

    function centerCamera() {
        camera.x = state.hero.x * tileSize - canvas.width / 2 + tileSize / 2;
        camera.y = state.hero.y * tileSize - canvas.height / 2 + tileSize / 2;
    }

    function draw() {
        ctx.clearRect(0, 0, canvas.width, canvas.height);

        const startCol = Math.max(0, Math.floor(camera.x / tileSize));
        const startRow = Math.max(0, Math.floor(camera.y / tileSize));
        const endCol = Math.min(MAP_W, Math.ceil((camera.x + canvas.width) / tileSize) + 1);
        const endRow = Math.min(MAP_H, Math.ceil((camera.y + canvas.height) / tileSize) + 1);

        for (let y = startRow; y < endRow; y++) {
            for (let x = startCol; x < endCol; x++) {
                const tile = state.map[y][x];
                const sx = x * tileSize - camera.x;
                const sy = y * tileSize - camera.y;

                ctx.fillStyle = TILE_COLORS[tile];
                ctx.fillRect(sx, sy, tileSize, tileSize);

                ctx.strokeStyle = "rgba(0,0,0,0.15)";
                ctx.strokeRect(sx, sy, tileSize, tileSize);

                if (tile === TILE.WATER) {
                    ctx.fillStyle = "rgba(255,255,255,0.08)";
                    ctx.fillRect(sx + 4, sy + tileSize / 2 - 1, tileSize - 8, 2);
                }

                const icon = TILE_ICONS[tile];
                if (icon) {
                    if (tile === TILE.TREASURE && state.visitedTreasures.has(`${x},${y}`)) continue;
                    ctx.font = `${tileSize * 0.55}px serif`;
                    ctx.textAlign = "center";
                    ctx.textBaseline = "middle";
                    ctx.fillText(icon, sx + tileSize / 2, sy + tileSize / 2);
                }

                if (tile === TILE.GOLD_MINE && state.ownedMines.has(`${x},${y}`)) {
                    ctx.fillStyle = "rgba(212,160,23,0.3)";
                    ctx.fillRect(sx, sy, tileSize, tileSize);
                }
            }
        }

        for (const enemy of state.enemies) {
            const sx = enemy.x * tileSize - camera.x;
            const sy = enemy.y * tileSize - camera.y;
            ctx.font = `${tileSize * 0.6}px serif`;
            ctx.textAlign = "center";
            ctx.textBaseline = "middle";
            ctx.fillText(enemy.icon, sx + tileSize / 2, sy + tileSize / 2);
        }

        const hx = state.hero.x * tileSize - camera.x;
        const hy = state.hero.y * tileSize - camera.y;

        ctx.fillStyle = "rgba(58,123,213,0.25)";
        ctx.fillRect(hx, hy, tileSize, tileSize);
        ctx.strokeStyle = "#3a7bd5";
        ctx.lineWidth = 2;
        ctx.strokeRect(hx + 1, hy + 1, tileSize - 2, tileSize - 2);
        ctx.lineWidth = 1;

        ctx.font = `${tileSize * 0.65}px serif`;
        ctx.textAlign = "center";
        ctx.textBaseline = "middle";
        ctx.fillText("🧙", hx + tileSize / 2, hy + tileSize / 2);

        if (pathPreview.length > 0) {
            ctx.strokeStyle = "rgba(255,255,255,0.35)";
            ctx.lineWidth = 2;
            ctx.setLineDash([4, 4]);
            ctx.beginPath();
            const startPx = state.hero.x * tileSize - camera.x + tileSize / 2;
            const startPy = state.hero.y * tileSize - camera.y + tileSize / 2;
            ctx.moveTo(startPx, startPy);
            for (const p of pathPreview) {
                ctx.lineTo(p.x * tileSize - camera.x + tileSize / 2, p.y * tileSize - camera.y + tileSize / 2);
            }
            ctx.stroke();
            ctx.setLineDash([]);
            ctx.lineWidth = 1;
        }
    }

    // ── Pathfinding (BFS) ──
    function findPath(sx, sy, tx, ty) {
        if (sx === tx && sy === ty) return [];
        if (!PASSABLE.has(state.map[ty]?.[tx])) return null;

        const visited = new Set();
        const queue = [{ x: sx, y: sy, path: [] }];
        visited.add(`${sx},${sy}`);

        while (queue.length > 0) {
            const cur = queue.shift();
            const dirs = [[0, -1], [0, 1], [-1, 0], [1, 0]];
            for (const [dx, dy] of dirs) {
                const nx = cur.x + dx;
                const ny = cur.y + dy;
                const key = `${nx},${ny}`;
                if (nx < 0 || ny < 0 || nx >= MAP_W || ny >= MAP_H) continue;
                if (visited.has(key)) continue;
                if (!PASSABLE.has(state.map[ny][nx])) continue;
                visited.add(key);
                const newPath = [...cur.path, { x: nx, y: ny }];
                if (nx === tx && ny === ty) return newPath;
                queue.push({ x: nx, y: ny, path: newPath });
            }
        }
        return null;
    }

    function pathCost(path) {
        let cost = 0;
        for (const p of path) cost += MOVE_COST[state.map[p.y][p.x]] || 2;
        return cost;
    }

    // ── Movement ──
    let pathPreview = [];

    function moveHero(tx, ty) {
        if (state.gameOver) return;
        const path = findPath(state.hero.x, state.hero.y, tx, ty);
        if (!path || path.length === 0) return;

        const cost = pathCost(path);
        if (cost > state.hero.move) {
            const affordable = [];
            let spent = 0;
            for (const p of path) {
                const c = MOVE_COST[state.map[p.y][p.x]] || 2;
                if (spent + c > state.hero.move) break;
                affordable.push(p);
                spent += c;
            }
            if (affordable.length === 0) return;
            animateMove(affordable);
            return;
        }
        animateMove(path);
    }

    function animateMove(path) {
        if (path.length === 0) return;
        let i = 0;
        const step = () => {
            if (i >= path.length || state.gameOver) { afterMove(); return; }
            const p = path[i];
            const cost = MOVE_COST[state.map[p.y][p.x]] || 2;
            if (state.hero.move < cost) { afterMove(); return; }

            state.hero.x = p.x;
            state.hero.y = p.y;
            state.hero.move -= cost;
            centerCamera();

            const enemy = state.enemies.find(e => e.x === p.x && e.y === p.y);
            if (enemy) {
                updateUI();
                draw();
                startCombat(enemy);
                return;
            }

            handleTileEvent(p.x, p.y);
            updateUI();
            draw();
            i++;
            setTimeout(step, 80);
        };
        step();
    }

    function afterMove() {
        pathPreview = [];
        updateUI();
        draw();
    }

    function handleTileEvent(x, y) {
        const tile = state.map[y][x];
        const key = `${x},${y}`;

        if (tile === TILE.TREASURE && !state.visitedTreasures.has(key)) {
            state.visitedTreasures.add(key);
            const gold = 100 + Math.floor(Math.random() * 200);
            state.resources.gold += gold;
            showMessage(`You found a treasure chest containing ${gold} gold!`);
        }

        if (tile === TILE.GOLD_MINE && !state.ownedMines.has(key)) {
            state.ownedMines.add(key);
            showMessage("You captured a gold mine! It will produce 100 gold per turn.");
        }

        if (tile === TILE.CASTLE && x === state.castlePos.x && y === state.castlePos.y) {
            openTown();
        }
    }

    // ── Combat system ──
    let currentEnemy = null;
    let combatOver = false;

    function startCombat(enemy) {
        currentEnemy = enemy;
        combatOver = false;
        $("combat-overlay").classList.remove("hidden");
        $("btn-attack").disabled = false;
        $("btn-flee").disabled = false;
        $("combat-log").innerHTML = "<p>The battle begins!</p>";
        renderCombatUnits();
    }

    function renderCombatUnits() {
        const atkDiv = $("attacker-units");
        const defDiv = $("defender-units");
        atkDiv.innerHTML = state.army.map(u => {
            const def = UNIT_DEFS[u.type];
            const dead = u.count <= 0 ? " dead" : "";
            return `<div class="combat-unit${dead}"><span class="unit-name">${def.icon} ${def.name}</span><span class="unit-count">x${Math.max(0, u.count)}</span></div>`;
        }).join("");
        defDiv.innerHTML = currentEnemy.army.map(u => {
            const def = UNIT_DEFS[u.type];
            const dead = u.count <= 0 ? " dead" : "";
            return `<div class="combat-unit${dead}"><span class="unit-name">${def.icon} ${def.name}</span><span class="unit-count">x${Math.max(0, u.count)}</span></div>`;
        }).join("");
    }

    function combatRound() {
        if (combatOver) return;
        const log = $("combat-log");

        for (const stack of state.army) {
            if (stack.count <= 0) continue;
            const def = UNIT_DEFS[stack.type];
            const target = currentEnemy.army.find(e => e.count > 0);
            if (!target) break;
            const tDef = UNIT_DEFS[target.type];
            const damage = Math.max(1, (def.atk + state.heroAtk) - tDef.def);
            const totalDmg = damage * stack.count;
            const kills = Math.min(target.count, Math.ceil(totalDmg / tDef.hp));
            target.count -= kills;
            log.innerHTML += `<p class="atk-log">${def.name} deals ${totalDmg} dmg → kills ${kills} ${tDef.name}</p>`;
        }

        for (const stack of currentEnemy.army) {
            if (stack.count <= 0) continue;
            const def = UNIT_DEFS[stack.type];
            const target = state.army.find(e => e.count > 0);
            if (!target) break;
            const tDef = UNIT_DEFS[target.type];
            const damage = Math.max(1, def.atk - (tDef.def + state.heroDef));
            const totalDmg = damage * stack.count;
            const kills = Math.min(target.count, Math.ceil(totalDmg / tDef.hp));
            target.count -= kills;
            log.innerHTML += `<p class="def-log">${def.name} deals ${totalDmg} dmg → kills ${kills} ${tDef.name}</p>`;
        }

        renderCombatUnits();
        log.scrollTop = log.scrollHeight;

        const playerAlive = state.army.some(u => u.count > 0);
        const enemyAlive = currentEnemy.army.some(u => u.count > 0);

        if (!enemyAlive) {
            combatOver = true;
            log.innerHTML += `<p class="result-log">Victory! You gained experience.</p>`;
            $("btn-attack").disabled = true;
            $("btn-flee").disabled = true;
            const idx = state.enemies.indexOf(currentEnemy);
            if (idx >= 0) state.enemies.splice(idx, 1);
            gainExperience();
            const reward = 50 + Math.floor(Math.random() * 150);
            state.resources.gold += reward;
            log.innerHTML += `<p class="result-log">Spoils: ${reward} gold</p>`;
            setTimeout(() => closeCombat(), 1500);
        }

        if (!playerAlive) {
            combatOver = true;
            log.innerHTML += `<p class="result-log">Defeat! Your hero has fallen.</p>`;
            $("btn-attack").disabled = true;
            $("btn-flee").disabled = true;
            state.gameOver = true;
            setTimeout(() => {
                closeCombat();
                showMessage("Your hero has been defeated. The kingdom falls into darkness...");
            }, 1500);
        }
    }

    function closeCombat() {
        $("combat-overlay").classList.add("hidden");
        currentEnemy = null;
        state.army = state.army.filter(u => u.count > 0);
        updateUI();
        draw();
    }

    function gainExperience() {
        state.heroLevel++;
        state.heroAtk += 1;
        state.heroDef += 1;
    }

    // ── Town ──
    function openTown() {
        $("town-overlay").classList.remove("hidden");
        renderTownArmy();
        updateRecruitButtons();
    }

    function renderTownArmy() {
        $("town-army-list").innerHTML = state.army.map(u => {
            const def = UNIT_DEFS[u.type];
            return `<span class="town-unit-badge">${def.icon} ${def.name} x${u.count}</span>`;
        }).join("");
    }

    function updateRecruitButtons() {
        document.querySelectorAll(".btn-recruit").forEach(btn => {
            const type = btn.dataset.unit;
            const def = UNIT_DEFS[type];
            btn.disabled = state.resources.gold < def.cost;
        });
    }

    function recruitUnit(type) {
        const def = UNIT_DEFS[type];
        if (state.resources.gold < def.cost) return;
        state.resources.gold -= def.cost;
        const existing = state.army.find(u => u.type === type);
        if (existing) existing.count++;
        else state.army.push({ type, count: 1 });
        renderTownArmy();
        updateRecruitButtons();
        updateUI();
    }

    // ── Messages ──
    let messageQueue = [];
    let messageShowing = false;

    function showMessage(text) {
        messageQueue.push(text);
        if (!messageShowing) showNextMessage();
    }

    function showNextMessage() {
        if (messageQueue.length === 0) { messageShowing = false; return; }
        messageShowing = true;
        $("message-text").textContent = messageQueue.shift();
        $("message-overlay").classList.remove("hidden");
    }

    // ── Turn system ──
    function endTurn() {
        if (state.gameOver) return;
        state.day++;
        state.hero.move = MAX_MOVE;
        state.resources.gold += state.ownedMines.size * 100;
        state.resources.wood += 2;
        state.resources.ore += 2;

        moveEnemies();

        if (state.day % 7 === 0) {
            state.resources.gems += 1;
            showMessage("A new week begins. You found a gem!");
        }

        checkVictory();
        updateUI();
        draw();
    }

    function moveEnemies() {
        for (const enemy of state.enemies) {
            const dx = state.hero.x - enemy.x;
            const dy = state.hero.y - enemy.y;
            const dist = Math.abs(dx) + Math.abs(dy);
            if (dist > 10 || dist < 2) continue;

            const nx = enemy.x + Math.sign(dx);
            const ny = enemy.y + Math.sign(dy);
            if (nx >= 0 && ny >= 0 && nx < MAP_W && ny < MAP_H && PASSABLE.has(state.map[ny][nx])) {
                const occupied = state.enemies.some(e => e !== enemy && e.x === nx && e.y === ny);
                if (!occupied) {
                    enemy.x = nx;
                    enemy.y = ny;
                }
            }

            if (enemy.x === state.hero.x && enemy.y === state.hero.y) {
                startCombat(enemy);
                return;
            }
        }
    }

    function checkVictory() {
        if (state.enemies.length === 0) {
            state.gameOver = true;
            showMessage("Glorious victory! You have vanquished all enemies and secured the realm!");
        }
    }

    // ── UI updates ──
    function updateUI() {
        resGold.textContent = state.resources.gold;
        resWood.textContent = state.resources.wood;
        resOre.textContent = state.resources.ore;
        resGems.textContent = state.resources.gems;
        dayEl.textContent = state.day;
        moveEl.textContent = state.hero.move;
        moveMaxEl.textContent = MAX_MOVE;
        heroLevelEl.textContent = state.heroLevel;
        heroAtkEl.textContent = state.heroAtk;
        heroDefEl.textContent = state.heroDef;

        armyPreview.innerHTML = state.army.map(u => {
            const def = UNIT_DEFS[u.type];
            return `<span class="army-badge">${def.icon} ${def.name} x${u.count}</span>`;
        }).join("");
    }

    // ── Input handling ──
    canvas.addEventListener("click", (e) => {
        if (state.gameOver) return;
        const rect = canvas.getBoundingClientRect();
        const mx = e.clientX - rect.left;
        const my = e.clientY - rect.top;
        const tx = Math.floor((mx + camera.x) / tileSize);
        const ty = Math.floor((my + camera.y) / tileSize);
        if (tx < 0 || ty < 0 || tx >= MAP_W || ty >= MAP_H) return;
        moveHero(tx, ty);
    });

    canvas.addEventListener("mousemove", (e) => {
        if (state.gameOver) return;
        const rect = canvas.getBoundingClientRect();
        const mx = e.clientX - rect.left;
        const my = e.clientY - rect.top;
        const tx = Math.floor((mx + camera.x) / tileSize);
        const ty = Math.floor((my + camera.y) / tileSize);
        if (tx < 0 || ty < 0 || tx >= MAP_W || ty >= MAP_H) { pathPreview = []; draw(); return; }

        const path = findPath(state.hero.x, state.hero.y, tx, ty);
        pathPreview = path || [];
        draw();
    });

    canvas.addEventListener("mouseleave", () => {
        pathPreview = [];
        draw();
    });

    $("btn-end-turn").addEventListener("click", endTurn);

    $("btn-attack").addEventListener("click", combatRound);

    $("btn-flee").addEventListener("click", () => {
        if (combatOver) return;
        const fleeChance = 0.5;
        if (Math.random() < fleeChance) {
            $("combat-log").innerHTML += `<p class="result-log">You fled the battle!</p>`;
            const casualty = state.army.find(u => u.count > 0);
            if (casualty) {
                const lost = Math.max(1, Math.floor(casualty.count * 0.2));
                casualty.count -= lost;
                $("combat-log").innerHTML += `<p class="def-log">${lost} ${UNIT_DEFS[casualty.type].name}(s) lost covering the retreat.</p>`;
            }
            combatOver = true;
            setTimeout(() => {
                closeCombat();
                state.hero.x = Math.max(1, state.hero.x - 2);
                state.hero.y = Math.max(1, state.hero.y - 2);
                if (!PASSABLE.has(state.map[state.hero.y][state.hero.x])) {
                    state.hero.x = state.castlePos.x;
                    state.hero.y = state.castlePos.y;
                }
                centerCamera();
                draw();
            }, 1000);
        } else {
            $("combat-log").innerHTML += `<p class="def-log">Failed to flee!</p>`;
            combatRound();
        }
    });

    document.querySelectorAll(".btn-recruit").forEach(btn => {
        btn.addEventListener("click", () => recruitUnit(btn.dataset.unit));
    });

    $("btn-leave-town").addEventListener("click", () => {
        $("town-overlay").classList.add("hidden");
    });

    $("btn-message-ok").addEventListener("click", () => {
        $("message-overlay").classList.add("hidden");
        showNextMessage();
    });

    document.addEventListener("keydown", (e) => {
        if (state.gameOver) return;
        const dirs = { ArrowUp: [0, -1], ArrowDown: [0, 1], ArrowLeft: [-1, 0], ArrowRight: [1, 0] };
        const dir = dirs[e.key];
        if (dir) {
            e.preventDefault();
            const tx = state.hero.x + dir[0];
            const ty = state.hero.y + dir[1];
            if (tx >= 0 && ty >= 0 && tx < MAP_W && ty < MAP_H) moveHero(tx, ty);
        }
        if (e.key === "e" || e.key === "E") endTurn();
    });

    let zoomTimeout;
    canvas.addEventListener("wheel", (e) => {
        e.preventDefault();
        const oldTile = tileSize;
        if (e.deltaY < 0) tileSize = Math.min(80, tileSize + 4);
        else tileSize = Math.max(20, tileSize - 4);

        if (tileSize !== oldTile) {
            centerCamera();
            draw();
        }
    }, { passive: false });

    // ── Init ──
    function init() {
        resize();
        state.map = generateMap();
        state.hero.x = state.castlePos.x;
        state.hero.y = state.castlePos.y;
        centerCamera();
        updateUI();
        draw();
    }

    window.addEventListener("resize", () => {
        resize();
        centerCamera();
        draw();
    });

    init();
})();
