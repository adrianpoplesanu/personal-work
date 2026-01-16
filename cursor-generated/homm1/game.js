// Main game logic
class Game {
    constructor() {
        this.canvas = document.getElementById('gameCanvas');
        this.ctx = this.canvas.getContext('2d');
        this.unitManager = new UnitManager();
        this.tileMap = new TileMap(30, 20, 32);
        this.renderer = new MapRenderer(this.canvas, this.tileMap);
        this.combatSystem = new CombatSystem(
            document.getElementById('combatCanvas'),
            document.getElementById('combatUI')
        );
        
        this.currentTurn = 'player';
        this.selectedTile = null;
        this.path = [];
        this.isPaused = false;
        this.isInCombat = false;
        this.combatClickHandler = null;
        this.isDragging = false;
        this.dragStartX = 0;
        this.dragStartY = 0;
        this.scrollLeft = 0;
        this.scrollTop = 0;
        
        this.setupCanvas();
        this.setupEventListeners();
        this.initializeGame();
    }

    setupCanvas() {
        this.canvas.width = 1800;
        this.canvas.height = 1200;
    }

    setupEventListeners() {
        const gameContainer = document.getElementById('gameContainer');
        
        // Canvas click
        this.canvas.addEventListener('click', (e) => {
            if (this.isInCombat || this.isDragging) return;
            this.handleCanvasClick(e);
        });
        
        // Canvas mouse move
        this.canvas.addEventListener('mousemove', (e) => {
            if (this.isInCombat) return;
            if (this.isDragging) {
                this.handleDrag(e);
                return;
            }
            this.handleMouseMove(e);
        });
        
        // Mouse down for dragging (middle mouse button or right mouse button)
        this.canvas.addEventListener('mousedown', (e) => {
            if (this.isInCombat) return;
            if (e.button === 1 || e.button === 2) { // Middle or right mouse button
                this.isDragging = true;
                this.dragStartX = e.clientX + gameContainer.scrollLeft;
                this.dragStartY = e.clientY + gameContainer.scrollTop;
                this.canvas.style.cursor = 'grabbing';
                e.preventDefault();
            }
        });
        
        // Mouse up
        this.canvas.addEventListener('mouseup', (e) => {
            if (this.isDragging) {
                this.isDragging = false;
                this.canvas.style.cursor = 'pointer';
            }
        });
        
        // Mouse leave
        this.canvas.addEventListener('mouseleave', () => {
            if (this.isDragging) {
                this.isDragging = false;
                this.canvas.style.cursor = 'pointer';
            }
        });
        
        
        // Prevent context menu on right click
        this.canvas.addEventListener('contextmenu', (e) => {
            if (this.isDragging) {
                e.preventDefault();
            }
        });
        
        // Keyboard
        document.addEventListener('keydown', (e) => {
            if (this.isInCombat || this.isPaused) {
                if (e.key === 'Escape') {
                    this.togglePause();
                }
                return;
            }
            
            if (e.key === 'Escape') {
                this.togglePause();
            } else if (e.key === 'E' || e.key === 'e') {
                if (this.currentTurn === 'player') {
                    this.endTurn();
                }
            } else {
                // Arrow key panning
                const scrollAmount = 50;
                if (e.key === 'ArrowLeft') {
                    gameContainer.scrollLeft -= scrollAmount;
                    e.preventDefault();
                } else if (e.key === 'ArrowRight') {
                    gameContainer.scrollLeft += scrollAmount;
                    e.preventDefault();
                } else if (e.key === 'ArrowUp') {
                    gameContainer.scrollTop -= scrollAmount;
                    e.preventDefault();
                } else if (e.key === 'ArrowDown') {
                    gameContainer.scrollTop += scrollAmount;
                    e.preventDefault();
                }
            }
        });
        
        // End turn button
        document.getElementById('endTurnBtn').addEventListener('click', () => {
            this.endTurn();
        });
        
        // Combat canvas click - attach when combat starts
        // We'll attach this in initiateCombat to ensure it's set up correctly
        
        // Combat end turn
        document.getElementById('combatEndTurn').addEventListener('click', () => {
            this.combatSystem.endTurn();
            this.combatSystem.render(); // Re-render after ending turn
        });
    }

