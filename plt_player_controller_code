using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    // Made to set player object speed and jump force in Unity editor
    [SerializeField] float playerSpeed;
    [SerializeField] float playerJumpForce;

    // Reference to player objects Rigidbody
    Rigidbody2D playerRigidbody;
    bool isGrounded;
    float fallToDeathDistance = -14.5f;
    int playerHealth;
    
    public bool gameOver;

    // Initializes variable, playerRigidbody, upon script being loaded
    void Awake()
    {
        playerRigidbody = GetComponent<Rigidbody2D>();
    }

    // Start is called before the first frame update
    void Start()
    {
        // Initializing player object health variable
        playerHealth = 2;
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        // Call methods that control player object
        CheckToRotatePlayer();
        PlayerRunInput();
        PlayerJumpInput();
        CheckIfPlayerFellToDeath();
    }

    // Make player object move left and right based on input
    void PlayerRunInput()
    {
        // Variables for moving player object and for checking which direction the player object is moving
        var horizontalInput = Input.GetAxis("Horizontal");
        var inputForCheckingMoveRight = Input.GetKey(KeyCode.D);
        var inputForCheckingMoveLeft = Input.GetKey(KeyCode.A);
        
        // Change direction player object is moving based on which input variable is true
        if (inputForCheckingMoveRight)
        {
            transform.Translate(Vector3.right.normalized * horizontalInput * playerSpeed * Time.fixedDeltaTime);
        }
        else if (inputForCheckingMoveLeft)
        {
            transform.Translate(Vector3.left.normalized * horizontalInput * playerSpeed * Time.fixedDeltaTime);
        }
    }

    // Make player object jump using input and set isGrounded variable to false
    void PlayerJumpInput()
    {
        var mainJumpInput = Input.GetKey(KeyCode.Space);
        var alternateJumpInput = Input.GetKey(KeyCode.W);
        
        if (mainJumpInput && isGrounded || alternateJumpInput && isGrounded)
        {
            playerRigidbody.AddForce(Vector2.up.normalized * playerJumpForce, ForceMode2D.Impulse);
            // Set upon the object jumping to avoid object being able to jump an infinite amount of times
            isGrounded = false;
        }
    }
    
    // If player object is touching the ground then isGrounded is set to true
    void OnCollisionEnter2D(Collision2D other)
    {
        if (other.gameObject.CompareTag("Ground")) 
        {
            isGrounded = true;
        }
    }

    // Decrease object health and kill object upon colliding with a "Mace" or "Saw" object
    void OnTriggerEnter2D(Collider2D other)
    {
        // Decrease player object health and make it smaller
        if (other.gameObject.CompareTag("MaceEnemy") && playerHealth == 2)
        {
            playerHealth -= 1;
            transform.localScale *= 0.67f;
        } 
        // Kill object by destroying it and end game
        else if (other.gameObject.CompareTag("MaceEnemy") && playerHealth == 1)
        {
            Destroy(gameObject);
            gameOver = true;
        }
        
        // Decrease object health and make it smaller
        if (other.gameObject.CompareTag("SawEnemy") && playerHealth == 2)
        {
            playerHealth -= 1;
            transform.localScale *= 0.67f;
        }
        // Kill object by destroying it and end game
        else if (other.gameObject.CompareTag("SawEnemy") && playerHealth == 1)
        {
            Destroy(gameObject);
            gameOver = true;
        }
    }

    // If player objects y position is below a certain distance then destroy it and end game
    void CheckIfPlayerFellToDeath()
    {
        if (transform.position.y < fallToDeathDistance)
        {
            Destroy(gameObject);
            gameOver = true;
        }
    }

    // Change direction player object is facing based on key input
    void CheckToRotatePlayer()
    {
        if (Input.GetKey(KeyCode.A))
        {
            transform.rotation = Quaternion.Euler(0, 180, 0);
        }
        else if (Input.GetKey(KeyCode.D))
        {
            transform.rotation = Quaternion.Euler(0, 0, 0);
        }
    }
}
