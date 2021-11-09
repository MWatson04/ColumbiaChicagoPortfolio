using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class WinLevelManager : MonoBehaviour
{
    // Booleans used later to check if level 1 is being loaded or if the game is being quit
    bool loadLevelOne;
    bool exitApplication;
    
    // Update is called once per frame
    void Update()
    {
        CheckIfQuittingOrRestarting();
        QuitOrReturnToGame();
    }

    // Actually reload the game or quit it based on player input
    void QuitOrReturnToGame()
    {
        if (loadLevelOne)
        {
            SceneManager.LoadScene("Level 1", LoadSceneMode.Single);
        }
        else if (exitApplication)
        {
            Application.Quit();
        }
    }

    // Check if quitting or restarting using player input
    void CheckIfQuittingOrRestarting()
    {
        var returnToGame = Input.GetKey(KeyCode.Space);
        var quitGame = Input.GetKey(KeyCode.Return);

        if (returnToGame)
        {
            loadLevelOne = true;
        }
        else if (quitGame)
        {
            exitApplication = true;
        }
    }
}
