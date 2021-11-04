using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpawnManager : MonoBehaviour
{
    // Reference to 2 game objects that is initialized in the Unity editor
    [SerializeField] GameObject playerProjectile;
    [SerializeField] GameObject player;

    // Update is called once per frame
    void Update()
    {
        // Call method to shoot projectile object
        ShootProjectile();
    }

    // Check if input is being made and if it is, then create the projectile object
    void ShootProjectile()
    {
        var mainShootProjectileInput = Input.GetButtonDown("Fire1");

        if (mainShootProjectileInput)
        {
            Instantiate(playerProjectile, player.transform.position, player.transform.rotation);
        }
    }
}
