using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WinCondition : MonoBehaviour
{
    // Variables for 3 game objects and the speed of a tree object that are defined in the Unity editor
    [SerializeField] GameObject player;
    [SerializeField] GameObject winTree;
    [SerializeField] GameObject endGameBarrier;
    [SerializeField] float treeSpeed;

    // Array of game objects that are coins
    public GameObject[] coinsInLevel;
    // Variables to check amount of coins collected and if the game has been beaten
    public int coinsCollected;
    public bool hasWonGame;
    
    // Update is called once per frame
    void FixedUpdate()
    {
        WinTreeMovement();
        SpawnEndGameBarrier();
    }

    // If the object this script is attached to, touches the player then the player wins
    void OnTriggerEnter2D(Collider2D other)
    {
        if (other.gameObject == player)
        {
            hasWonGame = true;
        }
    }

    // Method to move the tree and make it stop after winning the game
    void WinTreeMovement()
    {
        if (hasWonGame && winTree.transform.position.y < -4.073f)
        {
            winTree.transform.Translate(Vector3.up * treeSpeed * Time.deltaTime);
        }
        else if (hasWonGame && winTree.transform.position.y > -4.05f)
        {
            winTree.transform.Translate(Vector3.zero);
        }
    }

    // Barrier made active to lock player into the "win area"
    void SpawnEndGameBarrier()
    {
        if (hasWonGame)
        {
            endGameBarrier.SetActive(true);
        }
    }
}
