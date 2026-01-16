// Combat system
class CombatSystem {
    constructor(canvas, combatUI) {
        this.canvas = canvas;
        this.ctx = canvas.getContext('2d');
        this.combatUI = combatUI;
        this.combatLog = document.getElementById('combatLog');
        this.combatTurn = document.getElementById('combatTurn');
        this.playerUnits = [];
        this.enemyUnits = [];
        this.currentTurn = 'player';
        this.selectedCombatUnit = null;
        this.combatGrid = { width: 6, height: 5 };
        this.tileSize = 80; // Increased tile size for better visibility
        this.setupCanvas();
    }

    setupCanvas() {
        // Set canvas internal resolution to match display size
        // We'll set display size via CSS and match internal resolution
        const displayWidth = this.combatGrid.width * this.tileSize;
        const displayHeight = this.combatGrid.height * this.tileSize;
        
        // Set internal canvas size (for drawing)
        this.canvas.width = displayWidth;
        this.canvas.height = displayHeight;
        
        // Set CSS size to match (prevents scaling issues)
        this.canvas.style.width = displayWidth + 'px';
        this.canvas.style.height = displayHeight + 'px';
        
        console.log('Canvas setup:', {
            internal: { width: this.canvas.width, height: this.canvas.height },
            display: { width: displayWidth, height: displayHeight },
            tileSize: this.tileSize,
            grid: this.combatGrid
        });
    }

    initializeCombat(playerUnits, enemyUnits) {
        console.log('Initializing combat with', playerUnits.length, 'player units and', enemyUnits.length, 'enemy units');
        
        // Create combat copies of units
        this.playerUnits = playerUnits.map((unit, index) => {
            const combatUnit = new Unit(unit.type, unit.x, unit.y, unit.owner, { ...unit.stats });
            combatUnit.combatX = 1;
            combatUnit.combatY = Math.min(index, 2); // Limit to 3 rows
            combatUnit.hasActed = false;
            combatUnit.hasMoved = false;
            combatUnit.hasAttacked = false;
            combatUnit.originalUnit = unit; // Keep reference to original
            console.log('Created player unit:', combatUnit.type, 'at combat position', combatUnit.combatX, combatUnit.combatY);
            return combatUnit;
        });
        
        this.enemyUnits = enemyUnits.map((unit, index) => {
            const combatUnit = new Unit(unit.type, unit.x, unit.y, unit.owner, { ...unit.stats });
            combatUnit.combatX = 4;
            combatUnit.combatY = Math.min(index, 2); // Limit to 3 rows
            combatUnit.hasActed = false;
            combatUnit.hasMoved = false;
            combatUnit.hasAttacked = false;
            combatUnit.originalUnit = unit; // Keep reference to original
            return combatUnit;
        });
        
        this.currentTurn = 'player';
        this.selectedCombatUnit = null;
        this.selectedTile = null;
        this.updateCombatUI();
        this.log('Combat begins! Click on a blue unit on the left to select it.');
        console.log('Combat initialized. Player units:', this.playerUnits.map(u => ({type: u.type, x: u.combatX, y: u.combatY})));
    }

    log(message) {
        const entry = document.createElement('div');
        entry.className = 'combat-log-entry';
        entry.textContent = message;
        this.combatLog.appendChild(entry);
        this.combatLog.scrollTop = this.combatLog.scrollHeight;
    }

    updateCombatUI() {
        this.combatTurn.textContent = this.currentTurn === 'player' ? 'Player' : 'Enemy';
    }

    getUnitAt(x, y, units) {
        // Calculate grid position from canvas coordinates
        const gridX = Math.floor(x / this.tileSize);
        const gridY = Math.floor(y / this.tileSize);
        
        // Find unit at this grid position
        const unit = units.find(u => {
            if (!u.isAlive()) return false;
            return u.combatX === gridX && u.combatY === gridY;
        });
        
        if (unit) {
            console.log('Found unit at grid', gridX, gridY, ':', unit.type, 'combat pos', unit.combatX, unit.combatY);
        }
        return unit;
    }

