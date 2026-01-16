// Canvas setup
const canvas = document.getElementById('gameCanvas');
const ctx = canvas.getContext('2d');
canvas.width = 800;
canvas.height = 600;

// Game state
let currentLevel = 1;
let gameRunning = false;
let keys = {};
let animationFrameId = null;

// Player class
class Player {
    constructor(x, y) {
        this.x = x;
        this.y = y;
        this.width = 30;
        this.height = 30;
        this.velocityX = 0;
        this.velocityY = 0;
        this.speed = 5;
        this.jumpPower = 15;
        this.gravity = 0.8;
        this.onGround = false;
        this.color = '#00ffff';
    }

    update(platforms) {
        // Apply gravity
        if (!this.onGround) {
            this.velocityY += this.gravity;
        }

        // Handle input
        if (keys['ArrowLeft'] || keys['a'] || keys['A']) {
            this.velocityX = -this.speed;
        } else if (keys['ArrowRight'] || keys['d'] || keys['D']) {
            this.velocityX = this.speed;
        } else {
            this.velocityX *= 0.8; // Friction
        }

        if ((keys['ArrowUp'] || keys[' '] || keys['w'] || keys['W']) && this.onGround) {
            this.velocityY = -this.jumpPower;
            this.onGround = false;
        }

        // Update position
        this.x += this.velocityX;
        this.y += this.velocityY;

        // Collision with platforms
        this.onGround = false;
        for (let platform of platforms) {
            if (this.checkCollision(platform)) {
                // Top collision (landing on platform)
                if (this.velocityY > 0 && this.y - this.velocityY < platform.y) {
                    this.y = platform.y - this.height;
                    this.velocityY = 0;
                    this.onGround = true;
                }
                // Bottom collision (hitting platform from below)
                else if (this.velocityY < 0 && this.y - this.velocityY > platform.y + platform.height) {
                    this.y = platform.y + platform.height;
                    this.velocityY = 0;
                }
                // Side collisions
                else if (this.velocityX > 0) {
                    this.x = platform.x - this.width;
                    this.velocityX = 0;
                } else if (this.velocityX < 0) {
                    this.x = platform.x + platform.width;
                    this.velocityX = 0;
                }
            }
        }

        // Boundary collision
        if (this.x < 0) this.x = 0;
        if (this.x + this.width > canvas.width) this.x = canvas.width - this.width;
        if (this.y < 0) {
            this.y = 0;
            this.velocityY = 0;
        }
        if (this.y + this.height > canvas.height) {
            this.y = canvas.height - this.height;
            this.velocityY = 0;
            this.onGround = true;
        }
    }

    checkCollision(platform) {
        return this.x < platform.x + platform.width &&
               this.x + this.width > platform.x &&
               this.y < platform.y + platform.height &&
               this.y + this.height > platform.y;
    }

    draw() {
        ctx.fillStyle = this.color;
        ctx.shadowBlur = 20;
        ctx.shadowColor = this.color;
        ctx.fillRect(this.x, this.y, this.width, this.height);
        ctx.shadowBlur = 0;
    }
}

// Platform class
class Platform {
    constructor(x, y, width, height, color = '#00ffff') {
        this.x = x;
        this.y = y;
        this.width = width;
        this.height = height;
        this.color = color;
    }

    draw() {
        ctx.fillStyle = this.color;
        ctx.shadowBlur = 15;
        ctx.shadowColor = this.color;
        ctx.fillRect(this.x, this.y, this.width, this.height);
        ctx.shadowBlur = 0;
        
        // Add neon glow effect
        ctx.strokeStyle = this.color;
        ctx.lineWidth = 2;
        ctx.shadowBlur = 10;
        ctx.shadowColor = this.color;
        ctx.strokeRect(this.x, this.y, this.width, this.height);
        ctx.shadowBlur = 0;
    }
}

// Goal class
class Goal {
    constructor(x, y) {
        this.x = x;
        this.y = y;
        this.width = 40;
        this.height = 40;
        this.color = '#ff00ff';
        this.pulse = 0;
    }

    update() {
        this.pulse += 0.1;
    }

    draw() {
        ctx.fillStyle = this.color;
        ctx.shadowBlur = 20 + Math.sin(this.pulse) * 10;
        ctx.shadowColor = this.color;
        ctx.fillRect(this.x, this.y, this.width, this.height);
        ctx.shadowBlur = 0;
    }

    checkCollision(player) {
        return player.x < this.x + this.width &&
               player.x + player.width > this.x &&
               player.y < this.y + this.height &&
               player.y + player.height > this.y;
    }
}

