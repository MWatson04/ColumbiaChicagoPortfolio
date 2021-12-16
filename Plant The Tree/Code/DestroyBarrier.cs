using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DestroyBarrier : MonoBehaviour
{
    WinCondition winConditionScript;
    GameObject coinBarrier;

    void Awake()
    {
        // Init WinCondition script
        winConditionScript = GameObject.Find("Win Chest").GetComponent<WinCondition>();
    }

    // Start is called before the first frame update
    void Start()
    {
        // Init Coin Barrier object
        coinBarrier = GameObject.Find("Coin Barrier");
    }

    // Update is called once per frame
    void Update()
    {
        CheckIfCollectedEnoughCoins();
    }
    
    // Check if player collected enough coins to remove coinBarrier
    void CheckIfCollectedEnoughCoins()
    {
        if (winConditionScript.coinsCollected == winConditionScript.coinsInLevel.Length)
            coinBarrier.SetActive(false);
    }
}
