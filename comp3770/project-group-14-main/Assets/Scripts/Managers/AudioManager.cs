using System.Runtime.Versioning;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AudioManager : MonoBehaviour
{
    private AudioSource[] audioList;
    public static AudioSource buttonClick, bgm, jump, fall, heal, complete, breakSound, backButton, pickupAmmo,
                              shoot, damage, takeFlag, captureFlag, magicShoot, spiritShoot, lasershoot;
    
    // Start is called before the first frame update
    void Start()
    {
        LoadAudio();
        bgm.loop = true;
        bgm.volume = 0.5f;
        bgm.Play();
    }

    // Prepare all audio to be used in the program
    void LoadAudio(){
        for(int i = 0; i < 16; i++){
            gameObject.AddComponent<AudioSource>();
        }

        audioList = gameObject.GetComponents<AudioSource>();
        audioList[0].clip = (AudioClip)Resources.Load("Audio/buttonClick");
        audioList[1].clip = (AudioClip)Resources.Load("Audio/track_shortadventure_loop");
        audioList[2].clip = (AudioClip)Resources.Load("Audio/jump");
        audioList[3].clip = (AudioClip)Resources.Load("Audio/fall");
        audioList[4].clip = (AudioClip)Resources.Load("Audio/heal");
        audioList[5].clip = (AudioClip)Resources.Load("Audio/level-completed");
        audioList[6].clip = (AudioClip)Resources.Load("Audio/break");
        audioList[7].clip = (AudioClip)Resources.Load("Audio/backButtonClick");
        audioList[8].clip = (AudioClip)Resources.Load("Audio/pickupAmmo");
        audioList[9].clip = (AudioClip)Resources.Load("Audio/shoot1");
        audioList[10].clip = (AudioClip)Resources.Load("Audio/damage");
        audioList[11].clip = (AudioClip)Resources.Load("Audio/flagTaken");
        audioList[12].clip = (AudioClip)Resources.Load("Audio/capture");
        audioList[13].clip = (AudioClip)Resources.Load("Audio/magicShoot");
        audioList[14].clip = (AudioClip)Resources.Load("Audio/spiritShoot");
        audioList[15].clip = (AudioClip)Resources.Load("Audio/lasershoot");
        
        for(int i = 0; i < audioList.Length; i++){
            gameObject.GetComponents<AudioSource>()[i] = audioList[i];
        }

        buttonClick = gameObject.GetComponents<AudioSource>()[0];
        bgm = gameObject.GetComponents<AudioSource>()[1];
        jump = gameObject.GetComponents<AudioSource>()[2];
        fall = gameObject.GetComponents<AudioSource>()[3];
        heal = gameObject.GetComponents<AudioSource>()[4];
        complete = gameObject.GetComponents<AudioSource>()[5];
        breakSound = gameObject.GetComponents<AudioSource>()[6];
        backButton = gameObject.GetComponents<AudioSource>()[7];
        pickupAmmo = gameObject.GetComponents<AudioSource>()[8];
        shoot = gameObject.GetComponents<AudioSource>()[9];
        damage = gameObject.GetComponents<AudioSource>()[10];
        takeFlag = gameObject.GetComponents<AudioSource>()[11];
        captureFlag = gameObject.GetComponents<AudioSource>()[12];
        magicShoot = gameObject.GetComponents<AudioSource>()[13];
        spiritShoot = gameObject.GetComponents<AudioSource>()[14];
        lasershoot = gameObject.GetComponents<AudioSource>()[15];

        // Any required adjustments to audio (volume, tone, etc.)
        jump.volume = 0.5f;
        buttonClick.volume = 0.5f;
        backButton.volume = 0.5f;
    }
}