    canAttack(attacker, target) {
        const distance = Math.abs(attacker.combatX - target.combatX) + Math.abs(attacker.combatY - target.combatY);
        return distance <= 1 || (attacker.stats.shots > 0 && distance <= 3);
    }

    performAttack(attacker, target) {
        if (!this.canAttack(attacker, target)) {
            this.log(`${UnitTypes[attacker.type]?.name || attacker.type} cannot reach ${UnitTypes[target.type]?.name || target.type}`);
            return false;
        }

        const damage = attacker.calculateDamage(target);
        target.takeDamage(damage);
        
        this.log(`${UnitTypes[attacker.type]?.name || attacker.type} attacks ${UnitTypes[target.type]?.name || target.type} for ${damage} damage!`);
        
        if (attacker.stats.shots > 0) {
            attacker.stats.shots--;
        }
        
        if (!target.isAlive()) {
            this.log(`${UnitTypes[target.type]?.name || target.type} is defeated!`);
        }
        
        attacker.hasAttacked = true;
        attacker.hasActed = true; // Unit has acted after attacking
        return true;
    }

    canMoveTo(x, y) {
        // Check if position is valid and empty
        if (x < 0 || x >= this.combatGrid.width || y < 0 || y >= this.combatGrid.height) {
            return false;
        }
        
        // Check if there's already a unit there
        const allUnits = [...this.playerUnits, ...this.enemyUnits];
        return !allUnits.some(u => u.combatX === x && u.combatY === y && u.isAlive());
    }

    moveUnit(unit, newX, newY) {
        if (!this.canMoveTo(newX, newY)) {
            return false;
        }
        
        const distance = Math.abs(unit.combatX - newX) + Math.abs(unit.combatY - newY);
        if (distance > 1) {
            this.log('Units can only move 1 space at a time in combat');
            return false;
        }
        
        unit.combatX = newX;
        unit.combatY = newY;
        unit.hasMoved = true;
        this.log(`${UnitTypes[unit.type]?.name || unit.type} moves to (${newX}, ${newY})`);
        return true;
    }

    endTurn() {
        if (this.currentTurn === 'player') {
            // Check if all player units have acted (moved or attacked)
            const playerCanAct = this.playerUnits.some(u => u.isAlive() && !u.hasActed);
            if (playerCanAct) {
                const inactiveUnits = this.playerUnits.filter(u => u.isAlive() && !u.hasActed);
                this.log(`Some units still need to act! (${inactiveUnits.length} remaining)`);
                return;
            }
            
            // Reset player units for next turn
            this.playerUnits.forEach(u => {
                u.hasActed = false;
                u.hasMoved = false;
                u.hasAttacked = false;
            });
            
            this.currentTurn = 'enemy';
            this.selectedCombatUnit = null;
            this.selectedTile = null;
            this.updateCombatUI();
            this.log('Enemy turn begins');
            
            // AI turn
            setTimeout(() => this.enemyTurn(), 500);
        } else {
            // Reset enemy units
            this.enemyUnits.forEach(u => {
                u.hasActed = false;
                u.hasMoved = false;
                u.hasAttacked = false;
            });
            
            this.currentTurn = 'player';
            this.selectedCombatUnit = null;
            this.selectedTile = null;
            this.updateCombatUI();
            this.log('Player turn begins. Select a unit to move or attack.');
        }
    }

