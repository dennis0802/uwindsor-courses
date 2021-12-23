using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SplashScreen : MonoBehaviour
{
    [SerializeField] private float countdown = 3.0f;

    // Check for volume preferences before starting
    void Awake(){
        CheckVolume();
    }

    // Update is called once per frame
    void Update(){
        // Delay showing the menu for countdown amount of time
        if(countdown > 0){
            countdown -= Time.deltaTime;
        }
        if(countdown < 0){
            SceneManager.LoadScene(1);
        }
    }

    // If impatient and don't want to wait for the countdown to finish,
    // user can click to go to menu
    public void LoadMenu(){
        AudioManager.buttonClick.Play();
        SceneManager.LoadScene(1);
    }

    // Check volume levels if returning to game after setting preferences in a previous run
    private void CheckVolume(){
        if(PlayerPrefs.HasKey("Volume")){
            AudioListener.volume = PlayerPrefs.GetFloat("Volume");
        }
        if(PlayerPrefs.HasKey("IsMuted")){
            bool isMuted = PlayerPrefs.GetInt("IsMuted") == 1;
            AudioListener.pause = isMuted;
        }
    }

    // Check resolution settings if returning to a game after setting in a previous run
    private void CheckResolution(){
        if(PlayerPrefs.HasKey("IsFullScreen") && PlayerPrefs.HasKey("Resolution")){
            if(PlayerPrefs.GetInt("Resolution") == 2){
                Screen.SetResolution(640, 480, PlayerPrefs.GetInt("IsFullScreen") == 1);
            }
            else if(PlayerPrefs.GetInt("Resolution") == 1){
                Screen.SetResolution(1080, 960, PlayerPrefs.GetInt("IsFullScreen") == 1);
            }
            else{
                Screen.SetResolution(1920, 1080, PlayerPrefs.GetInt("IsFullScreen") == 1);
            }
        }
    }
}
