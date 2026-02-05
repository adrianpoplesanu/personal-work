// Game State
const gameState = {
    turn: 1,
    playerTurn: true,
    playerHealth: 30,
    playerMana: 1,
    playerManaMax: 1,
    opponentHealth: 30,
    opponentMana: 0,
    opponentManaMax: 0,
    playerHand: [],
    opponentHand: [],
    playerBoard: [],
    opponentBoard: [],
    selectedCard: null,
    selectedTarget: null,
    gameOver: false
};

// Card Database
const cardDatabase = [
    { id: 1, name: "Fireball", cost: 4, attack: 0, health: 0, description: "Deal 6 damage", type: "spell", effect: "damage", value: 6 },
    { id: 2, name: "Lightning Bolt", cost: 1, attack: 0, health: 0, description: "Deal 3 damage", type: "spell", effect: "damage", value: 3 },
    { id: 3, name: "Heal", cost: 2, attack: 0, health: 0, description: "Restore 5 health", type: "spell", effect: "heal", value: 5 },
    { id: 4, name: "Peasant", cost: 1, attack: 1, health: 1, description: "A weak minion", type: "minion" },
    { id: 5, name: "Orc Warrior", cost: 3, attack: 3, health: 2, description: "A fierce fighter", type: "minion" },
    { id: 6, name: "Dragon", cost: 8, attack: 8, health: 8, description: "A powerful beast", type: "minion" },
    { id: 7, name: "Knight", cost: 4, attack: 3, health: 5, description: "A sturdy defender", type: "minion" },
    { id: 8, name: "Goblin", cost: 2, attack: 2, health: 1, description: "Quick but fragile", type: "minion" },
    { id: 9, name: "Shield", cost: 1, attack: 0, health: 0, description: "Gain 5 armor", type: "spell", effect: "armor", value: 5 },
    { id: 10, name: "Wolf", cost: 2, attack: 2, health: 2, description: "A loyal companion", type: "minion" }
];

// Initialize Game
function initGame() {
    // Draw initial hands
    for (let i = 0; i < 3; i++) {
        drawCard(true);
        drawCard(false);
    }
    
    updateUI();
    setupEventListeners();
}

// Draw a card
function drawCard(isPlayer) {
    const hand = isPlayer ? gameState.playerHand : gameState.opponentHand;
    if (hand.length >= 10) return; // Max hand size
    
    const randomCard = { ...cardDatabase[Math.floor(Math.random() * cardDatabase.length)] };
    randomCard.instanceId = Date.now() + Math.random();
    hand.push(randomCard);
    
    if (isPlayer) {
        renderHand();
    }
}

// Render Hand
function renderHand() {
    const handArea = document.getElementById('hand-area');
    handArea.innerHTML = '';
    
    gameState.playerHand.forEach((card, index) => {
        const cardElement = createCardElement(card, true, index);
        handArea.appendChild(cardElement);
    });
}

// Create Card Element
function createCardElement(card, isPlayer, index = null) {
    const cardDiv = document.createElement('div');
    cardDiv.className = 'card';
    cardDiv.dataset.cardId = card.instanceId;
    
    if (isPlayer && card.cost <= gameState.playerMana && !gameState.selectedCard) {
        cardDiv.classList.add('playable');
    }
    
    const header = document.createElement('div');
    header.className = 'card-header';
    
    const cost = document.createElement('div');
    cost.className = 'card-cost';
    cost.textContent = card.cost;
    header.appendChild(cost);
    
    if (card.type === 'minion') {
        const attack = document.createElement('div');
        attack.className = 'card-attack';
        attack.textContent = card.attack;
        header.appendChild(attack);
    }
    
    const body = document.createElement('div');
    body.className = 'card-body';
    
    const name = document.createElement('div');
    name.className = 'card-name';
    name.textContent = card.name;
    body.appendChild(name);
    
    const description = document.createElement('div');
    description.className = 'card-description';
    description.textContent = card.description;
    body.appendChild(description);
    
    const footer = document.createElement('div');
    footer.className = 'card-footer';
    
    if (card.type === 'minion') {
        const health = document.createElement('div');
        health.className = 'card-health';
        health.textContent = card.health;
        footer.appendChild(health);
    }
    
    cardDiv.appendChild(header);
    cardDiv.appendChild(body);
    cardDiv.appendChild(footer);
    
    return cardDiv;
}

