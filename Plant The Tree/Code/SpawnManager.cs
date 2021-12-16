using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpawnManager : MonoBehaviour
{
    [SerializeField] GameObject playerProjectile;
    [SerializeField] GameObject player;

    // Update is called once per frame
    void Update()
    {
        ShootProjectile();
    }

    // Instantiate projectile object if player shoots
    void ShootProjectile()
    {
        var mainShootProjectileInput = Input.GetButtonDown("Fire1");

        if (mainShootProjectileInput)
            Instantiate(playerProjectile, player.transform.position, player.transform.rotation);
    }
}
