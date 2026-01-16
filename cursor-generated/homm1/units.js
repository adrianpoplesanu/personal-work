// Unit definitions and management
class Unit {
    constructor(type, x, y, owner, stats) {
        this.type = type;
        this.x = x;
        this.y = y;
        this.owner = owner; // 'player' or 'enemy'
        this.stats = {
            attack: stats.attack || 5,
            defense: stats.defense || 3,
            health: stats.health || 20,
            maxHealth: stats.maxHealth || stats.health || 20,
            speed: stats.speed || 5,
            movementPoints: stats.movementPoints || stats.speed || 5,
            maxMovementPoints: stats.maxMovementPoints || stats.movementPoints || stats.speed || 5,
            damage: stats.damage || { min: 2, max: 4 },
            shots: stats.shots || 0,
            maxShots: stats.maxShots || stats.shots || 0
        };
        this.hasMoved = false;
        this.hasAttacked = false;
        this.color = owner === 'player' ? '#4a9eff' : '#ff4a4a';
        this.minions = []; // Array to store minions for heroes
        this.isHero = type === 'HERO' || type === 'ENEMY_KNIGHT';
    }

    resetTurn() {
        this.hasMoved = false;
        this.hasAttacked = false;
        this.stats.movementPoints = this.stats.maxMovementPoints;
    }

    canMove() {
        return !this.hasMoved && this.stats.movementPoints > 0;
    }

    canAttack() {
        return !this.hasAttacked;
    }

    move(distance) {
        if (this.canMove() && this.stats.movementPoints >= distance) {
            this.stats.movementPoints -= distance;
            return true;
        }
        return false;
    }

    takeDamage(amount) {
        this.stats.health -= amount;
        if (this.stats.health < 0) {
            this.stats.health = 0;
        }
    }

    isAlive() {
        return this.stats.health > 0;
    }

    calculateDamage(target) {
        const baseDamage = Math.floor(Math.random() * (this.stats.damage.max - this.stats.damage.min + 1)) + this.stats.damage.min;
        const attackBonus = this.stats.attack;
        const defenseReduction = target.stats.defense;
        const damage = Math.max(1, baseDamage + attackBonus - defenseReduction);
        return damage;
    }
}

// Unit type definitions
const UnitTypes = {
    HERO: {
        name: 'Hero',
        stats: {
            attack: 8,
            defense: 6,
            health: 50,
            maxHealth: 50,
            speed: 8,
            movementPoints: 8,
            maxMovementPoints: 8,
            damage: { min: 5, max: 8 }
        }
    },
    ARCHER: {
        name: 'Archer',
        stats: {
            attack: 6,
            defense: 3,
            health: 15,
            maxHealth: 15,
            speed: 4,
            movementPoints: 4,
            maxMovementPoints: 4,
            damage: { min: 3, max: 5 },
            shots: 12,
            maxShots: 12
        }
    },
    SWORDSMAN: {
        name: 'Swordsman',
        stats: {
            attack: 7,
            defense: 5,
            health: 25,
            maxHealth: 25,
            speed: 5,
            movementPoints: 5,
            maxMovementPoints: 5,
            damage: { min: 4, max: 6 }
        }
    },
    GRIFFIN: {
        name: 'Griffin',
        stats: {
            attack: 9,
            defense: 4,
            health: 30,
            maxHealth: 30,
            speed: 7,
            movementPoints: 7,
            maxMovementPoints: 7,
            damage: { min: 5, max: 7 }
        }
    },
    ENEMY_KNIGHT: {
        name: 'Enemy Knight',
        stats: {
            attack: 7,
            defense: 6,
            health: 40,
            maxHealth: 40,
            speed: 6,
            movementPoints: 6,
            maxMovementPoints: 6,
            damage: { min: 4, max: 7 }
        }
    },
    ENEMY_ARCHER: {
        name: 'Enemy Archer',
        stats: {
            attack: 5,
            defense: 2,
            health: 12,
            maxHealth: 12,
            speed: 4,
            movementPoints: 4,
            maxMovementPoints: 4,
            damage: { min: 2, max: 4 },
            shots: 10,
            maxShots: 10
        }
    }
};

// Unit manager
class UnitManager {
    constructor() {
        this.units = [];
        this.selectedUnit = null;
    }

    addUnit(type, x, y, owner) {
        const unitType = UnitTypes[type];
        if (!unitType) return null;
        
        const unit = new Unit(type, x, y, owner, { ...unitType.stats });
        this.units.push(unit);
        return unit;
    }

    addMinionToHero(hero, minionType) {
        const unitType = UnitTypes[minionType];
        if (!unitType) return null;
        
        const minion = new Unit(minionType, hero.x, hero.y, hero.owner, { ...unitType.stats });
        hero.minions.push(minion);
        return minion;
    }

    getAllUnitsForCombat(hero) {
        // Returns hero + all their minions for combat
        return [hero, ...hero.minions.filter(m => m.isAlive())];
    }

    getUnitAt(x, y) {
        return this.units.find(u => u.x === x && u.y === y && u.isAlive());
    }

    getUnitsByOwner(owner) {
        return this.units.filter(u => u.owner === owner && u.isAlive());
    }

    removeUnit(unit) {
        const index = this.units.indexOf(unit);
        if (index > -1) {
            this.units.splice(index, 1);
        }
    }

    resetAllTurns() {
        this.units.forEach(unit => unit.resetTurn());
    }

    selectUnit(unit) {
        this.selectedUnit = unit;
    }

    deselectUnit() {
        this.selectedUnit = null;
    }
}

