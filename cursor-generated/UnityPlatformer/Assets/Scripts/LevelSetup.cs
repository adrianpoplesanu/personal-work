using UnityEngine;

public class LevelSetup : MonoBehaviour
{
    [Header("Prefabs")]
    public GameObject playerPrefab;
    public GameObject platformPrefab;
    public GameObject coinPrefab;
    public GameObject goalPrefab;
    
    void Start()
    {
        SetupLevel();
    }
    
    void SetupLevel()
    {
        // Convert canvas coordinates (800x600, top-left origin) to Unity coordinates
        // Canvas: (0,0) top-left, (800,600) bottom-right
        // Unity 2D: approximately (-4,-3) to (4,3) with camera at (0,0)
        // Conversion: x = (canvasX - 400) / 100, y = (300 - canvasY) / 100
        
        // Create Player (canvas: x=50, y=100)
        if (playerPrefab != null)
        {
            Vector3 playerPos = new Vector3(-3.5f, 2f, 0f);
            Instantiate(playerPrefab, playerPos, Quaternion.identity);
        }
        
        // Create Platforms
        if (platformPrefab != null)
        {
            // Platform positions from game.js (converted to Unity coordinates)
            Vector2[] platformPositions = new Vector2[]
            {
                new Vector2(-4f, -0.5f),    // (0, 550)
                new Vector2(-1.5f, 0f),     // (250, 500)
                new Vector2(0.5f, 0.5f),     // (450, 450)
                new Vector2(2.5f, 1f),      // (650, 400)
                new Vector2(-2f, 1.5f),       // (200, 350)
                new Vector2(0f, 2f),         // (400, 300)
                new Vector2(2f, 2.5f),       // (600, 250)
                new Vector2(-3f, 3f),        // (100, 200)
                new Vector2(-1f, 3.5f),      // (300, 150)
                new Vector2(1f, 4f),         // (500, 100)
                new Vector2(3f, 4.5f)        // (700, 50)
            };
            
            Vector2[] platformSizes = new Vector2[]
            {
                new Vector2(2f, 0.5f),      // (200, 50)
                new Vector2(1.5f, 0.5f),    // (150, 50)
                new Vector2(1.5f, 0.5f),     // (150, 50)
                new Vector2(1.5f, 0.5f),     // (150, 50)
                new Vector2(1.2f, 0.5f),     // (120, 50)
                new Vector2(1.2f, 0.5f),     // (120, 50)
                new Vector2(1.2f, 0.5f),     // (120, 50)
                new Vector2(1f, 0.5f),       // (100, 50)
                new Vector2(1f, 0.5f),       // (100, 50)
                new Vector2(1f, 0.5f),       // (100, 50)
                new Vector2(1f, 0.5f)        // (100, 50)
            };
            
            for (int i = 0; i < platformPositions.Length; i++)
            {
                GameObject platform = Instantiate(platformPrefab, platformPositions[i], Quaternion.identity);
                platform.transform.localScale = new Vector3(platformSizes[i].x, platformSizes[i].y, 1f);
            }
        }
        
        // Create Coins
        if (coinPrefab != null)
        {
            Vector2[] coinPositions = new Vector2[]
            {
                new Vector2(-1f, 0.5f),     // (300, 450)
                new Vector2(1f, 1f),         // (500, 400)
                new Vector2(-1.5f, 2f),     // (250, 300)
                new Vector2(0.5f, 2.5f),    // (450, 250)
                new Vector2(-2.5f, 3.5f),    // (150, 150)
                new Vector2(1.5f, 4.5f)      // (550, 50)
            };
            
            foreach (Vector2 pos in coinPositions)
            {
                Instantiate(coinPrefab, pos, Quaternion.identity);
            }
        }
        
        // Create Goal (canvas: x=720, y=10)
        if (goalPrefab != null)
        {
            Vector3 goalPos = new Vector3(3.2f, 4.9f, 0f);
            Instantiate(goalPrefab, goalPos, Quaternion.identity);
        }
    }
}