    initializeGame() {
        // Create player hero
        const hero = this.unitManager.addUnit('HERO', 5, 5, 'player');
        
        // Add minions to the hero (they only appear in combat)
        this.unitManager.addMinionToHero(hero, 'ARCHER');
        this.unitManager.addMinionToHero(hero, 'SWORDSMAN');
        this.unitManager.addMinionToHero(hero, 'GRIFFIN');
        
        // Create enemy heroes (enemies are also heroes on the map)
        const enemyHero1 = this.unitManager.addUnit('ENEMY_KNIGHT', 20, 15, 'enemy');
        this.unitManager.addMinionToHero(enemyHero1, 'ENEMY_ARCHER');
        
        const enemyHero2 = this.unitManager.addUnit('ENEMY_KNIGHT', 20, 16, 'enemy');
        this.unitManager.addMinionToHero(enemyHero2, 'ENEMY_ARCHER');
        
        // Center view on hero by scrolling
        const gameContainer = document.getElementById('gameContainer');
        const heroScreenX = hero.x * this.tileMap.tileSize;
        const heroScreenY = hero.y * this.tileMap.tileSize;
        // Scroll to center hero (accounting for viewport size)
        gameContainer.scrollLeft = heroScreenX - window.innerWidth / 2;
        gameContainer.scrollTop = heroScreenY - window.innerHeight / 2;
        
        // Set camera to 0,0 since we're using scrolling now
        this.renderer.setCamera(0, 0);
        
        this.updateUI();
        this.gameLoop();
    }

    handleDrag(e) {
        const gameContainer = document.getElementById('gameContainer');
        const newScrollLeft = this.dragStartX - e.clientX;
        const newScrollTop = this.dragStartY - e.clientY;
        gameContainer.scrollLeft = newScrollLeft;
        gameContainer.scrollTop = newScrollTop;
    }

    handleCanvasClick(e) {
        const rect = this.canvas.getBoundingClientRect();
        const gameContainer = document.getElementById('gameContainer');
        // Account for scroll position
        const x = Math.floor((e.clientX - rect.left + gameContainer.scrollLeft) / this.tileMap.tileSize);
        const y = Math.floor((e.clientY - rect.top + gameContainer.scrollTop) / this.tileMap.tileSize);
        
        if (!this.tileMap.isValidPosition(x, y)) return;
        
        if (this.currentTurn !== 'player') return;
        
        const clickedUnit = this.unitManager.getUnitAt(x, y);
        
        // If clicking on a player hero, select it (allow re-selection even if already moved)
        if (clickedUnit && clickedUnit.owner === 'player' && clickedUnit.isHero) {
            // If clicking the same unit, just re-select it
            if (this.unitManager.selectedUnit === clickedUnit) {
                // Already selected, just update UI
                this.selectedTile = null;
                this.path = [];
                this.updateUI();
                return;
            }
            // Select the hero (even if it has already moved)
            this.unitManager.selectUnit(clickedUnit);
            this.selectedTile = null;
            this.path = [];
            this.updateUI();
            return;
        }
        
        // If a unit is selected, try to move or attack
        if (this.unitManager.selectedUnit) {
            const selectedUnit = this.unitManager.selectedUnit;
            
            // Check if clicking on an enemy hero
            if (clickedUnit && clickedUnit.owner === 'enemy' && clickedUnit.isHero) {
                const distance = this.tileMap.getDistance(selectedUnit.x, selectedUnit.y, x, y);
                if (distance === 1) {
                    // Attack
                    this.initiateCombat(selectedUnit, clickedUnit);
                }
                return;
            }
            
            // Try to move
            if (this.path.length > 0) {
                const moveCost = this.path.reduce((sum, tile) => {
                    return sum + this.tileMap.getMovementCost(tile.x, tile.y);
                }, 0);
                
                if (selectedUnit.move(moveCost)) {
                    const lastTile = this.path[this.path.length - 1];
                    selectedUnit.x = lastTile.x;
                    selectedUnit.y = lastTile.y;
                    selectedUnit.hasMoved = true;
                    this.unitManager.deselectUnit();
                    this.selectedTile = null;
                    this.path = [];
                    this.updateUI();
                }
            }
        }
    }

