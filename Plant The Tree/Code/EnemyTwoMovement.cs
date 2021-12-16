using System;
using System.Collections;
using System.Collections.Generic;
using System.Numerics;
using Unity.Mathematics;
using UnityEngine;
using Vector2 = UnityEngine.Vector2;
using Vector3 = UnityEngine.Vector3;

public class EnemyTwoMovement : MonoBehaviour
{
    [SerializeField] float enemySpeed;
    [SerializeField] float rotationSpeed;
    [SerializeField] float leftPoint;
    [SerializeField] float rightPoint;

    Vector2 pointA;
    Vector2 pointB;
    Vector3 enemyTwoPosition;

    // Start is called before the first frame update
    void Start()
    {
        // Initializing enemy pos
        enemyTwoPosition = transform.position;
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        RepeatLeftAndRightMovement();
        
        // Rotate object to give spinning animation effect
        transform.Rotate(Vector3.forward * rotationSpeed * Time.deltaTime);
    }

    // Move object left and right
    void RepeatLeftAndRightMovement()
    {
        // Store the objects starting pos and where it'll move to
        pointA = new Vector2(leftPoint, enemyTwoPosition.y);
        pointB = new Vector2(rightPoint, enemyTwoPosition.y);
        // Determine the time it will take the enemy to move
        var movementTime = Mathf.PingPong(Time.time * enemySpeed, 1);
        
        // Move object by calculating the distance it'll travel and the time it'll take
        transform.position = (Vector3.Lerp(pointA, pointB, movementTime));
    }
}
