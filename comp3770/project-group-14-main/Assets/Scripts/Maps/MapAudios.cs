using System.Collections;
using System.Collections.Generic;
using Mirror;
using UnityEngine;
using UnityEngine.SceneManagement;

public class MapAudios : MonoBehaviour
{
    // Update is called once per frame
    void Update()
    {
        // Stop bgm audio from playing on the maps
        if(AudioManager.bgm.isPlaying){
            AudioManager.bgm.Stop();
        }
    }
}
