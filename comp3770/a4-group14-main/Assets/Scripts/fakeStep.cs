using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class fakeStep : MonoBehaviour
{
    void OnTriggerEnter(Collider other)
    {
        AudioManager.breakSound.Play();
        Destroy(gameObject);
    }
}