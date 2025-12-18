using UnityEngine;

public class Coin : MonoBehaviour
{
    private bool collected = false;
    private SpriteRenderer spriteRenderer;
    private CircleCollider2D collider;
    
    void Start()
    {
        spriteRenderer = GetComponent<SpriteRenderer>();
        collider = GetComponent<CircleCollider2D>();
        
        if (collider == null)
        {
            collider = gameObject.AddComponent<CircleCollider2D>();
            collider.isTrigger = true;
        }
        
        // Set color to gold
        if (spriteRenderer != null)
        {
            spriteRenderer.color = new Color(1f, 0.84f, 0f); // #FFD700
        }
    }
    
    void Update()
    {
        if (!collected)
        {
            // Rotate coin for visual effect
            transform.Rotate(0, 0, 90 * Time.deltaTime);
        }
    }
    
    public void Collect()
    {
        if (collected) return;
        
        collected = true;
        
        if (spriteRenderer != null)
        {
            spriteRenderer.enabled = false;
        }
        
        if (collider != null)
        {
            collider.enabled = false;
        }
        
        GameManager.Instance.AddScore(10);
    }
    
    public void ResetCoin()
    {
        collected = false;
        
        if (spriteRenderer != null)
        {
            spriteRenderer.enabled = true;
        }
        
        if (collider != null)
        {
            collider.enabled = true;
        }
    }
}

