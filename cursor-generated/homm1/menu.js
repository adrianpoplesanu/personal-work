// Menu system
let gameInstance = null;

document.addEventListener('DOMContentLoaded', () => {
    const startGameBtn = document.getElementById('startGameBtn');
    const resumeBtn = document.getElementById('resumeBtn');
    const mainMenuBtn = document.getElementById('mainMenuBtn');
    const instructionsBtn = document.getElementById('instructionsBtn');
    
    startGameBtn.addEventListener('click', () => {
        startGame();
    });
    
    resumeBtn.addEventListener('click', () => {
        resumeGame();
    });
    
    mainMenuBtn.addEventListener('click', () => {
        returnToMainMenu();
    });
    
    instructionsBtn.addEventListener('click', () => {
        showInstructions();
    });
});

function startGame() {
    // Hide main menu
    document.getElementById('mainMenu').classList.add('hidden');
    
    // Show game container
    document.getElementById('gameContainer').classList.remove('hidden');
    
    // Initialize game
    if (!gameInstance) {
        gameInstance = new Game();
    }
}

function resumeGame() {
    // Hide pause menu
    document.getElementById('pauseMenu').classList.add('hidden');
    
    if (gameInstance) {
        gameInstance.isPaused = false;
    }
}

function returnToMainMenu() {
    // Hide pause menu and game container
    document.getElementById('pauseMenu').classList.add('hidden');
    document.getElementById('gameContainer').classList.add('hidden');
    document.getElementById('combatScreen').classList.add('hidden');
    
    // Show main menu
    document.getElementById('mainMenu').classList.remove('hidden');
    
    // Reset game
    if (gameInstance) {
        gameInstance = null;
        // Reload page to reset everything
        location.reload();
    }
}

function showInstructions() {
    alert(`Heroes of Might and Magic 2 - Clone

INSTRUCTIONS:
- Click on your units to select them
- Click on tiles to move (yellow highlight shows path)
- Click on enemy units adjacent to your units to attack
- Each unit has movement points that limit how far they can move
- Use the "End Turn" button to end your turn
- Press ESC to pause the game

COMBAT:
- Combat is turn-based
- Click on your units to select them
- Click on enemy units to attack
- Use "End Turn" to finish your turn

GOAL:
- Defeat all enemy units on the map!`);
}

