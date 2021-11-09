using System;
using System.Collections;
using System.Collections.Generic;
using System.Numerics;
using Unity.Mathematics;
using UnityEngine;
using Vector2 = UnityEngine.Vector2;
using Vector3 = UnityEngine.Vector3;

public class EnemyOneMovement : MonoBehaviour
{
    // Serialized variables to set speed and distance this object will move
    [SerializeField] float enemySpeed;
    [SerializeField] float topPoint;
    [SerializeField] float bottomPoint;
        
    // Setting distance this object will move as vector variables
    Vector2 pointA;
    Vector2 pointB;
    Vector3 enemyOnePosition;
        
    // Start is called before the first frame update
    void Start()
    {
        // Initializing enemyOnePosition variable with its own position
        enemyOnePosition = transform.position;
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        // Call method to constantly move this object
        RepeatUpAndDownMovement();
    }

    // Move object up and down using the position variables made above
    void RepeatUpAndDownMovement()
    {
        // Store the object position and where it'll move to in two vector variables
        pointA = new Vector2(enemyOnePosition.x, topPoint);
        pointB = new Vector2(enemyOnePosition.x, bottomPoint);
        // This variable is made to determine the time it'll take the object to move
        // in relation to its speed (enemySpeed) using a length of 1 (repeating value of 0 to 1)
        var movementTime = Mathf.PingPong(Time.time * enemySpeed, 1);
        
        // Move the object from point A to Point B at the speed/time defined in the movementTime variable
        // This only works if the length of time is repeating between 0 and 1 which
        // is why the length in the movementTime variable is set to 1
        transform.position = (Vector3.Lerp(pointA, pointB, movementTime));
    }
}