// Level definitions
const levels = {
    1: {
        platforms: [
            new Platform(0, 550, 200, 50),
            new Platform(250, 500, 150, 50),
            new Platform(450, 450, 150, 50),
            new Platform(650, 400, 150, 50),
            new Platform(200, 350, 100, 20, '#ff00ff'),
            new Platform(500, 300, 100, 20, '#ff00ff'),
            new Platform(0, 200, 150, 20, '#ff00ff'),
            new Platform(650, 150, 150, 20, '#ff00ff'),
        ],
        playerStart: { x: 50, y: 500 },
        goal: { x: 700, y: 100 }
    },
    2: {
        platforms: [
            new Platform(0, 550, 100, 50),
            new Platform(150, 500, 100, 50),
            new Platform(300, 450, 100, 50),
            new Platform(450, 400, 100, 50),
            new Platform(600, 350, 100, 50),
            new Platform(700, 250, 100, 50),
            new Platform(100, 300, 80, 20, '#ff00ff'),
            new Platform(300, 250, 80, 20, '#ff00ff'),
            new Platform(500, 200, 80, 20, '#ff00ff'),
            new Platform(0, 150, 200, 20, '#ff00ff'),
        ],
        playerStart: { x: 50, y: 500 },
        goal: { x: 720, y: 200 }
    },
    3: {
        platforms: [
            new Platform(0, 550, 150, 50),
            new Platform(200, 500, 100, 50),
            new Platform(350, 450, 100, 50),
            new Platform(500, 400, 100, 50),
            new Platform(650, 500, 150, 50),
            new Platform(100, 350, 100, 20, '#ff00ff'),
            new Platform(300, 300, 100, 20, '#ff00ff'),
            new Platform(550, 250, 100, 20, '#ff00ff'),
            new Platform(0, 200, 150, 20, '#ff00ff'),
            new Platform(200, 150, 100, 20, '#ff00ff'),
            new Platform(450, 100, 100, 20, '#ff00ff'),
            new Platform(650, 50, 150, 20, '#ff00ff'),
        ],
        playerStart: { x: 50, y: 500 },
        goal: { x: 700, y: 10 }
    }
};

let player;
let platforms = [];
let goal;

// Initialize game
function initGame(levelNum) {
    // Stop any existing game loop
    if (animationFrameId !== null) {
        cancelAnimationFrame(animationFrameId);
        animationFrameId = null;
    }
    
    // Clear any pressed keys
    keys = {};
    
    currentLevel = levelNum;
    const level = levels[levelNum];
    
    player = new Player(level.playerStart.x, level.playerStart.y);
    platforms = level.platforms;
    goal = new Goal(level.goal.x, level.goal.y);
    
    document.getElementById('levelDisplay').textContent = levelNum;
    gameRunning = true;
    gameLoop();
}

// Game loop
function gameLoop() {
    if (!gameRunning) {
        animationFrameId = null;
        return;
    }

    // Clear canvas
    ctx.fillStyle = '#0a0a0a';
    ctx.fillRect(0, 0, canvas.width, canvas.height);

    // Update
    player.update(platforms);
    goal.update();

    // Check goal collision
    if (goal.checkCollision(player)) {
        // Level complete
        if (currentLevel < Object.keys(levels).length) {
            gameRunning = false;
            setTimeout(() => {
                initGame(currentLevel + 1);
            }, 500);
            return;
        } else {
            // All levels complete
            gameRunning = false;
            alert('Congratulations! You completed all levels!');
            showMainMenu();
            return;
        }
    }

    // Draw
    platforms.forEach(platform => platform.draw());
    goal.draw();
    player.draw();

    animationFrameId = requestAnimationFrame(gameLoop);
}

// Menu functions
function startGame() {
    document.getElementById('menu').classList.add('hidden');
    document.getElementById('levelSelect').classList.add('hidden');
    document.getElementById('gameContainer').classList.remove('hidden');
    initGame(1);
}

function showLevelSelect() {
    document.getElementById('menu').classList.add('hidden');
    document.getElementById('levelSelect').classList.remove('hidden');
    document.getElementById('gameContainer').classList.add('hidden');
    gameRunning = false;
    if (animationFrameId !== null) {
        cancelAnimationFrame(animationFrameId);
        animationFrameId = null;
    }
    keys = {};
}

function showMainMenu() {
    document.getElementById('menu').classList.remove('hidden');
    document.getElementById('levelSelect').classList.add('hidden');
    document.getElementById('gameContainer').classList.add('hidden');
    gameRunning = false;
    if (animationFrameId !== null) {
        cancelAnimationFrame(animationFrameId);
        animationFrameId = null;
    }
    keys = {};
}

function loadLevel(levelNum) {
    document.getElementById('menu').classList.add('hidden');
    document.getElementById('levelSelect').classList.add('hidden');
    document.getElementById('gameContainer').classList.remove('hidden');
    initGame(levelNum);
}

// Keyboard input
document.addEventListener('keydown', (e) => {
    keys[e.key] = true;
    if (e.key === 'Escape' && gameRunning) {
        showMainMenu();
    }
});

document.addEventListener('keyup', (e) => {
    keys[e.key] = false;
});

// Prevent spacebar from scrolling
window.addEventListener('keydown', (e) => {
    if (e.key === ' ' && e.target === document.body) {
        e.preventDefault();
    }
});

