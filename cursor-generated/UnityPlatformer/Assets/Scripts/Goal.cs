using UnityEngine;

public class Goal : MonoBehaviour
{
    void Start()
    {
        // Ensure it has a trigger collider
        Collider2D collider = GetComponent<Collider2D>();
        if (collider == null)
        {
            BoxCollider2D boxCollider = gameObject.AddComponent<BoxCollider2D>();
            boxCollider.isTrigger = true;
        }
        else
        {
            collider.isTrigger = true;
        }
        
        // Set color to green
        SpriteRenderer spriteRenderer = GetComponent<SpriteRenderer>();
        if (spriteRenderer != null)
        {
            spriteRenderer.color = new Color(0.32f, 0.81f, 0.40f); // #51CF66
        }
    }
}

