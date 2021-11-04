using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ProjectileController : MonoBehaviour
{
    // Projectile speed to set in Unity editor
    [SerializeField] float projectileSpeed;
    
    // Reference to game object
    GameObject player;
    // Distances to destroy projectile if it's out of the camera view
    float destroyDistanceLeft = -8;
    float destroyDistanceRight = 18;
    float destroyDistanceUp = 10;
    float destroyDistanceDown = -10;

    // Start is called before the first frame update
    void Start()
    {
        // Initialize game object variable with player object
        player = GameObject.Find("Player");
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        /*
            NOTE: This object is instantiated in the "Spawn Manager" script
            and is instantiated based on the player objects position, so 
            if the player is facing right, the projectile will move right, and
            if the player is facing left, the projectile will move left
        */ 
        
        // Move projectile object and check if it needs to be destroyed
        transform.Translate(Vector3.right * projectileSpeed * Time.fixedDeltaTime);
        
        CheckForOutOfBoundsToDestroy();
    }

    // Check to destroy projectile object by seeing if it's out of screen view
    void CheckForOutOfBoundsToDestroy()
    {
        var distanceFromProjectileToPlayerOnX = transform.position.x - player.transform.position.x;
        var distanceFromProjectileToPlayerOnY = transform.position.y - player.transform.position.y;

        if (distanceFromProjectileToPlayerOnX >= destroyDistanceRight
            || distanceFromProjectileToPlayerOnX <= destroyDistanceLeft)
        {
            Destroy(gameObject);
        }
        else if (distanceFromProjectileToPlayerOnY >= destroyDistanceUp
                 || distanceFromProjectileToPlayerOnY < destroyDistanceDown)
        {
            Destroy(gameObject);
        }
    }

    // If projectile object collides with "Mace" or "Saw" object then destroy the other objects and/or itself
    void OnTriggerEnter2D(Collider2D other)
    {
        if (other.gameObject.CompareTag("MaceEnemy"))
        {
            Destroy(gameObject);
            Destroy(other.gameObject);
        }
        else if (other.gameObject.CompareTag("SawEnemy"))
        {
            Destroy(gameObject);
        }
    }

    // If projectile object hits an object tagged ground then destroy it 
    void OnCollisionEnter2D(Collision2D other)
    {
        if (other.gameObject.CompareTag("Ground"))
        {
            Destroy(gameObject);
        }
    }
}
