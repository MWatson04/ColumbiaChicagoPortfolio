using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FollowPlayer : MonoBehaviour
{
    [SerializeField] GameObject player;
    
    // Offset camera from player pos
    Vector3 offset = new Vector3(6, 0.23f, -10);

    // Called every frame as needed
    void LateUpdate()
    {
        // Camera follow player with offset
        transform.position = new Vector3(player.transform.position.x + offset.x, offset.y, offset.z);
    }
}
