using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// Originally written by Jim Lin for A4
public class RotatePickup : MonoBehaviour
{
    [SerializeField]
    private int rotateSpeed;

    void Start()
    {
        rotateSpeed = 1;    
    }
    void Update()
    {
        transform.Rotate(0, rotateSpeed, 0, Space.World);    
    }
}