// Render Board
function renderBoard() {
    const playerBoard = document.getElementById('player-board');
    const opponentBoard = document.getElementById('opponent-board');
    
    playerBoard.innerHTML = '';
    opponentBoard.innerHTML = '';
    
    gameState.playerBoard.forEach((minion, index) => {
        const minionElement = createMinionElement(minion, true, index);
        playerBoard.appendChild(minionElement);
    });
    
    gameState.opponentBoard.forEach((minion, index) => {
        const minionElement = createMinionElement(minion, false, index);
        opponentBoard.appendChild(minionElement);
    });
}

// Create Minion Element
function createMinionElement(minion, isPlayer, index) {
    const minionDiv = document.createElement('div');
    minionDiv.className = 'card minion';
    minionDiv.dataset.minionId = minion.instanceId;
    minionDiv.dataset.index = index;
    minionDiv.dataset.isPlayer = isPlayer ? 'true' : 'false';
    
    if (isPlayer && minion.canAttack) {
        if (!gameState.selectedCard || gameState.selectedCard.instanceId === minion.instanceId) {
            minionDiv.classList.add('can-attack');
        }
    }
    
    if (!isPlayer && gameState.selectedCard && gameState.selectedCard.canAttack) {
        minionDiv.classList.add('attackable');
    }
    
    const header = document.createElement('div');
    header.className = 'card-header';
    
    if (minion.cost) {
        const cost = document.createElement('div');
        cost.className = 'card-cost';
        cost.textContent = minion.cost;
        header.appendChild(cost);
    }
    
    const attack = document.createElement('div');
    attack.className = 'card-attack';
    attack.textContent = minion.attack;
    header.appendChild(attack);
    
    const body = document.createElement('div');
    body.className = 'card-body';
    
    const name = document.createElement('div');
    name.className = 'card-name';
    name.textContent = minion.name;
    body.appendChild(name);
    
    const footer = document.createElement('div');
    footer.className = 'card-footer';
    
    const health = document.createElement('div');
    health.className = 'card-health';
    health.textContent = minion.health;
    footer.appendChild(health);
    
    minionDiv.appendChild(header);
    minionDiv.appendChild(body);
    minionDiv.appendChild(footer);
    
    return minionDiv;
}

// Setup Event Listeners
function setupEventListeners() {
    document.getElementById('end-turn-btn').addEventListener('click', endTurn);
    
    // Card click handlers are added dynamically in renderHand
    document.addEventListener('click', handleCardClick);
}