    enemyTurn() {
        // Simple AI: attack nearest player unit
        for (const enemy of this.enemyUnits) {
            if (!enemy.isAlive() || enemy.hasActed) continue;
            
            // Find nearest player unit
            let nearestPlayer = null;
            let minDistance = Infinity;
            
            for (const player of this.playerUnits) {
                if (!player.isAlive()) continue;
                
                const distance = Math.abs(enemy.combatX - player.combatX) + Math.abs(enemy.combatY - player.combatY);
                if (distance < minDistance) {
                    minDistance = distance;
                    nearestPlayer = player;
                }
            }
            
            if (nearestPlayer && this.canAttack(enemy, nearestPlayer)) {
                this.performAttack(enemy, nearestPlayer);
            } else if (nearestPlayer) {
                // Move towards player
                const dx = nearestPlayer.combatX - enemy.combatX;
                const dy = nearestPlayer.combatY - enemy.combatY;
                
                const newX = enemy.combatX + (dx !== 0 ? Math.sign(dx) : 0);
                const newY = enemy.combatY + (dy !== 0 ? Math.sign(dy) : 0);
                
                if (this.canMoveTo(newX, newY)) {
                    this.moveUnit(enemy, newX, newY);
                } else {
                    // Try alternative move
                    if (dy !== 0 && this.canMoveTo(enemy.combatX, enemy.combatY + Math.sign(dy))) {
                        this.moveUnit(enemy, enemy.combatX, enemy.combatY + Math.sign(dy));
                    } else if (dx !== 0 && this.canMoveTo(enemy.combatX + Math.sign(dx), enemy.combatY)) {
                        this.moveUnit(enemy, enemy.combatX + Math.sign(dx), enemy.combatY);
                    }
                }
                
                // Check if can attack after moving
                if (nearestPlayer && this.canAttack(enemy, nearestPlayer)) {
                    this.performAttack(enemy, nearestPlayer);
                } else {
                    enemy.hasActed = true;
                }
            } else {
                enemy.hasActed = true;
            }
        }
        
        this.endTurn();
    }

    checkCombatEnd() {
        const playerAlive = this.playerUnits.some(u => u.isAlive());
        const enemyAlive = this.enemyUnits.some(u => u.isAlive());
        
        if (!playerAlive) {
            this.log('All your units have been defeated!');
            return 'defeat';
        }
        if (!enemyAlive) {
            this.log('All enemy units have been defeated!');
            return 'victory';
        }
        return null;
    }

