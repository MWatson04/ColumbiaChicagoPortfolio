using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DestroyBarrier : MonoBehaviour
{
    // Reference to script and game object
    WinCondition winConditionScript;
    GameObject coinBarrier;
    
    // Start is called before the first frame update
    void Start()
    {
        // Initializing script and game object variables
        winConditionScript = GameObject.Find("Win Chest").GetComponent<WinCondition>();
        coinBarrier = GameObject.Find("Coin Barrier");
    }

    // Update is called once per frame
    void Update()
    {
        // Call method for checking collected coins and modifying a game object
        CheckIfCollectedEnoughCoins();
    }
    
    // Check if player collected enough coins and removing a game object if true
    void CheckIfCollectedEnoughCoins()
    {
        if (winConditionScript.coinsCollected == winConditionScript.coinsInLevel.Length)
        {
            coinBarrier.SetActive(false);
        }
    }
}