// Handle Card Click
function handleCardClick(event) {
    // Don't handle clicks on buttons
    if (event.target.closest('.end-turn-btn')) return;
    
    // Handle opponent hero attack first (before checking for cards)
    const opponentPortrait = event.target.closest('.opponent-portrait');
    if (opponentPortrait && gameState.selectedCard && gameState.playerTurn) {
        attackHero(false);
        return;
    }
    
    const cardElement = event.target.closest('.card');
    
    if (!cardElement) {
        // Clicked elsewhere, deselect
        if (gameState.selectedCard) {
            gameState.selectedCard = null;
            updateUI();
        }
        return;
    }
    
    const cardId = cardElement.dataset.cardId;
    const minionId = cardElement.dataset.minionId;
    
    // If we have a selected minion and click on an opponent minion, attack it
    // Check if this is an opponent minion by checking if it's in the opponent board
    if (minionId && gameState.selectedCard && gameState.playerTurn) {
        // Check if this minion is in the opponent board (not in player board)
        const target = gameState.opponentBoard.find(m => m.instanceId == minionId);
        const isPlayerMinionCheck = gameState.playerBoard.find(m => m.instanceId == minionId);
        
        if (target && !isPlayerMinionCheck && gameState.selectedCard.canAttack) {
            attackMinion(gameState.selectedCard, target);
            return;
        }
    }
    
    const isPlayerMinion = cardElement.dataset.isPlayer === 'true';
    
    // Check if clicking on a card in hand
    if (cardId) {
        // Only process if we don't have a selected minion
        if (!gameState.selectedCard && gameState.playerTurn) {
            const card = gameState.playerHand.find(c => c.instanceId == cardId);
            if (card && card.cost <= gameState.playerMana) {
                if (card.type === 'spell') {
                    playSpell(card);
                } else if (card.type === 'minion') {
                    if (gameState.playerBoard.length < 7) {
                        playMinion(card);
                    } else {
                        alert('Board is full!');
                    }
                }
            }
        }
        return;
    }
    
    // Handle player minion clicks
    if (minionId && isPlayerMinion && gameState.playerTurn) {
        const minion = gameState.playerBoard.find(m => m.instanceId == minionId);
        if (minion) {
            if (minion.canAttack) {
                // Select this minion for attack
                if (gameState.selectedCard && gameState.selectedCard.instanceId === minion.instanceId) {
                    // Deselect if clicking the same minion
                    gameState.selectedCard = null;
                } else {
                    // Select this minion
                    gameState.selectedCard = minion;
                }
                highlightTargets();
            }
        }
        return;
    }
    
    // If we get here and have a selected card, deselect it
    if (gameState.selectedCard) {
        gameState.selectedCard = null;
        updateUI();
    }
}

// Play Minion
function playMinion(card) {
    const minion = { ...card };
    // Minions can't attack the turn they're played (summoning sickness)
    minion.canAttack = false;
    // Ensure type is preserved
    if (!minion.type) {
        minion.type = 'minion';
    }
    
    gameState.playerBoard.push(minion);
    gameState.playerMana -= card.cost;
    gameState.playerHand = gameState.playerHand.filter(c => c.instanceId !== card.instanceId);
    
    // Clear selection if any
    gameState.selectedCard = null;
    
    updateUI();
}

// Play Spell
function playSpell(card) {
    if (card.effect === 'damage') {
        // For simplicity, damage spells target a random enemy minion or hero
        if (gameState.opponentBoard.length > 0) {
            const target = gameState.opponentBoard[Math.floor(Math.random() * gameState.opponentBoard.length)];
            dealDamage(target, card.value);
        } else {
            dealDamageToHero(false, card.value);
        }
    } else if (card.effect === 'heal') {
        gameState.playerHealth = Math.min(30, gameState.playerHealth + card.value);
    } else if (card.effect === 'armor') {
        // Armor would be separate, but for simplicity we'll just heal
        gameState.playerHealth = Math.min(30, gameState.playerHealth + card.value);
    }
    
    gameState.playerMana -= card.cost;
    gameState.playerHand = gameState.playerHand.filter(c => c.instanceId !== card.instanceId);
    
    updateUI();
}

// Attack Minion
function attackMinion(attacker, defender) {
    dealDamage(defender, attacker.attack);
    dealDamage(attacker, defender.attack);
    
    attacker.canAttack = false;
    gameState.selectedCard = null;
    
    // Remove dead minions
    gameState.playerBoard = gameState.playerBoard.filter(m => m.health > 0);
    gameState.opponentBoard = gameState.opponentBoard.filter(m => m.health > 0);
    
    updateUI();
}

// Attack Hero
function attackHero(isPlayer) {
    if (!gameState.selectedCard || !gameState.selectedCard.canAttack) return;
    
    if (isPlayer) {
        dealDamageToHero(true, gameState.selectedCard.attack);
    } else {
        dealDamageToHero(false, gameState.selectedCard.attack);
    }
    
    gameState.selectedCard.canAttack = false;
    gameState.selectedCard = null;
    updateUI();
}

