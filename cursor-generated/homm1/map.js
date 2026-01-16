// Tile map system
class TileMap {
    constructor(width, height, tileSize = 32) {
        this.width = width;
        this.height = height;
        this.tileSize = tileSize;
        this.tiles = [];
        this.initializeMap();
    }

    initializeMap() {
        // Create a simple map with different terrain types
        for (let y = 0; y < this.height; y++) {
            this.tiles[y] = [];
            for (let x = 0; x < this.width; x++) {
                // Random terrain generation
                const rand = Math.random();
                let terrain = 'grass';
                let movementCost = 1;
                
                if (rand < 0.1) {
                    terrain = 'water';
                    movementCost = 3;
                } else if (rand < 0.2) {
                    terrain = 'mountain';
                    movementCost = 2;
                } else if (rand < 0.3) {
                    terrain = 'forest';
                    movementCost = 1.5;
                } else if (rand < 0.4) {
                    terrain = 'desert';
                    movementCost = 1.2;
                }
                
                this.tiles[y][x] = {
                    terrain: terrain,
                    movementCost: movementCost,
                    x: x,
                    y: y
                };
            }
        }
    }

    getTile(x, y) {
        if (x >= 0 && x < this.width && y >= 0 && y < this.height) {
            return this.tiles[y][x];
        }
        return null;
    }

    getMovementCost(x, y) {
        const tile = this.getTile(x, y);
        return tile ? tile.movementCost : 999;
    }

    isValidPosition(x, y) {
        return x >= 0 && x < this.width && y >= 0 && y < this.height;
    }

    getDistance(x1, y1, x2, y2) {
        return Math.abs(x1 - x2) + Math.abs(y1 - y2);
    }

    // Find path using simple A* (simplified)
    findPath(startX, startY, endX, endY, maxMovement) {
        const visited = new Set();
        const queue = [{ x: startX, y: startY, cost: 0, path: [] }];
        
        while (queue.length > 0) {
            queue.sort((a, b) => a.cost - b.cost);
            const current = queue.shift();
            const key = `${current.x},${current.y}`;
            
            if (visited.has(key)) continue;
            visited.add(key);
            
            if (current.x === endX && current.y === endY) {
                return current.path;
            }
            
            const neighbors = [
                { x: current.x + 1, y: current.y },
                { x: current.x - 1, y: current.y },
                { x: current.x, y: current.y + 1 },
                { x: current.x, y: current.y - 1 }
            ];
            
            for (const neighbor of neighbors) {
                if (!this.isValidPosition(neighbor.x, neighbor.y)) continue;
                
                const tile = this.getTile(neighbor.x, neighbor.y);
                const newCost = current.cost + tile.movementCost;
                
                if (newCost <= maxMovement) {
                    const neighborKey = `${neighbor.x},${neighbor.y}`;
                    if (!visited.has(neighborKey)) {
                        queue.push({
                            x: neighbor.x,
                            y: neighbor.y,
                            cost: newCost,
                            path: [...current.path, { x: neighbor.x, y: neighbor.y }]
                        });
                    }
                }
            }
        }
        
        return [];
    }
}

// Map renderer
class MapRenderer {
    constructor(canvas, tileMap) {
        this.canvas = canvas;
        this.ctx = canvas.getContext('2d');
        this.tileMap = tileMap;
        this.cameraX = 0;
        this.cameraY = 0;
    }

    setCamera(x, y) {
        this.cameraX = x;
        this.cameraY = y;
    }

    getTerrainColor(terrain) {
        const colors = {
            grass: '#4a7c3a',
            water: '#2a4a7a',
            mountain: '#6a6a6a',
            forest: '#2a5a2a',
            desert: '#d4a574'
        };
        return colors[terrain] || '#4a7c3a';
    }

    drawTile(x, y, tile) {
        const screenX = x * this.tileMap.tileSize - this.cameraX;
        const screenY = y * this.tileMap.tileSize - this.cameraY;
        
        // Draw terrain
        this.ctx.fillStyle = this.getTerrainColor(tile.terrain);
        this.ctx.fillRect(screenX, screenY, this.tileMap.tileSize, this.tileMap.tileSize);
        
        // Draw grid
        this.ctx.strokeStyle = 'rgba(0, 0, 0, 0.3)';
        this.ctx.lineWidth = 1;
        this.ctx.strokeRect(screenX, screenY, this.tileMap.tileSize, this.tileMap.tileSize);
    }

    drawHighlight(x, y, color = 'rgba(255, 255, 0, 0.5)') {
        const screenX = x * this.tileMap.tileSize - this.cameraX;
        const screenY = y * this.tileMap.tileSize - this.cameraY;
        
        this.ctx.fillStyle = color;
        this.ctx.fillRect(screenX, screenY, this.tileMap.tileSize, this.tileMap.tileSize);
    }

    drawPath(path) {
        path.forEach((tile, index) => {
            const alpha = 0.3 + (index / path.length) * 0.3;
            this.drawHighlight(tile.x, tile.y, `rgba(100, 200, 255, ${alpha})`);
        });
    }

    drawUnit(unit) {
        const screenX = unit.x * this.tileMap.tileSize - this.cameraX;
        const screenY = unit.y * this.tileMap.tileSize - this.cameraY;
        
        // Draw unit circle
        this.ctx.fillStyle = unit.color;
        this.ctx.beginPath();
        this.ctx.arc(
            screenX + this.tileMap.tileSize / 2,
            screenY + this.tileMap.tileSize / 2,
            this.tileMap.tileSize / 2 - 2,
            0,
            Math.PI * 2
        );
        this.ctx.fill();
        
        // Draw border
        this.ctx.strokeStyle = '#fff';
        this.ctx.lineWidth = 2;
        this.ctx.stroke();
        
        // Draw health bar
        const healthPercent = unit.stats.health / unit.stats.maxHealth;
        const barWidth = this.tileMap.tileSize - 4;
        const barHeight = 4;
        const barX = screenX + 2;
        const barY = screenY + this.tileMap.tileSize - 6;
        
        this.ctx.fillStyle = '#ff0000';
        this.ctx.fillRect(barX, barY, barWidth, barHeight);
        
        this.ctx.fillStyle = '#00ff00';
        this.ctx.fillRect(barX, barY, barWidth * healthPercent, barHeight);
    }

    render(unitManager, selectedTile = null, path = []) {
        // Clear canvas
        this.ctx.clearRect(0, 0, this.canvas.width, this.canvas.height);
        
        // Draw tiles
        for (let y = 0; y < this.tileMap.height; y++) {
            for (let x = 0; x < this.tileMap.width; x++) {
                const tile = this.tileMap.getTile(x, y);
                if (tile) {
                    this.drawTile(x, y, tile);
                }
            }
        }
        
        // Draw path
        if (path.length > 0) {
            this.drawPath(path);
        }
        
        // Draw selected tile highlight
        if (selectedTile) {
            this.drawHighlight(selectedTile.x, selectedTile.y, 'rgba(255, 255, 0, 0.4)');
        }
        
        // Draw only heroes on the map (minions are only shown in combat)
        unitManager.units.forEach(unit => {
            if (unit.isAlive() && unit.isHero) {
                this.drawUnit(unit);
            }
        });
        
        // Draw selected unit highlight
        if (unitManager.selectedUnit) {
            const unit = unitManager.selectedUnit;
            this.drawHighlight(unit.x, unit.y, 'rgba(0, 255, 255, 0.5)');
        }
    }
}

