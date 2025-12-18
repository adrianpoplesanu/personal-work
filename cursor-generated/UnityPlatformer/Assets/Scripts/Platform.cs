using UnityEngine;

public class Platform : MonoBehaviour
{
    void Start()
    {
        // Ensure platform has a collider
        Collider2D collider = GetComponent<Collider2D>();
        if (collider == null)
        {
            BoxCollider2D boxCollider = gameObject.AddComponent<BoxCollider2D>();
        }
        
        // Set color to teal
        SpriteRenderer spriteRenderer = GetComponent<SpriteRenderer>();
        if (spriteRenderer != null)
        {
            spriteRenderer.color = new Color(0.31f, 0.80f, 0.77f); // #4ECDC4
        }
    }
}