// Deal Damage
function dealDamage(target, damage) {
    target.health -= damage;
    
    // Find the DOM element for this minion to show damage popup
    if (target.instanceId) {
        const element = document.querySelector(`[data-minion-id="${target.instanceId}"]`);
        if (element) {
            showDamagePopup(element, damage);
        }
    }
    
    if (target.health <= 0) {
        setTimeout(() => {
            if (target.instanceId) {
                const element = document.querySelector(`[data-minion-id="${target.instanceId}"]`);
                if (element) {
                    element.classList.add('dying');
                    setTimeout(() => {
                        gameState.playerBoard = gameState.playerBoard.filter(m => m.instanceId !== target.instanceId);
                        gameState.opponentBoard = gameState.opponentBoard.filter(m => m.instanceId !== target.instanceId);
                        updateUI();
                    }, 500);
                }
            }
        }, 100);
    }
}

// Deal Damage to Hero
function dealDamageToHero(isPlayer, damage) {
    if (isPlayer) {
        gameState.playerHealth = Math.max(0, gameState.playerHealth - damage);
    } else {
        gameState.opponentHealth = Math.max(0, gameState.opponentHealth - damage);
    }
    
    const heroElement = isPlayer ? document.querySelector('.player-portrait') : document.querySelector('.opponent-portrait');
    showDamagePopup(heroElement, damage);
    
    checkGameOver();
}

// Show Damage Popup
function showDamagePopup(target, damage) {
    const popup = document.createElement('div');
    popup.className = 'damage-popup';
    popup.textContent = `-${damage}`;
    
    const rect = target.getBoundingClientRect();
    popup.style.left = (rect.left + rect.width / 2) + 'px';
    popup.style.top = (rect.top + rect.height / 2) + 'px';
    
    document.body.appendChild(popup);
    
    setTimeout(() => {
        popup.remove();
    }, 1000);
}

// Highlight Targets
function highlightTargets() {
    // Update UI to show which targets can be attacked
    updateUI();
    
    // Also highlight opponent hero portrait
    const opponentPortrait = document.querySelector('.opponent-portrait');
    if (opponentPortrait && gameState.selectedCard && gameState.selectedCard.canAttack) {
        opponentPortrait.style.border = '3px solid #ff4444';
        opponentPortrait.style.boxShadow = '0 0 20px rgba(255, 68, 68, 0.6)';
        opponentPortrait.style.cursor = 'pointer';
    }
}

// End Turn
function endTurn() {
    if (!gameState.playerTurn) return;
    
    gameState.playerTurn = false;
    
    // Reset minion attack status
    gameState.playerBoard.forEach(minion => {
        minion.canAttack = true;
    });
    
    // Opponent's turn
    setTimeout(() => {
        opponentTurn();
    }, 1000);
}

// Opponent Turn
function opponentTurn() {
    gameState.turn++;
    gameState.opponentManaMax = Math.min(10, Math.floor(gameState.turn / 2));
    gameState.opponentMana = gameState.opponentManaMax;
    
    drawCard(false);
    
    // Track which minions were on the board at the start of the turn
    const minionsAtStartOfTurn = gameState.opponentBoard.map(m => m.instanceId);
    
    updateUI();
    
    // Simple AI: play cards and attack
    setTimeout(() => {
        opponentPlayCards(minionsAtStartOfTurn);
    }, 500);
    
    setTimeout(() => {
        opponentAttack(minionsAtStartOfTurn);
    }, 2000);
    
    setTimeout(() => {
        endOpponentTurn();
    }, 3000);
}

// Opponent Play Cards
function opponentPlayCards(minionsAtStartOfTurn) {
    const playableCards = gameState.opponentHand.filter(card => 
        card.cost <= gameState.opponentMana
    );
    
    playableCards.sort((a, b) => b.cost - a.cost); // Play expensive cards first
    
    for (const card of playableCards) {
        if (gameState.opponentMana >= card.cost) {
            if (card.type === 'minion' && gameState.opponentBoard.length < 7) {
                const minion = { ...card };
                minion.canAttack = false;
                gameState.opponentBoard.push(minion);
                gameState.opponentMana -= card.cost;
                gameState.opponentHand = gameState.opponentHand.filter(c => c.instanceId !== card.instanceId);
            } else if (card.type === 'spell') {
                if (card.effect === 'damage') {
                    if (gameState.playerBoard.length > 0) {
                        const target = gameState.playerBoard[Math.floor(Math.random() * gameState.playerBoard.length)];
                        dealDamage(target, card.value);
                    } else {
                        dealDamageToHero(true, card.value);
                    }
                } else if (card.effect === 'heal') {
                    gameState.opponentHealth = Math.min(30, gameState.opponentHealth + card.value);
                }
                gameState.opponentMana -= card.cost;
                gameState.opponentHand = gameState.opponentHand.filter(c => c.instanceId !== card.instanceId);
            }
        }
    }
    
    updateUI();
}

