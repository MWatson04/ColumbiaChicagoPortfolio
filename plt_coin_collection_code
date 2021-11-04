using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CoinCollection : MonoBehaviour
{
    // Reference to script and game object
    GameObject player;
    WinCondition winConditionScript;
    
    // Start is called before the first frame update
    void Start()
    {
        // Initialize object and script variables
        player = GameObject.Find("Player");
        winConditionScript = GameObject.Find("Win Chest").GetComponent<WinCondition>();
    }

    // Destroy coin on collision with player and add 1 to total coins collected
    void OnCollisionEnter2D(Collision2D other)
    {
        if (other.gameObject == player)
        {
            winConditionScript.coinsCollected += 1;
            Destroy(gameObject);
        }
    }
}
