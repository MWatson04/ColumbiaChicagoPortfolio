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
    [SerializeField] float enemySpeed;
    [SerializeField] float topPoint;
    [SerializeField] float bottomPoint;
        
    Vector2 pointA;
    Vector2 pointB;
    Vector3 enemyOnePosition;
        
    // Start is called before the first frame update
    void Start()
    {
        // Init enemy pos
        enemyOnePosition = transform.position;
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        RepeatUpAndDownMovement();
    }

    // Move object up and down
    void RepeatUpAndDownMovement()
    {
        // Store the objects starting pos and where it'll move to
        pointA = new Vector2(enemyOnePosition.x, topPoint);
        pointB = new Vector2(enemyOnePosition.x, bottomPoint);
        // Determine the time it will take the enemy to move
        var movementTime = Mathf.PingPong(Time.time * enemySpeed, 1);
        
        // Move object by calculating the distance it'll travel and the time it'll take
        transform.position = (Vector3.Lerp(pointA, pointB, movementTime));
    }
}