    render() {
        this.ctx.clearRect(0, 0, this.canvas.width, this.canvas.height);
        
        // Draw combat grid
        for (let y = 0; y < this.combatGrid.height; y++) {
            for (let x = 0; x < this.combatGrid.width; x++) {
                const screenX = x * this.tileSize;
                const screenY = y * this.tileSize;
                
                this.ctx.fillStyle = (x + y) % 2 === 0 ? '#4a4a6a' : '#3a3a5a';
                this.ctx.fillRect(screenX, screenY, this.tileSize, this.tileSize);
                
                this.ctx.strokeStyle = '#8b7355';
                this.ctx.lineWidth = 1;
                this.ctx.strokeRect(screenX, screenY, this.tileSize, this.tileSize);
            }
        }
        
        // Draw movement/attack range for selected unit
        if (this.selectedCombatUnit && this.currentTurn === 'player' && !this.selectedCombatUnit.hasActed) {
            const unit = this.selectedCombatUnit;
            const range = unit.stats.shots > 0 ? 3 : 1; // Ranged units can attack from 3 spaces
            
            for (let y = 0; y < this.combatGrid.height; y++) {
                for (let x = 0; x < this.combatGrid.width; x++) {
                    const distance = Math.abs(unit.combatX - x) + Math.abs(unit.combatY - y);
                    if (distance <= range && distance > 0) {
                        const screenX = x * this.tileSize;
                        const screenY = y * this.tileSize;
                        
                        // Check if it's an attackable enemy or moveable space
                        const target = this.getUnitAt(x, y, this.enemyUnits);
                        if (target && this.canAttack(unit, target)) {
                            // Highlight attackable enemy
                            this.ctx.fillStyle = 'rgba(255, 0, 0, 0.3)';
                            this.ctx.fillRect(screenX, screenY, this.tileSize, this.tileSize);
                        } else if (distance === 1 && this.canMoveTo(x, y) && !unit.hasMoved) {
                            // Highlight moveable space
                            this.ctx.fillStyle = 'rgba(0, 255, 0, 0.2)';
                            this.ctx.fillRect(screenX, screenY, this.tileSize, this.tileSize);
                        }
                    }
                }
            }
        }
        
        // Draw units
        [...this.playerUnits, ...this.enemyUnits].forEach((unit, index) => {
            if (!unit.isAlive()) return;
            
            const screenX = unit.combatX * this.tileSize;
            const screenY = unit.combatY * this.tileSize;
            
            // Debug: log unit positions on first render
            if (index === 0 && this.playerUnits.length > 0) {
                console.log('Rendering unit:', unit.type, 'at screen', screenX, screenY, 'combat pos', unit.combatX, unit.combatY);
            }
            
            // Draw unit with different colors based on state
            let unitColor = unit.owner === 'player' ? '#4a9eff' : '#ff4a4a';
            if (unit.owner === 'player' && unit.hasActed) {
                unitColor = '#666'; // Gray out units that have acted
            }
            
            this.ctx.fillStyle = unitColor;
            this.ctx.beginPath();
            this.ctx.arc(
                screenX + this.tileSize / 2,
                screenY + this.tileSize / 2,
                this.tileSize / 2 - 5,
                0,
                Math.PI * 2
            );
            this.ctx.fill();
            
            // Draw border - thicker for selectable units
            this.ctx.strokeStyle = unit.owner === 'player' && !unit.hasActed ? '#fff' : '#888';
            this.ctx.lineWidth = unit.owner === 'player' && !unit.hasActed ? 3 : 2;
            this.ctx.stroke();
            
            // Draw health bar
            const healthPercent = unit.stats.health / unit.stats.maxHealth;
            const barWidth = this.tileSize - 10;
            const barHeight = 6;
            const barX = screenX + 5;
            const barY = screenY + this.tileSize - 10;
            
            this.ctx.fillStyle = '#ff0000';
            this.ctx.fillRect(barX, barY, barWidth, barHeight);
            
            this.ctx.fillStyle = '#00ff00';
            this.ctx.fillRect(barX, barY, barWidth * healthPercent, barHeight);
            
            // Draw unit type label
            this.ctx.fillStyle = '#fff';
            this.ctx.font = 'bold 11px Arial';
            this.ctx.textAlign = 'center';
            this.ctx.textBaseline = 'middle';
            const unitName = UnitTypes[unit.type]?.name || unit.type;
            this.ctx.fillText(unitName, screenX + this.tileSize / 2, screenY + this.tileSize / 2 - 8);
            
            // Draw status indicators
            if (unit.hasActed) {
                this.ctx.fillStyle = '#ff0';
                this.ctx.font = 'bold 9px Arial';
                this.ctx.fillText('DONE', screenX + this.tileSize / 2, screenY + this.tileSize - 8);
            } else if (unit.owner === 'player') {
                // Show "CLICK" hint for selectable units
                this.ctx.fillStyle = '#0ff';
                this.ctx.font = '8px Arial';
                this.ctx.fillText('CLICK', screenX + this.tileSize / 2, screenY + this.tileSize - 8);
            }
        });
        
        // Draw selected unit highlight
        if (this.selectedCombatUnit && this.currentTurn === 'player') {
            const unit = this.selectedCombatUnit;
            const screenX = unit.combatX * this.tileSize;
            const screenY = unit.combatY * this.tileSize;
            
            this.ctx.strokeStyle = '#ffff00';
            this.ctx.lineWidth = 3;
            this.ctx.strokeRect(screenX, screenY, this.tileSize, this.tileSize);
        }
    }

