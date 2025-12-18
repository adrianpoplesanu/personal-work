// Game Canvas Setup
const canvas = document.getElementById('gameCanvas');
const ctx = canvas.getContext('2d');
canvas.width = 800;
canvas.height = 600;

// Game State
let score = 0;
let lives = 3;
let gameRunning = true;

// Player Object
const player = {
    x: 50,
    y: 100,
    width: 40,
    height: 40,
    velocityX: 0,
    velocityY: 0,
    speed: 5,
    jumpPower: -15,
    onGround: false,
    color: '#FF6B6B'
};

// Platforms
const platforms = [
    { x: 0, y: 550, width: 200, height: 50, color: '#4ECDC4' },
    { x: 250, y: 500, width: 150, height: 50, color: '#4ECDC4' },
    { x: 450, y: 450, width: 150, height: 50, color: '#4ECDC4' },
    { x: 650, y: 400, width: 150, height: 50, color: '#4ECDC4' },
    { x: 200, y: 350, width: 120, height: 50, color: '#4ECDC4' },
    { x: 400, y: 300, width: 120, height: 50, color: '#4ECDC4' },
    { x: 600, y: 250, width: 120, height: 50, color: '#4ECDC4' },
    { x: 100, y: 200, width: 100, height: 50, color: '#4ECDC4' },
    { x: 300, y: 150, width: 100, height: 50, color: '#4ECDC4' },
    { x: 500, y: 100, width: 100, height: 50, color: '#4ECDC4' },
    { x: 700, y: 50, width: 100, height: 50, color: '#4ECDC4' }
];

// Goal (flag)
const goal = {
    x: 720,
    y: 10,
    width: 30,
    height: 40,
    color: '#51CF66'
};

// Collectibles (coins)
const coins = [
    { x: 300, y: 450, width: 20, height: 20, collected: false },
    { x: 500, y: 400, width: 20, height: 20, collected: false },
    { x: 250, y: 300, width: 20, height: 20, collected: false },
    { x: 450, y: 250, width: 20, height: 20, collected: false },
    { x: 150, y: 150, width: 20, height: 20, collected: false },
    { x: 550, y: 50, width: 20, height: 20, collected: false }
];

// Input Handling
const keys = {};

window.addEventListener('keydown', (e) => {
    keys[e.key.toLowerCase()] = true;
    if (e.key === ' ' || e.key === 'w' || e.key === 'ArrowUp') {
        e.preventDefault();
    }
});

window.addEventListener('keyup', (e) => {
    keys[e.key.toLowerCase()] = false;
});

// Collision Detection
function checkCollision(rect1, rect2) {
    return rect1.x < rect2.x + rect2.width &&
           rect1.x + rect1.width > rect2.x &&
           rect1.y < rect2.y + rect2.height &&
           rect1.y + rect1.height > rect2.y;
}

// Update Player
function updatePlayer() {
    // Horizontal Movement
    if (keys['a'] || keys['arrowleft']) {
        player.velocityX = -player.speed;
    } else if (keys['d'] || keys['arrowright']) {
        player.velocityX = player.speed;
    } else {
        player.velocityX *= 0.8; // Friction
    }

    // Jumping
    if ((keys[' '] || keys['w'] || keys['arrowup']) && player.onGround) {
        player.velocityY = player.jumpPower;
        player.onGround = false;
    }

    // Apply Gravity
    player.velocityY += 0.8; // Gravity
    player.velocityY = Math.min(player.velocityY, 15); // Terminal velocity

    // Update Position
    player.x += player.velocityX;
    player.y += player.velocityY;

    // Platform Collision
    player.onGround = false;
    for (let platform of platforms) {
        if (checkCollision(player, platform)) {
            // Landing on top of platform
            if (player.velocityY > 0 && player.y < platform.y) {
                player.y = platform.y - player.height;
                player.velocityY = 0;
                player.onGround = true;
            }
            // Hitting platform from below
            else if (player.velocityY < 0 && player.y > platform.y) {
                player.y = platform.y + platform.height;
                player.velocityY = 0;
            }
            // Side collisions
            else if (player.velocityX > 0) {
                player.x = platform.x - player.width;
                player.velocityX = 0;
            } else if (player.velocityX < 0) {
                player.x = platform.x + platform.width;
                player.velocityX = 0;
            }
        }
    }

    // Boundary Collision
    if (player.x < 0) {
        player.x = 0;
        player.velocityX = 0;
    }
    if (player.x + player.width > canvas.width) {
        player.x = canvas.width - player.width;
        player.velocityX = 0;
    }

    // Fall off screen
    if (player.y > canvas.height) {
        lives--;
        resetPlayer();
        if (lives <= 0) {
            endGame(false);
        }
    }

    // Collect Coins
    for (let coin of coins) {
        if (!coin.collected && checkCollision(player, coin)) {
            coin.collected = true;
            score += 10;
            updateUI();
        }
    }

    // Check Win Condition
    if (checkCollision(player, goal)) {
        endGame(true);
    }
}