    handleMouseMove(e) {
        const rect = this.canvas.getBoundingClientRect();
        const gameContainer = document.getElementById('gameContainer');
        // Account for scroll position
        const x = Math.floor((e.clientX - rect.left + gameContainer.scrollLeft) / this.tileMap.tileSize);
        const y = Math.floor((e.clientY - rect.top + gameContainer.scrollTop) / this.tileMap.tileSize);
        
        if (!this.tileMap.isValidPosition(x, y)) return;
        
        this.selectedTile = { x, y };
        
        // Calculate path if unit is selected
        if (this.unitManager.selectedUnit && this.currentTurn === 'player') {
            const unit = this.unitManager.selectedUnit;
            if (unit.canMove()) {
                this.path = this.tileMap.findPath(
                    unit.x,
                    unit.y,
                    x,
                    y,
                    unit.stats.movementPoints
                );
            }
        }
    }

    initiateCombat(attacker, defender) {
        this.isInCombat = true;
        
        // Get all units for combat: hero + their minions
        const playerUnits = this.unitManager.getAllUnitsForCombat(attacker);
        const enemyUnits = this.unitManager.getAllUnitsForCombat(defender);
        
        // Show combat screen
        document.getElementById('combatScreen').classList.remove('hidden');
        document.getElementById('gameContainer').classList.add('hidden');
        
        // Initialize combat
        this.combatSystem.initializeCombat(playerUnits, enemyUnits);
        this.combatSystem.render();
        
        // Attach click handler to combat canvas
        const combatCanvas = document.getElementById('combatCanvas');
        const clickHandler = (e) => {
            if (!this.isInCombat) return;
            // Pass the raw click coordinates - handleClick will handle the conversion
            const x = e.clientX;
            const y = e.clientY;
            console.log('Combat canvas clicked at screen:', x, y);
            this.combatSystem.handleClick(x, y);
            this.combatSystem.render();
        };
        
        // Remove old listener if any
        combatCanvas.removeEventListener('click', this.combatClickHandler);
        this.combatClickHandler = clickHandler;
        combatCanvas.addEventListener('click', clickHandler);
        
        // Start combat loop
        this.combatLoop();
    }

    endCombat(result) {
        this.isInCombat = false;
        document.getElementById('combatScreen').classList.add('hidden');
        document.getElementById('gameContainer').classList.remove('hidden');
        
        // Sync combat results back to original units
        this.combatSystem.playerUnits.forEach(combatUnit => {
            if (combatUnit.originalUnit) {
                combatUnit.originalUnit.stats.health = combatUnit.stats.health;
                combatUnit.originalUnit.stats.shots = combatUnit.stats.shots;
                
                // Remove defeated minions
                if (!combatUnit.isAlive() && !combatUnit.originalUnit.isHero) {
                    const hero = this.unitManager.units.find(u => u.minions.includes(combatUnit.originalUnit));
                    if (hero) {
                        const index = hero.minions.indexOf(combatUnit.originalUnit);
                        if (index > -1) {
                            hero.minions.splice(index, 1);
                        }
                    }
                }
            }
        });
        
        this.combatSystem.enemyUnits.forEach(combatUnit => {
            if (combatUnit.originalUnit) {
                combatUnit.originalUnit.stats.health = combatUnit.stats.health;
                combatUnit.originalUnit.stats.shots = combatUnit.stats.shots;
                
                // Remove defeated enemy heroes or minions
                if (!combatUnit.isAlive() && result === 'victory') {
                    if (combatUnit.originalUnit.isHero) {
                        this.unitManager.removeUnit(combatUnit.originalUnit);
                    } else {
                        // Remove minion from hero
                        const hero = this.unitManager.units.find(u => u.minions.includes(combatUnit.originalUnit));
                        if (hero) {
                            const index = hero.minions.indexOf(combatUnit.originalUnit);
                            if (index > -1) {
                                hero.minions.splice(index, 1);
                            }
                        }
                    }
                }
            }
        });
        
        // Reset combat log
        document.getElementById('combatLog').innerHTML = '';
        
        // Reset turns
        this.unitManager.resetAllTurns();
        this.updateUI();
    }

