using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class magicStair : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        Invoke("Show",3f);
    }
    void Show(){
        transform.gameObject.SetActive(true);
        Invoke("Hide",3f);
    }
    void Hide(){
        transform.gameObject.SetActive(false);
        Invoke("Show",3f);
    }
}