    handleClick(x, y) {
        // Get actual canvas dimensions (accounting for any CSS scaling)
        const rect = this.canvas.getBoundingClientRect();
        const scaleX = this.canvas.width / rect.width;
        const scaleY = this.canvas.height / rect.height;
        
        // Convert click coordinates to canvas coordinates
        const canvasX = (x - rect.left) * scaleX;
        const canvasY = (y - rect.top) * scaleY;
        
        // Calculate grid coordinates based on actual canvas size
        const gridX = Math.floor(canvasX / this.tileSize);
        const gridY = Math.floor(canvasY / this.tileSize);
        
        console.log('handleClick called:', {
            click: { x, y },
            rect: { left: rect.left, top: rect.top, width: rect.width, height: rect.height },
            scale: { x: scaleX, y: scaleY },
            canvas: { x: canvasX, y: canvasY },
            grid: { x: gridX, y: gridY },
            tileSize: this.tileSize
        });
        
        if (this.currentTurn !== 'player') {
            this.log('Wait for your turn!');
            return;
        }
        
        // Check if clicking on a player unit to select (using canvas coordinates)
        const clickedPlayerUnit = this.getUnitAt(canvasX, canvasY, this.playerUnits);
        console.log('Clicked unit (canvas coords):', clickedPlayerUnit);
        console.log('Grid coordinates:', gridX, gridY);
        
        // If screen-based didn't work, try grid-based
        if (!clickedPlayerUnit) {
            const gridBasedUnit = this.playerUnits.find(u => 
                u.combatX === gridX && u.combatY === gridY && u.isAlive()
            );
            if (gridBasedUnit) {
                console.log('Found unit via grid coordinates');
                if (gridBasedUnit.hasActed) {
                    this.log(`${UnitTypes[gridBasedUnit.type]?.name || gridBasedUnit.type} has already acted this turn`);
                    return;
                }
                this.selectedCombatUnit = gridBasedUnit;
                const unitName = UnitTypes[gridBasedUnit.type]?.name || gridBasedUnit.type;
                this.log(`Selected ${unitName}. Click an enemy to attack or an empty space to move.`);
                return;
            }
        }
        
        if (clickedPlayerUnit) {
            if (clickedPlayerUnit.hasActed) {
                this.log(`${UnitTypes[clickedPlayerUnit.type]?.name || clickedPlayerUnit.type} has already acted this turn`);
                return;
            }
            this.selectedCombatUnit = clickedPlayerUnit;
            const unitName = UnitTypes[clickedPlayerUnit.type]?.name || clickedPlayerUnit.type;
            this.log(`Selected ${unitName}. Click an enemy to attack or an empty space to move.`);
            console.log('Unit selected:', unitName);
            return;
        }
        
        // If a unit is selected, try to move or attack
        if (this.selectedCombatUnit && !this.selectedCombatUnit.hasActed) {
            const unit = this.selectedCombatUnit;
            
            // Check if clicking on an enemy unit to attack (using canvas coordinates)
            const target = this.getUnitAt(canvasX, canvasY, this.enemyUnits);
            if (target && this.canAttack(unit, target)) {
                this.performAttack(unit, target);
                this.selectedCombatUnit = null;
                
                // Check for combat end
                const result = this.checkCombatEnd();
                if (result) {
                    setTimeout(() => {
                        if (result === 'victory') {
                            this.log('Victory!');
                        } else {
                            this.log('Defeat!');
                        }
                    }, 1000);
                }
                return;
            }
            
            // Check if clicking on an empty space to move
            if (!unit.hasMoved && this.canMoveTo(gridX, gridY)) {
                const distance = Math.abs(unit.combatX - gridX) + Math.abs(unit.combatY - gridY);
                if (distance === 1) {
                    this.moveUnit(unit, gridX, gridY);
                    // Don't deselect - allow unit to attack after moving
                    // If unit can't attack, mark as acted
                    const canStillAttack = this.enemyUnits.some(enemy => 
                        enemy.isAlive() && this.canAttack(unit, enemy)
                    );
                    if (!canStillAttack) {
                        unit.hasActed = true;
                        this.selectedCombatUnit = null;
                        this.log(`${UnitTypes[unit.type]?.name || unit.type} has finished their turn`);
                    }
                    return;
                } else {
                    this.log('Can only move 1 space at a time');
                    return;
                }
            }
            
            // If clicking on invalid target, show message
            if (target) {
                this.log('Cannot attack that target from here');
            } else if (!this.canMoveTo(gridX, gridY)) {
                this.log('Cannot move there');
            }
        } else if (this.selectedCombatUnit && this.selectedCombatUnit.hasActed) {
            this.log('This unit has already acted. Select another unit.');
            this.selectedCombatUnit = null;
        } else {
            console.log('No action taken. Click on a unit to select, or select a unit first.');
        }
    }
}

