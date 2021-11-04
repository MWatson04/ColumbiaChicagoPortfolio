using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class LevelManager : MonoBehaviour
{
    // Reference to two different scripts
    PlayerController playerControllerScript;
    WinCondition winConditionScript;
    // Booleans used later to check if level 1 is being loaded or if the game is being quit
    bool loadLevelOne;
    bool exitApplication;

    // Start is called before the first frame update
    void Start()
    {
        // Initializing the two script variables
        playerControllerScript = GameObject.Find("Player").GetComponent<PlayerController>();
        winConditionScript = GameObject.Find("Win Chest").GetComponent<WinCondition>();
    }

    // Update is called once per frame
    void Update()
    {
        // Call method with coroutine to use a timer
        StartCoroutine(ChangeToGameOverOrWinScene());
    }

    // Start a timer, then change scene depending on which variable is true
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
