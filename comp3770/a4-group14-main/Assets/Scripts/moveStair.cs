using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class moveStair : MonoBehaviour
{
    public int start = 1;
    Vector3 offset = new Vector3();
    void Start(){
        offset = transform.position;
    }
    void Update()
    {
        if(transform.position.y == offset.y){
            start = 1;
        }else if(transform.position.y == (offset.y + 2)){
            start = 0;
        }
        if(start == 0)
        transform.position = Vector3.MoveTowards(transform.position,offset,2.0f*Time.deltaTime);
        else
        transform.position = Vector3.MoveTowards(transform.position,new Vector3(offset.x,offset.y + 2,offset.z),2.0f*Time.deltaTime);
    }
}
