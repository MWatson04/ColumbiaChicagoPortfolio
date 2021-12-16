using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class LevelManager : MonoBehaviour
{
    PlayerController playerControllerScript;
    WinCondition winConditionScript;
    
    bool loadLevelOne;
    bool exitApplication;

    void Awake()
    {
        // Init scripts
        playerControllerScript = GameObject.Find("Player").GetComponent<PlayerController>();
        winConditionScript = GameObject.Find("Win Chest").GetComponent<WinCondition>();
    }

    // Update is called once per frame
    void Update()
    {
        StartCoroutine(ChangeToGameOverOrWinScene());
    }

    // Start a timer to wait for scene to change, then change scene depending on game state
    IEnumerator ChangeToGameOverOrWinScene()
    {
        if (playerControllerScript.gameOver)
        {
            yield return new WaitForSeconds(2.5f);
            SceneManager.LoadScene("Game Over", LoadSceneMode.Single);
        }
        else if (winConditionScript.hasWonGame)
        {
            yield return new WaitForSeconds(10f);
            SceneManager.LoadScene("Win", LoadSceneMode.Single);
        }
    }
}
