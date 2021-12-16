using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CoinCollection : MonoBehaviour
{
    GameObject player;
    WinCondition winConditionScript;

    void Awake()
    {
        // Init WinCondition script
        winConditionScript = GameObject.Find("Win Chest").GetComponent<WinCondition>();
    }

    // Start is called before the first frame update
    void Start()
    {
        // Init player object
        player = GameObject.Find("Player");
    }

    // Destroy coin on collision with player and add to coinsCollected
    void OnCollisionEnter2D(Collision2D other)
    {
        if (other.gameObject == player)
        {
            winConditionScript.coinsCollected += 1;
            Destroy(gameObject);
        }
    }
}
