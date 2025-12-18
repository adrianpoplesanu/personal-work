using UnityEngine;

public class PlayerController : MonoBehaviour
{
    [Header("Movement Settings")]
    public float speed = 5f;
    public float jumpPower = 15f;
    public float friction = 0.8f;
    public float gravity = 0.8f;
    public float terminalVelocity = 15f;
    
    private Rigidbody2D rb;
    private bool isGrounded = false;
    private Vector2 velocity;
    private float startX = -3.5f;
    private float startY = 2f;
    
    void Start()
    {
        rb = GetComponent<Rigidbody2D>();
        if (rb == null)
        {
            rb = gameObject.AddComponent<Rigidbody2D>();
        }
        
        // Set up physics
        rb.bodyType = RigidbodyType2D.Kinematic; // Use kinematic for manual movement
        rb.gravityScale = 0; // We'll handle gravity manually
        rb.freezeRotation = true;
        rb.collisionDetectionMode = CollisionDetectionMode2D.Continuous;
        
        // Set initial position (converted from canvas coordinates)
        // Canvas: x=50, y=100 -> Unity: approximately x=-3.5, y=2
        transform.position = new Vector3(startX, startY, 0);
    }
    
    void Update()
    {
        if (!GameManager.Instance.IsGameRunning()) return;
        
        HandleInput();
        ApplyGravity();
        ApplyMovement();
        CheckBoundaries();
        CheckFallOffScreen();
    }
    
    void HandleInput()
    {
        // Horizontal Movement
        float horizontal = 0f;
        if (Input.GetKey(KeyCode.A) || Input.GetKey(KeyCode.LeftArrow))
        {
            horizontal = -1f;
        }
        else if (Input.GetKey(KeyCode.D) || Input.GetKey(KeyCode.RightArrow))
        {
            horizontal = 1f;
        }
        
        if (horizontal != 0)
        {
            velocity.x = horizontal * speed;
        }
        else
        {
            velocity.x *= friction;
        }
        
        // Jumping
        if ((Input.GetKeyDown(KeyCode.Space) || Input.GetKeyDown(KeyCode.W) || Input.GetKeyDown(KeyCode.UpArrow)) && isGrounded)
        {
            velocity.y = jumpPower;
            isGrounded = false;
        }
    }
    
    void ApplyGravity()
    {
        velocity.y -= gravity;
        velocity.y = Mathf.Max(velocity.y, -terminalVelocity);
    }
    
    void ApplyMovement()
    {
        Vector2 movement = velocity * Time.deltaTime;
        Vector2 newPosition = (Vector2)transform.position + movement;
        rb.MovePosition(newPosition);
    }
    
    void CheckBoundaries()
    {
        // Screen boundaries (converted from 800px width, 600px height)
        // Unity camera view: approximately -4 to 4 horizontally, -3 to 3 vertically
        float leftBound = -4f;
        float rightBound = 4f;
        
        if (transform.position.x < leftBound)
        {
            transform.position = new Vector3(leftBound, transform.position.y, transform.position.z);
            velocity.x = 0;
        }
        if (transform.position.x > rightBound)
        {
            transform.position = new Vector3(rightBound, transform.position.y, transform.position.z);
            velocity.x = 0;
        }
    }
    
    void CheckFallOffScreen()
    {
        // If player falls below screen
        if (transform.position.y < -3.5f)
        {
            GameManager.Instance.PlayerFell();
            ResetPosition();
        }
    }
    
    void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.CompareTag("Platform"))
        {
            // Check if landing on top
            foreach (ContactPoint2D contact in collision.contacts)
            {
                if (contact.normal.y > 0.7f && velocity.y <= 0)
                {
                    isGrounded = true;
                    velocity.y = 0;
                    break;
                }
            }
        }
    }
    
    void OnCollisionStay2D(Collision2D collision)
    {
        if (collision.gameObject.CompareTag("Platform"))
        {
            // Check if on top of platform
            foreach (ContactPoint2D contact in collision.contacts)
            {
                if (contact.normal.y > 0.7f)
                {
                    isGrounded = true;
                    if (velocity.y < 0) velocity.y = 0;
                    break;
                }
            }
        }
    }
    
    void OnCollisionExit2D(Collision2D collision)
    {
        if (collision.gameObject.CompareTag("Platform"))
        {
            // Small delay before considering not grounded
            Invoke(nameof(CheckGrounded), 0.1f);
        }
    }
    
    void CheckGrounded()
    {
        // Raycast to check if still grounded
        RaycastHit2D hit = Physics2D.Raycast(transform.position, Vector2.down, 0.6f);
        if (hit.collider == null || !hit.collider.CompareTag("Platform"))
        {
            isGrounded = false;
        }
    }
    
    void OnTriggerEnter2D(Collider2D other)
    {
        if (other.CompareTag("Coin"))
        {
            other.GetComponent<Coin>().Collect();
        }
        else if (other.CompareTag("Goal"))
        {
            GameManager.Instance.PlayerReachedGoal();
        }
    }
    
    public void ResetPosition()
    {
        transform.position = new Vector3(startX, startY, 0);
        velocity = Vector2.zero;
        isGrounded = false;
    }
}

