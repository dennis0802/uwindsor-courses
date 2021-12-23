using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class rotateStair : MonoBehaviour
{
    void Update()
    {
        transform.Rotate(Vector3.right,0.05f,Space.World);
    }
}