// Opponent Attack
function opponentAttack(minionsAtStartOfTurn) {
    // Only reset attack status for minions that were on the board at the start of the turn
    // Newly played minions should not be able to attack
    gameState.opponentBoard.forEach(minion => {
        if (minionsAtStartOfTurn.includes(minion.instanceId)) {
            minion.canAttack = true;
        }
    });
    
    // Attack with minions that can attack
    const attackers = [...gameState.opponentBoard].filter(m => m.canAttack);
    
    for (const attacker of attackers) {
        // Stop if game is over
        if (gameState.gameOver) break;
        
        if (gameState.playerBoard.length > 0) {
            // Attack a random player minion
            const target = gameState.playerBoard[Math.floor(Math.random() * gameState.playerBoard.length)];
            attackMinion(attacker, target);
        } else {
            // Attack player hero
            dealDamageToHero(true, attacker.attack);
            attacker.canAttack = false;
        }
    }
    
    updateUI();
}

// End Opponent Turn
function endOpponentTurn() {
    gameState.playerTurn = true;
    gameState.turn++;
    gameState.playerManaMax = Math.min(10, Math.floor((gameState.turn + 1) / 2));
    gameState.playerMana = gameState.playerManaMax;
    
    drawCard(true);
    
    // Reset minion attack status
    gameState.playerBoard.forEach(minion => {
        minion.canAttack = true;
    });
    
    updateUI();
}

// Update UI
function updateUI() {
    document.getElementById('player-health').textContent = gameState.playerHealth;
    document.getElementById('player-mana').textContent = gameState.playerMana;
    document.getElementById('player-mana-max').textContent = gameState.playerManaMax;
    
    document.getElementById('opponent-health').textContent = gameState.opponentHealth;
    document.getElementById('opponent-mana').textContent = gameState.opponentMana;
    document.getElementById('opponent-mana-max').textContent = gameState.opponentManaMax;
    
    document.getElementById('turn-number').textContent = gameState.turn;
    document.getElementById('turn-indicator').textContent = gameState.playerTurn ? 'Your Turn' : "Opponent's Turn";
    
    document.getElementById('end-turn-btn').disabled = !gameState.playerTurn;
    
    // Reset opponent portrait styling
    const opponentPortrait = document.querySelector('.opponent-portrait');
    if (opponentPortrait) {
        if (gameState.selectedCard && gameState.selectedCard.canAttack && gameState.playerTurn) {
            opponentPortrait.style.border = '3px solid #ff4444';
            opponentPortrait.style.boxShadow = '0 0 20px rgba(255, 68, 68, 0.6)';
            opponentPortrait.style.cursor = 'pointer';
        } else {
            opponentPortrait.style.border = '';
            opponentPortrait.style.boxShadow = '';
            opponentPortrait.style.cursor = '';
        }
    }
    
    renderHand();
    renderBoard();
}

// Check Game Over
function checkGameOver() {
    // Only check if game is not already over
    if (gameState.gameOver) return;
    
    if (gameState.playerHealth <= 0) {
        gameState.gameOver = true;
        setTimeout(() => {
            alert('You Lose!');
            location.reload();
        }, 500);
    } else if (gameState.opponentHealth <= 0) {
        gameState.gameOver = true;
        setTimeout(() => {
            alert('You Win!');
            location.reload();
        }, 500);
    }
}

// Start Game
initGame();

