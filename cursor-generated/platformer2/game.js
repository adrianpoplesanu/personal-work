(() => {
    const canvas = document.getElementById("game");
    const ctx = canvas.getContext("2d");
    const W = 960;
    const H = 540;
    canvas.width = W;
    canvas.height = H;

    const hudLevel = document.getElementById("hud-level");
    const hudHp = document.getElementById("hud-hp");
    const overlay = document.getElementById("overlay");
    const overlayText = document.getElementById("overlay-text");
    const overlaySub = document.getElementById("overlay-sub");

    const GRAVITY = 0.6;
    const PLAYER_SPEED = 4.5;
    const JUMP_FORCE = -11;
    const COYOTE_TIME = 8;
    const JUMP_BUFFER = 6;
    const ATTACK_DURATION = 15;
    const ATTACK_COOLDOWN = 25;
    const ATTACK_RANGE = 40;
    const ATTACK_DAMAGE = 2;
    const PLAYER_MAX_HP = 5;
    const DAMAGE_FLASH = 30;
    const INVINCIBLE_TIME = 60;
    const EXIT_WIDTH = 40;
    const EXIT_HEIGHT = 60;

    const COLORS = {
        bg: "#16213e",
        platform: "#0f3460",
        platformTop: "#1a5276",
        player: "#53a8b6",
        playerAttack: "#e94560",
        enemy: "#e94560",
        enemyHurt: "#ff8a80",
        exit: "#4ecca3",
        exitGlow: "rgba(78, 204, 163, 0.25)",
        attackArc: "rgba(233, 69, 96, 0.4)",
        hp: "#4ecca3",
        hpLost: "#333",
        particle: "#ffd700",
    };

    const keys = {};
    window.addEventListener("keydown", (e) => { keys[e.code] = true; });
    window.addEventListener("keyup", (e) => { keys[e.code] = false; });

    class Camera {
        constructor() { this.x = 0; this.y = 0; }
        follow(target, levelWidth) {
            this.x = target.x - W / 2;
            this.y = target.y - H / 2 + 60;
            this.x = Math.max(0, Math.min(this.x, levelWidth - W));
            this.y = Math.max(0, Math.min(this.y, 200));
        }
    }

    class Particle {
        constructor(x, y, color) {
            this.x = x;
            this.y = y;
            this.vx = (Math.random() - 0.5) * 6;
            this.vy = (Math.random() - 0.5) * 6 - 2;
            this.life = 20 + Math.random() * 15;
            this.maxLife = this.life;
            this.size = 2 + Math.random() * 3;
            this.color = color;
        }
        update() {
            this.x += this.vx;
            this.y += this.vy;
            this.vy += 0.15;
            this.life--;
        }
        draw(ctx, cam) {
            const alpha = this.life / this.maxLife;
            ctx.globalAlpha = alpha;
            ctx.fillStyle = this.color;
            ctx.fillRect(this.x - cam.x - this.size / 2, this.y - cam.y - this.size / 2, this.size, this.size);
            ctx.globalAlpha = 1;
        }
    }

    class Player {
        constructor(x, y) {
            this.x = x;
            this.y = y;
            this.w = 24;
            this.h = 32;
            this.vx = 0;
            this.vy = 0;
            this.onGround = false;
            this.jumpsLeft = 2;
            this.coyoteTimer = 0;
            this.jumpBufferTimer = 0;
            this.facing = 1;
            this.hp = PLAYER_MAX_HP;
            this.invincible = 0;
            this.damageFlash = 0;
            this.attacking = false;
            this.attackTimer = 0;
            this.attackCooldown = 0;
            this.dead = false;
        }

        update(platforms) {
            if (this.dead) return;

            const left = keys["ArrowLeft"] || keys["KeyA"];
            const right = keys["ArrowRight"] || keys["KeyD"];
            const jump = keys["ArrowUp"] || keys["KeyW"] || keys["Space"];
            const attack = keys["KeyJ"] || keys["KeyZ"];

            if (left) { this.vx = -PLAYER_SPEED; this.facing = -1; }
            else if (right) { this.vx = PLAYER_SPEED; this.facing = 1; }
            else { this.vx *= 0.7; }

            if (this.onGround) {
                this.coyoteTimer = COYOTE_TIME;
                this.jumpsLeft = 2;
            } else {
                this.coyoteTimer--;
            }

            if (jump && !this._jumpHeld) {
                this.jumpBufferTimer = JUMP_BUFFER;
            }
            this._jumpHeld = jump;

            if (this.jumpBufferTimer > 0) {
                this.jumpBufferTimer--;
                if (this.coyoteTimer > 0 && this.jumpsLeft === 2) {
                    this.vy = JUMP_FORCE;
                    this.jumpsLeft = 1;
                    this.coyoteTimer = 0;
                    this.jumpBufferTimer = 0;
                    this.onGround = false;
                } else if (this.jumpsLeft > 0 && this.coyoteTimer <= 0) {
                    this.vy = JUMP_FORCE * 0.85;
                    this.jumpsLeft = 0;
                    this.jumpBufferTimer = 0;
                }
            }

            this.vy += GRAVITY;
            if (this.vy > 14) this.vy = 14;

            this.x += this.vx;
            this.resolveHorizontal(platforms);

            this.y += this.vy;
            this.onGround = false;
            this.resolveVertical(platforms);

            if (this.y > H + 100) {
                this.hp = 0;
                this.dead = true;
            }

            if (attack && !this.attacking && this.attackCooldown <= 0) {
                this.attacking = true;
                this.attackTimer = ATTACK_DURATION;
                this.attackCooldown = ATTACK_COOLDOWN;
            }
            if (this.attacking) {
                this.attackTimer--;
                if (this.attackTimer <= 0) this.attacking = false;
            }
            if (this.attackCooldown > 0) this.attackCooldown--;
            if (this.invincible > 0) this.invincible--;
            if (this.damageFlash > 0) this.damageFlash--;
        }

        resolveHorizontal(platforms) {
            for (const p of platforms) {
                if (this.overlaps(p)) {
                    if (this.vx > 0) this.x = p.x - this.w;
                    else if (this.vx < 0) this.x = p.x + p.w;
                    this.vx = 0;
                }
            }
        }

        resolveVertical(platforms) {
            for (const p of platforms) {
                if (this.overlaps(p)) {
                    if (this.vy > 0) {
                        this.y = p.y - this.h;
                        this.vy = 0;
                        this.onGround = true;
                    } else if (this.vy < 0) {
                        this.y = p.y + p.h;
                        this.vy = 0;
                    }
                }
            }
        }

        overlaps(r) {
            return this.x < r.x + r.w && this.x + this.w > r.x &&
                   this.y < r.y + r.h && this.y + this.h > r.y;
        }

        getAttackBox() {
            const ax = this.facing === 1 ? this.x + this.w : this.x - ATTACK_RANGE;
            return { x: ax, y: this.y - 4, w: ATTACK_RANGE, h: this.h + 8 };
        }

        takeDamage(amount) {
            if (this.invincible > 0 || this.dead) return;
            this.hp -= amount;
            this.invincible = INVINCIBLE_TIME;
            this.damageFlash = DAMAGE_FLASH;
            if (this.hp <= 0) {
                this.hp = 0;
                this.dead = true;
            }
        }

        draw(ctx, cam) {
            if (this.dead) return;

            const sx = this.x - cam.x;
            const sy = this.y - cam.y;

            if (this.attacking) {
                const ab = this.getAttackBox();
                ctx.fillStyle = COLORS.attackArc;
                ctx.beginPath();
                const cx = (this.facing === 1 ? sx + this.w : sx) ;
                const cy = sy + this.h / 2;
                ctx.ellipse(cx + this.facing * ATTACK_RANGE / 2, cy, ATTACK_RANGE / 2 + 4, this.h / 2 + 8, 0, 0, Math.PI * 2);
                ctx.fill();
            }

            const blink = this.invincible > 0 && Math.floor(this.invincible / 3) % 2 === 0;
            if (!blink) {
                ctx.fillStyle = this.damageFlash > 0 ? "#fff" : COLORS.player;
                ctx.fillRect(sx, sy, this.w, this.h);

                ctx.fillStyle = "#fff";
                const eyeX = this.facing === 1 ? sx + 15 : sx + 5;
                ctx.fillRect(eyeX, sy + 8, 5, 5);

                ctx.fillStyle = "#1a1a2e";
                const pupilX = this.facing === 1 ? eyeX + 2 : eyeX;
                ctx.fillRect(pupilX, sy + 10, 3, 3);
            }
        }
    }

    class Enemy {
        constructor(x, y, patrolLeft, patrolRight) {
            this.x = x;
            this.y = y;
            this.w = 26;
            this.h = 26;
            this.hp = 3;
            this.maxHp = 3;
            this.speed = 1.2;
            this.dir = 1;
            this.patrolLeft = patrolLeft;
            this.patrolRight = patrolRight;
            this.hurtTimer = 0;
            this.dead = false;
        }

        update() {
            if (this.dead) return;
            this.x += this.speed * this.dir;
            if (this.x <= this.patrolLeft) { this.x = this.patrolLeft; this.dir = 1; }
            if (this.x + this.w >= this.patrolRight) { this.x = this.patrolRight - this.w; this.dir = -1; }
            if (this.hurtTimer > 0) this.hurtTimer--;
        }

        takeDamage(amount, particles) {
            if (this.dead) return;
            this.hp -= amount;
            this.hurtTimer = 10;
            for (let i = 0; i < 8; i++) {
                particles.push(new Particle(this.x + this.w / 2, this.y + this.h / 2, COLORS.particle));
            }
            if (this.hp <= 0) {
                this.dead = true;
                for (let i = 0; i < 14; i++) {
                    particles.push(new Particle(this.x + this.w / 2, this.y + this.h / 2, COLORS.enemy));
                }
            }
        }

        touchesPlayer(player) {
            return !this.dead && !player.dead &&
                   this.x < player.x + player.w && this.x + this.w > player.x &&
                   this.y < player.y + player.h && this.y + this.h > player.y;
        }

        draw(ctx, cam) {
            if (this.dead) return;
            const sx = this.x - cam.x;
            const sy = this.y - cam.y;

            ctx.fillStyle = this.hurtTimer > 0 ? COLORS.enemyHurt : COLORS.enemy;
            ctx.fillRect(sx, sy, this.w, this.h);

            ctx.fillStyle = "#fff";
            ctx.fillRect(sx + 4, sy + 6, 5, 5);
            ctx.fillRect(sx + this.w - 9, sy + 6, 5, 5);
            ctx.fillStyle = "#1a1a2e";
            ctx.fillRect(sx + (this.dir === 1 ? 6 : 4), sy + 8, 3, 3);
            ctx.fillRect(sx + this.w - (this.dir === 1 ? 7 : 9) , sy + 8, 3, 3);

            const barW = this.w;
            const barH = 3;
            const barY = sy - 8;
            ctx.fillStyle = "#333";
            ctx.fillRect(sx, barY, barW, barH);
            ctx.fillStyle = COLORS.enemy;
            ctx.fillRect(sx, barY, barW * (this.hp / this.maxHp), barH);
        }
    }

    function boxOverlap(a, b) {
        return a.x < b.x + b.w && a.x + a.w > b.x &&
               a.y < b.y + b.h && a.y + a.h > b.y;
    }

    function generateLevel(levelNum) {
        const platforms = [];
        const enemies = [];

        const MAX_REACH_X = 190;
        const MAX_REACH_UP = 140;
        const MIN_PLAT_Y = 80;
        const MAX_PLAT_Y = H - 50;
        const PLAT_MIN_W = 80;
        const PLAT_MAX_W = 150;

        const columnCount = 8 + levelNum * 2;
        const columnWidth = 200;
        const columnSpread = 50;

        function canReach(a, b) {
            const gapX = Math.max(0, Math.max(b.x - (a.x + a.w), a.x - (b.x + b.w)));
            if (gapX > MAX_REACH_X) return false;
            const rise = a.y - b.y;
            if (rise > 0) {
                const ratio = gapX / MAX_REACH_X;
                return rise <= MAX_REACH_UP * (1 - ratio * ratio) * 0.85;
            }
            return true;
        }

        const startPlat = { x: 0, y: H - 40, w: 200, h: 40 };
        platforms.push(startPlat);

        const columns = [[startPlat]];

        for (let col = 0; col < columnCount; col++) {
            const colCenterX = 200 + col * columnWidth + columnWidth / 2;
            const platsInCol = 4 + Math.floor(Math.random() * 2);
            const colPlats = [];
            const prevCol = columns[columns.length - 1];

            const slotH = (MAX_PLAT_Y - MIN_PLAT_Y) / platsInCol;
            for (let p = 0; p < platsInCol; p++) {
                if (colPlats.length > 0 && Math.random() < 0.1) continue;
                const depthRatio = platsInCol > 1 ? p / (platsInCol - 1) : 0.5;
                const minW = PLAT_MIN_W * (0.5 + depthRatio * 0.5);
                const maxW = PLAT_MAX_W * (0.6 + depthRatio * 0.4);
                const pw = minW + Math.random() * (maxW - minW);
                const px = colCenterX - pw / 2 + (Math.random() - 0.5) * columnSpread;
                const py = MIN_PLAT_Y + p * slotH + Math.random() * slotH * 0.7;

                colPlats.push({ x: px, y: Math.max(MIN_PLAT_Y, Math.min(MAX_PLAT_Y, py)), w: pw, h: 16 });
            }

            colPlats.sort((a, b) => a.y - b.y);

            for (let i = 1; i < colPlats.length; i++) {
                if (colPlats[i].y - colPlats[i - 1].y > MAX_REACH_UP * 0.85) {
                    colPlats[i].y = colPlats[i - 1].y + MAX_REACH_UP * (0.4 + Math.random() * 0.4);
                }
            }

            let hasReachable = false;
            for (const cp of colPlats) {
                for (const pp of prevCol) {
                    if (canReach(pp, cp)) { hasReachable = true; break; }
                }
                if (hasReachable) break;
            }

            if (!hasReachable) {
                let bestPrev = prevCol[0];
                let bestDist = Infinity;
                for (const pp of prevCol) {
                    const d = Math.abs(pp.y - colPlats[0].y);
                    if (d < bestDist) { bestDist = d; bestPrev = pp; }
                }
                const gapX = Math.max(0, colPlats[0].x - (bestPrev.x + bestPrev.w));
                const ratio = Math.min(1, gapX / MAX_REACH_X);
                const allowedUp = MAX_REACH_UP * (1 - ratio * ratio) * 0.8;

                if (colPlats[0].y < bestPrev.y) {
                    colPlats[0].y = Math.max(MIN_PLAT_Y, bestPrev.y - allowedUp * (0.3 + Math.random() * 0.5));
                }
            }

            for (const cp of colPlats) {
                platforms.push(cp);
                if (cp.w >= 70 && Math.random() < 0.3 + levelNum * 0.04) {
                    enemies.push(new Enemy(cp.x + 10, cp.y - 26, cp.x, cp.x + cp.w));
                }
            }

            columns.push(colPlats);
        }

        const lastCol = columns[columns.length - 1];
        const anchorPlat = lastCol[Math.floor(Math.random() * lastCol.length)];
        const exitPlatX = anchorPlat.x + anchorPlat.w + 60;
        let exitPlatY = anchorPlat.y + (Math.random() - 0.5) * 60;
        exitPlatY = Math.max(MIN_PLAT_Y + EXIT_HEIGHT, Math.min(MAX_PLAT_Y, exitPlatY));

        platforms.push({ x: exitPlatX, y: exitPlatY, w: 120, h: 16 });

        const exit = {
            x: exitPlatX + 40,
            y: exitPlatY - EXIT_HEIGHT,
            w: EXIT_WIDTH,
            h: EXIT_HEIGHT,
        };

        const levelWidth = exitPlatX + 200;

        return { platforms, enemies, exit, levelWidth };
    }

    let level = 1;
    let { platforms, enemies, exit, levelWidth } = generateLevel(level);
    let player = new Player(40, H - 100);
    let camera = new Camera();
    let particles = [];
    let gameOver = false;
    let levelTransition = 0;

    function nextLevel() {
        level++;
        const gen = generateLevel(level);
        platforms = gen.platforms;
        enemies = gen.enemies;
        exit = gen.exit;
        levelWidth = gen.levelWidth;
        player.x = 40;
        player.y = H - 100;
        player.vx = 0;
        player.vy = 0;
        player.onGround = false;
        particles = [];
        levelTransition = 40;
    }

    function restart() {
        level = 1;
        const gen = generateLevel(level);
        platforms = gen.platforms;
        enemies = gen.enemies;
        exit = gen.exit;
        levelWidth = gen.levelWidth;
        player = new Player(40, H - 100);
        camera = new Camera();
        particles = [];
        gameOver = false;
        overlay.classList.add("hidden");
    }

    window.addEventListener("keydown", (e) => {
        if (e.code === "KeyR" && gameOver) restart();
    });

    function update() {
        if (gameOver) return;
        if (levelTransition > 0) { levelTransition--; return; }

        player.update(platforms);

        if (player.attacking) {
            const ab = player.getAttackBox();
            for (const e of enemies) {
                if (!e.dead && boxOverlap(ab, e)) {
                    e.takeDamage(ATTACK_DAMAGE, particles);
                }
            }
        }

        for (const e of enemies) {
            e.update();
            if (e.touchesPlayer(player)) {
                player.takeDamage(1);
            }
        }

        if (player.dead) {
            gameOver = true;
            overlayText.textContent = "GAME OVER";
            overlaySub.textContent = `Reached level ${level} — Press R to restart`;
            overlay.classList.remove("hidden");
        }

        if (boxOverlap(player, exit)) {
            for (let i = 0; i < 20; i++) {
                particles.push(new Particle(exit.x + EXIT_WIDTH / 2, exit.y + EXIT_HEIGHT / 2, COLORS.exit));
            }
            nextLevel();
        }

        for (let i = particles.length - 1; i >= 0; i--) {
            particles[i].update();
            if (particles[i].life <= 0) particles.splice(i, 1);
        }

        camera.follow(player, levelWidth);
        hudLevel.textContent = `Level ${level}`;
        hudHp.textContent = `HP: ${player.hp}`;
    }

    function drawBackground(cam) {
        ctx.fillStyle = COLORS.bg;
        ctx.fillRect(0, 0, W, H);

        ctx.fillStyle = "rgba(255,255,255,0.015)";
        const starSpacing = 80;
        for (let sx = -cam.x * 0.2 % starSpacing; sx < W; sx += starSpacing) {
            for (let sy = -cam.y * 0.1 % starSpacing; sy < H; sy += starSpacing) {
                ctx.fillRect(sx, sy, 2, 2);
            }
        }
    }

    function drawPlatforms(cam) {
        for (const p of platforms) {
            const sx = p.x - cam.x;
            const sy = p.y - cam.y;
            if (sx + p.w < -50 || sx > W + 50) continue;

            ctx.fillStyle = COLORS.platform;
            ctx.fillRect(sx, sy, p.w, p.h);
            ctx.fillStyle = COLORS.platformTop;
            ctx.fillRect(sx, sy, p.w, 3);
        }
    }

    function drawExit(cam) {
        const sx = exit.x - cam.x;
        const sy = exit.y - cam.y;

        const pulse = Math.sin(Date.now() * 0.005) * 0.3 + 0.7;

        ctx.fillStyle = COLORS.exitGlow;
        ctx.beginPath();
        ctx.ellipse(sx + EXIT_WIDTH / 2, sy + EXIT_HEIGHT / 2, EXIT_WIDTH + 10, EXIT_HEIGHT + 10, 0, 0, Math.PI * 2);
        ctx.fill();

        ctx.globalAlpha = pulse;
        ctx.fillStyle = COLORS.exit;
        ctx.fillRect(sx, sy, EXIT_WIDTH, EXIT_HEIGHT);
        ctx.globalAlpha = 1;

        ctx.fillStyle = "#fff";
        ctx.font = "bold 11px sans-serif";
        ctx.textAlign = "center";
        ctx.fillText("EXIT", sx + EXIT_WIDTH / 2, sy + EXIT_HEIGHT / 2 + 4);
    }

    function drawHpBar(cam) {
        const bx = 16;
        const by = H - 24;
        for (let i = 0; i < PLAYER_MAX_HP; i++) {
            ctx.fillStyle = i < player.hp ? COLORS.hp : COLORS.hpLost;
            ctx.fillRect(bx + i * 18, by, 14, 14);
        }
    }

    function drawLevelTransition() {
        if (levelTransition <= 0) return;
        const alpha = levelTransition / 40;
        ctx.fillStyle = `rgba(0,0,0,${alpha})`;
        ctx.fillRect(0, 0, W, H);
        ctx.fillStyle = `rgba(78,204,163,${alpha})`;
        ctx.font = "bold 32px sans-serif";
        ctx.textAlign = "center";
        ctx.fillText(`Level ${level}`, W / 2, H / 2);
    }

    function draw() {
        drawBackground(camera);
        drawPlatforms(camera);
        drawExit(camera);

        for (const e of enemies) e.draw(ctx, camera);

        player.draw(ctx, camera);

        for (const p of particles) p.draw(ctx, camera);

        drawHpBar(camera);
        drawLevelTransition();
    }

    function loop() {
        update();
        draw();
        requestAnimationFrame(loop);
    }

    loop();
})();
