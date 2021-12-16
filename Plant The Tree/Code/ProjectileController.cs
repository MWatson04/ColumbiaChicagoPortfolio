using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ProjectileController : MonoBehaviour
{
    [SerializeField] float projectileSpeed;
    
    GameObject player;
    
    float destroyDistanceLeft = -8;
    float destroyDistanceRight = 18;
    float destroyDistanceUp = 10;
    float destroyDistanceDown = -10;

    // Start is called before the first frame update
    void Start()
    {
        // Init player game object
        player = GameObject.Find("Player");
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        // Move projectile 
        transform.Translate(Vector3.right * projectileSpeed * Time.fixedDeltaTime);
        
        CheckForOutOfBoundsToDestroy();
    }

    // Check to destroy projectile if it's out of screen view
    void CheckForOutOfBoundsToDestroy()
    {
        var _distanceFromProjectileToPlayerOnX = transform.position.x - player.transform.position.x;
        var _distanceFromProjectileToPlayerOnY = transform.position.y - player.transform.position.y;

        if (_distanceFromProjectileToPlayerOnX >= destroyDistanceRight
            || _distanceFromProjectileToPlayerOnX <= destroyDistanceLeft)
        {
            Destroy(gameObject);
        }
        else if (_distanceFromProjectileToPlayerOnY >= destroyDistanceUp
                 || _distanceFromProjectileToPlayerOnY < destroyDistanceDown)
        {
            Destroy(gameObject);
        }
    }

    // Check for projectile collision with enemies
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

    // Check for projectile collision with the ground
    void OnCollisionEnter2D(Collision2D other)
    {
        if (other.gameObject.CompareTag("Ground"))
        {
            Destroy(gameObject);
        }
    }
}