// Reset Player Position
function resetPlayer() {
    player.x = 50;
    player.y = 100;
    player.velocityX = 0;
    player.velocityY = 0;
    updateUI();
}

// Draw Functions
function drawPlayer() {
    ctx.fillStyle = player.color;
    ctx.fillRect(player.x, player.y, player.width, player.height);
    
    // Draw eyes
    ctx.fillStyle = '#FFF';
    ctx.fillRect(player.x + 8, player.y + 10, 8, 8);
    ctx.fillRect(player.x + 24, player.y + 10, 8, 8);
}

function drawPlatforms() {
    platforms.forEach(platform => {
        ctx.fillStyle = platform.color;
        ctx.fillRect(platform.x, platform.y, platform.width, platform.height);
        
        // Add highlight for depth
        ctx.fillStyle = 'rgba(255, 255, 255, 0.3)';
        ctx.fillRect(platform.x, platform.y, platform.width, 5);
    });
}

function drawGoal() {
    // Flag pole
    ctx.fillStyle = '#333';
    ctx.fillRect(goal.x + 10, goal.y, 5, goal.height);
    
    // Flag
    ctx.fillStyle = goal.color;
    ctx.beginPath();
    ctx.moveTo(goal.x + 15, goal.y + 5);
    ctx.lineTo(goal.x + 15, goal.y + 20);
    ctx.lineTo(goal.x + 30, goal.y + 12.5);
    ctx.closePath();
    ctx.fill();
}

function drawCoins() {
    coins.forEach(coin => {
        if (!coin.collected) {
            ctx.fillStyle = '#FFD700';
            ctx.beginPath();
            ctx.arc(coin.x + coin.width/2, coin.y + coin.height/2, coin.width/2, 0, Math.PI * 2);
            ctx.fill();
            
            // Coin shine
            ctx.fillStyle = '#FFF';
            ctx.beginPath();
            ctx.arc(coin.x + coin.width/2 - 3, coin.y + coin.height/2 - 3, 4, 0, Math.PI * 2);
            ctx.fill();
        }
    });
}

// UI Updates
function updateUI() {
    document.getElementById('score').textContent = `Score: ${score}`;
    document.getElementById('lives').textContent = `Lives: ${lives}`;
}

// Game Over
function endGame(won) {
    gameRunning = false;
    const gameOverDiv = document.getElementById('gameOver');
    const gameOverText = document.getElementById('gameOverText');
    
    if (won) {
        gameOverText.textContent = `You Win! Score: ${score}`;
        gameOverText.style.color = '#51CF66';
    } else {
        gameOverText.textContent = 'Game Over!';
        gameOverText.style.color = '#FF6B6B';
    }
    
    gameOverDiv.classList.remove('hidden');
}

// Restart Game
document.getElementById('restartBtn').addEventListener('click', () => {
    score = 0;
    lives = 3;
    gameRunning = true;
    document.getElementById('gameOver').classList.add('hidden');
    
    // Reset coins
    coins.forEach(coin => coin.collected = false);
    
    resetPlayer();
});

// Game Loop
function gameLoop() {
    // Clear Canvas
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    
    if (gameRunning) {
        updatePlayer();
    }
    
    // Draw Everything
    drawPlatforms();
    drawCoins();
    drawGoal();
    drawPlayer();
    
    requestAnimationFrame(gameLoop);
}

// Initialize
updateUI();
gameLoop();

