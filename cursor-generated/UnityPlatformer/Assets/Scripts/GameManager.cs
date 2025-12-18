using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class GameManager : MonoBehaviour
{
    public static GameManager Instance;
    
    [Header("UI References")]
    public TextMeshProUGUI scoreText;
    public TextMeshProUGUI livesText;
    public GameObject gameOverPanel;
    public TextMeshProUGUI gameOverText;
    public Button restartButton;
    
    private int score = 0;
    private int lives = 3;
    private bool gameRunning = true;
    private PlayerController player;
    private Coin[] coins;
    
    void Awake()
    {
        if (Instance == null)
        {
            Instance = this;
        }
        else
        {
            Destroy(gameObject);
            return;
        }
    }
    
    void Start()
    {
        player = FindObjectOfType<PlayerController>();
        coins = FindObjectsOfType<Coin>();
        
        if (gameOverPanel != null)
        {
            gameOverPanel.SetActive(false);
        }
        
        if (restartButton != null)
        {
            restartButton.onClick.AddListener(RestartGame);
        }
        
        UpdateUI();
    }
    
    public void AddScore(int points)
    {
        score += points;
        UpdateUI();
    }
    
    public void PlayerFell()
    {
        lives--;
        UpdateUI();
        
        if (lives <= 0)
        {
            EndGame(false);
        }
    }
    
    public void PlayerReachedGoal()
    {
        EndGame(true);
    }
    
    void EndGame(bool won)
    {
        gameRunning = false;
        
        if (gameOverPanel != null)
        {
            gameOverPanel.SetActive(true);
            
            if (gameOverText != null)
            {
                if (won)
                {
                    gameOverText.text = $"You Win! Score: {score}";
                    gameOverText.color = new Color(0.32f, 0.81f, 0.40f); // #51CF66
                }
                else
                {
                    gameOverText.text = "Game Over!";
                    gameOverText.color = new Color(1f, 0.42f, 0.42f); // #FF6B6B
                }
            }
        }
    }
    
    void RestartGame()
    {
        score = 0;
        lives = 3;
        gameRunning = true;
        
        if (gameOverPanel != null)
        {
            gameOverPanel.SetActive(false);
        }
        
        // Reset all coins
        foreach (Coin coin in coins)
        {
            coin.ResetCoin();
        }
        
        // Reset player
        if (player != null)
        {
            player.ResetPosition();
        }
        
        UpdateUI();
    }
    
    void UpdateUI()
    {
        if (scoreText != null)
        {
            scoreText.text = $"Score: {score}";
        }
        
        if (livesText != null)
        {
            livesText.text = $"Lives: {lives}";
        }
    }
    
    public bool IsGameRunning()
    {
        return gameRunning;
    }
}

