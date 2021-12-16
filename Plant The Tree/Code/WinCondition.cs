using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WinCondition : MonoBehaviour
{
    public GameObject[] coinsInLevel;
    public int coinsCollected;
    public bool hasWonGame;
    
    [SerializeField] GameObject player;
    [SerializeField] GameObject winTree;
    [SerializeField] GameObject endGameBarrier;
    [SerializeField] float treeSpeed;
    
    // Update is called once per frame
    void FixedUpdate()
    {
        WinTreeMovement();
        SpawnEndGameBarrier();
    }

    // Check player collision with object that determines if player wins
    void OnTriggerEnter2D(Collider2D other)
    {
        if (other.gameObject == player)
        {
            hasWonGame = true;
        }
    }

    // Move tree after winning game
    void WinTreeMovement()
    {
        if (hasWonGame && winTree.transform.position.y < -4.073f)
            winTree.transform.Translate(Vector3.up * treeSpeed * Time.deltaTime);
        else if (hasWonGame && winTree.transform.position.y > -4.05f)
            winTree.transform.Translate(Vector3.zero);
    }

    // Activate barrier to lock player in win area
    void SpawnEndGameBarrier()
    {
        if (hasWonGame)
            endGameBarrier.SetActive(true);
    }
}