    combatLoop() {
        if (!this.isInCombat) return;
        
        this.combatSystem.render();
        
        // Check for combat end
        const result = this.combatSystem.checkCombatEnd();
        if (result) {
            this.isInCombat = false; // Stop the loop
            setTimeout(() => {
                this.endCombat(result);
            }, 2000);
            return;
        }
        
        requestAnimationFrame(() => this.combatLoop());
    }

    endTurn() {
        if (this.currentTurn === 'player') {
            this.currentTurn = 'enemy';
            this.unitManager.deselectUnit();
            this.selectedTile = null;
            this.path = [];
            
            // Enemy AI turn
            setTimeout(() => this.enemyTurn(), 500);
        }
    }

    enemyTurn() {
        const enemyHeroes = this.unitManager.getUnitsByOwner('enemy').filter(u => u.isHero);
        
        for (const enemy of enemyHeroes) {
            if (!enemy.isAlive() || enemy.hasMoved) continue;
            
            // Find nearest player hero
            const playerHeroes = this.unitManager.getUnitsByOwner('player').filter(u => u.isHero);
            let nearestPlayer = null;
            let minDistance = Infinity;
            
            for (const player of playerHeroes) {
                if (!player.isAlive()) continue;
                
                const distance = this.tileMap.getDistance(enemy.x, enemy.y, player.x, player.y);
                if (distance < minDistance) {
                    minDistance = distance;
                    nearestPlayer = player;
                }
            }
            
            if (nearestPlayer) {
                // Move towards player or attack if adjacent
                if (minDistance === 1) {
                    // Attack
                    this.initiateCombat(enemy, nearestPlayer);
                    return;
                } else {
                    // Move towards player
                    const path = this.tileMap.findPath(
                        enemy.x,
                        enemy.y,
                        nearestPlayer.x,
                        nearestPlayer.y,
                        enemy.stats.movementPoints
                    );
                    
                    if (path.length > 0) {
                        const moveCost = path.slice(0, 1).reduce((sum, tile) => {
                            return sum + this.tileMap.getMovementCost(tile.x, tile.y);
                        }, 0);
                        
                        if (enemy.move(moveCost)) {
                            const nextTile = path[0];
                            enemy.x = nextTile.x;
                            enemy.y = nextTile.y;
                            enemy.hasMoved = true;
                        }
                    }
                }
            }
        }
        
        // Reset enemy units for next turn
        enemyHeroes.forEach(unit => unit.resetTurn());
        
        // Switch back to player
        this.currentTurn = 'player';
        this.unitManager.resetAllTurns();
        this.updateUI();
    }

    updateUI() {
        const playerHeroes = this.unitManager.getUnitsByOwner('player').filter(u => u.isHero);
        const totalMovement = playerHeroes.reduce((sum, u) => sum + u.stats.movementPoints, 0);
        
        document.getElementById('movementPoints').textContent = totalMovement;
        
        if (this.unitManager.selectedUnit) {
            const unit = this.unitManager.selectedUnit;
            document.getElementById('unitInfo').classList.remove('hidden');
            document.getElementById('unitName').textContent = UnitTypes[unit.type].name + ` (${unit.minions.length} minions)`;
            document.getElementById('unitStats').innerHTML = `
                HP: ${unit.stats.health}/${unit.stats.maxHealth}<br>
                Attack: ${unit.stats.attack}<br>
                Defense: ${unit.stats.defense}<br>
                Movement: ${unit.stats.movementPoints}/${unit.stats.maxMovementPoints}<br>
                Minions: ${unit.minions.filter(m => m.isAlive()).length}
            `;
        } else {
            document.getElementById('unitInfo').classList.add('hidden');
        }
    }

    togglePause() {
        this.isPaused = !this.isPaused;
        const pauseMenu = document.getElementById('pauseMenu');
        if (this.isPaused) {
            pauseMenu.classList.remove('hidden');
        } else {
            pauseMenu.classList.add('hidden');
        }
    }

    gameLoop() {
        if (!this.isPaused && !this.isInCombat) {
            this.renderer.render(this.unitManager, this.selectedTile, this.path);
            this.updateUI();
        }
        
        requestAnimationFrame(() => this.gameLoop());
    }
}

// Game class is initialized from menu.js

