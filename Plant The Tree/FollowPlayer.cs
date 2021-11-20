using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FollowPlayer : MonoBehaviour
{
    // Reference to game object and initialized in Unity editor
    [SerializeField] GameObject player;
    
    // Vector variable made to offset the camera on the player objects position
    Vector3 offset = new Vector3(6, 0.23f, -10);

    // Called every frame if contents are being used
    void LateUpdate()
    {
        // Make camera follow player with an offset on the cameras position
        transform.position = new Vector3(player.transform.position.x + offset.x, offset.y, offset.z);
    }
}
