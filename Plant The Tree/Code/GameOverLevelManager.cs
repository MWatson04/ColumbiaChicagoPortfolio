using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GameOverLevelManager : MonoBehaviour
{
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
            SceneManager.LoadScene("Level 1", LoadSceneMode.Single);
        else if (exitApplication)
            Application.Quit();
    }

    // Check if quitting or restarting using player input
    void CheckIfQuittingOrRestarting()
    {
        var _returnToGame = Input.GetKey(KeyCode.Space);
        var _quitGame = Input.GetKey(KeyCode.Return);

        if (_returnToGame)
            loadLevelOne = true;
        else if (_quitGame)
            exitApplication = true;
    }
}
