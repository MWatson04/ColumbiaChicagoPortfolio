using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    public bool gameOver;
    
    [SerializeField] float playerSpeed;
    [SerializeField] float playerJumpForce;

    Rigidbody2D playerRigidbody;
    
    bool isGrounded;
    float fallToDeathDistance = -14.5f;
    int playerHealth;
    
    // Start is called before the first frame update
    void Start()
    {
        // Init variables
        playerRigidbody = GetComponent<Rigidbody2D>();
        playerHealth = 2;
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        PlayerRunInput();
        PlayerJumpInput();
        CheckToRotatePlayer();
        CheckIfPlayerFellToDeath();
    }

    // Make player move left and right based on input
    void PlayerRunInput()
    {
        // Movement input 
        var _horizontalInput = Input.GetAxis("Horizontal");
        var _inputForCheckingMoveRight = Input.GetKey(KeyCode.D);
        var _inputForCheckingMoveLeft = Input.GetKey(KeyCode.A);
        
        // Change direction player object is moving
        if (_inputForCheckingMoveRight)
            transform.Translate(Vector3.right.normalized * _horizontalInput * playerSpeed * Time.fixedDeltaTime);
        else if (_inputForCheckingMoveLeft)
            transform.Translate(Vector3.left.normalized * _horizontalInput * playerSpeed * Time.fixedDeltaTime);
    }

    // Set player jumping input
    void PlayerJumpInput()
    {
        // Input
        var _mainJumpInput = Input.GetKey(KeyCode.Space);
        var _alternateJumpInput = Input.GetKey(KeyCode.W);
        
        // Check if player is on the ground
        if (_mainJumpInput && isGrounded || _alternateJumpInput && isGrounded)
        {
            playerRigidbody.AddForce(Vector2.up.normalized * playerJumpForce, ForceMode2D.Impulse);
            isGrounded = false;
        }
    }
    
    // Check for collision between player and ground
    void OnCollisionEnter2D(Collision2D other)
    {
        if (other.gameObject.CompareTag("Ground")) 
            isGrounded = true;
    }

    // Check for collision between player and enemies
    void OnTriggerEnter2D(Collider2D other)
    {
        // Decrease player health and make size smaller
        if (other.gameObject.CompareTag("MaceEnemy") && playerHealth == 2 || 
            other.gameObject.CompareTag("SawEnemy") && playerHealth == 2)
        {
            playerHealth -= 1;
            transform.localScale *= 0.67f;
        } 
        // Kill player and end game
        else if (other.gameObject.CompareTag("MaceEnemy") && playerHealth == 1 ||
                 other.gameObject.CompareTag("SawEnemy") && playerHealth == 1)
        {
            Destroy(gameObject);
            gameOver = true;
        }
    }

    // Check if player has fallen to death
    void CheckIfPlayerFellToDeath()
    {
        if (transform.position.y < fallToDeathDistance)
        {
            Destroy(gameObject);
            gameOver = true;
        }
    }

    // "Rotate" player by flipping sprite in direction player is moving
    void CheckToRotatePlayer()
    {
        if (Input.GetKey(KeyCode.A))
            transform.rotation = Quaternion.Euler(0, 180, 0);  // Rotate left
        else if (Input.GetKey(KeyCode.D))
            transform.rotation = Quaternion.Euler(0, 0, 0);    // Rotate right
    }
}
