# Simple Platformer - Unity Project

This is a Unity implementation of the same platformer game created in HTML5/JavaScript.

## Setup Instructions

1. **Open in Unity:**
   - Open Unity Hub
   - Click "Add" and select the `UnityPlatformer` folder
   - The project should open with Unity 2022.3.0f1 or later

2. **Scene Setup:**
   - The project includes a `LevelSetup` script that will automatically create all game objects
   - Open the scene: `Assets/Scenes/GameScene.unity`
   - If the scene doesn't exist or is empty, create a new scene and add the following:
     - Main Camera (2D)
     - Empty GameObject with `GameManager` script
     - Empty GameObject with `LevelSetup` script
     - Canvas for UI (with TextMeshPro components for score and lives)
     - Game Over Panel (initially disabled)

3. **Create Game Objects:**
   - Create a Player GameObject:
     - Add a SpriteRenderer (or use a colored quad)
     - Add a BoxCollider2D
     - Add the `PlayerController` script
     - Tag: "Player"
     - Color: Red (#FF6B6B)
   
   - Create a Platform Prefab:
     - Add a SpriteRenderer (or use a colored quad)
     - Add a BoxCollider2D
     - Add the `Platform` script
     - Tag: "Platform"
     - Color: Teal (#4ECDC4)
   
   - Create a Coin Prefab:
     - Add a SpriteRenderer (circle sprite)
     - Add a CircleCollider2D (set as trigger)
     - Add the `Coin` script
     - Tag: "Coin"
     - Color: Gold (#FFD700)
   
   - Create a Goal Prefab:
     - Add a SpriteRenderer
     - Add a BoxCollider2D (set as trigger)
     - Add the `Goal` script
     - Tag: "Goal"
     - Color: Green (#51CF66)

4. **Assign Prefabs to LevelSetup:**
   - Select the GameObject with `LevelSetup` script
   - In the Inspector, assign the prefabs you created to the corresponding fields

5. **Setup UI:**
   - Create a Canvas
   - Add TextMeshPro text for Score and Lives
   - Create a Game Over Panel with:
     - TextMeshPro text for game over message
     - Button for restart
   - Assign these UI elements to the `GameManager` script in the Inspector

6. **Camera Setup:**
   - Set Camera to Orthographic
   - Position at (0, 0, -10)
   - Size: 3 (adjust to fit the game view)

## Game Features

- **Player Controls:**
  - A/D or Arrow Keys: Move left/right
  - Space/W/Up Arrow: Jump

- **Game Mechanics:**
  - Physics-based movement with gravity
  - Platform collision detection
  - Collectible coins (6 total, 10 points each)
  - Lives system (3 lives)
  - Win condition: Reach the green flag

- **Game Elements:**
  - 11 platforms arranged in a challenging path
  - 6 collectible coins
  - 1 goal flag at the top right
  - Score and lives tracking
  - Game over screen with restart functionality

## Scripts Overview

- **PlayerController.cs**: Handles player movement, jumping, physics, and collision detection
- **GameManager.cs**: Manages game state, score, lives, UI updates, and game over logic
- **Coin.cs**: Collectible item that adds to score when collected
- **Goal.cs**: Win condition trigger
- **Platform.cs**: Static platform with collision
- **LevelSetup.cs**: Automatically creates all game objects at runtime

## Notes

- The game uses Unity's 2D physics system
- Coordinates are converted from the original canvas-based game (800x600) to Unity's coordinate system
- The game will automatically set up all platforms, coins, and the goal when the scene starts
- Make sure to set up the UI elements and assign them to the GameManager in the Inspector

