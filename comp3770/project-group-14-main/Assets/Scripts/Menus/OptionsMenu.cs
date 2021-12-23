using System;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;
using TMPro;

public class OptionsMenu : MainMenu{
    // Muting based off from: https://www.youtube.com/watch?v=J-igitoipYY
    // Volume slider based off from: https://www.youtube.com/watch?v=yWCHaTwVblk
    // NOTE: resolution and window settings are not visible unless a build version is ran

    [SerializeField]
    private TextMeshProUGUI muteDescription, windowDescription, res1, res2, res3;
    [SerializeField] 
    private Slider volumeSlider;
    private bool isMuted, isFullScreen;

    void Start(){
        isMuted = PlayerPrefs.GetInt("IsMuted") == 1;
        isFullScreen = PlayerPrefs.GetInt("IsFullScreen") == 1;
        CheckMuteText();
        CheckWindowText();
        CheckResolutionText();
        AudioListener.pause = isMuted;

        if(!PlayerPrefs.HasKey("Volume")){
            PlayerPrefs.SetFloat("Volume", 1);
            Load();
        }
        else{
            Load();
        }
    }

    // Muting functions
    public void Mute(){
        isMuted = !isMuted;
        AudioListener.pause = isMuted;
        PlayerPrefs.SetInt("IsMuted", isMuted ? 1 : 0);
        CheckMuteText();
    }

    private void CheckMuteText(){
        if(isMuted){
            muteDescription.text = "Audio is muted";
        }
        else{
            muteDescription.text = "Audio is not muted";
        }
    }

    // Volume functions
    public void ChangeVolume(){
        AudioListener.volume = volumeSlider.value;
        Save();
    }

    private void Load(){
        volumeSlider.value = PlayerPrefs.GetFloat("Volume");
    }

    private void Save(){
        PlayerPrefs.SetFloat("Volume", volumeSlider.value);        
    }

    // Window functions
    public void ChangeWindowMode(){
        #if UNITY_EDITOR
            Debug.Log("This setting is only visible in build versions");
        #endif
        isFullScreen = !isFullScreen;
        AudioManager.buttonClick.Play();
        if(PlayerPrefs.GetInt("Resolution") == 2){
            Screen.SetResolution(640, 480, isFullScreen);
        }
        else if(PlayerPrefs.GetInt("Resolution") == 1){
            Screen.SetResolution(1080, 960, isFullScreen);
        }
        else{
            Screen.SetResolution(1920, 1080, isFullScreen);
        }

        PlayerPrefs.SetInt("IsFullScreen", isFullScreen ? 1 : 0);
        CheckWindowText();
    }

    public void ChangeResolutionLow(){
        #if UNITY_EDITOR
            Debug.Log("This setting is only visible in build versions");
        #endif
        AudioManager.buttonClick.Play();
        Screen.SetResolution(640, 480, PlayerPrefs.GetInt("IsFullScreen") == 1);
        PlayerPrefs.SetInt("Resolution", 2);
        CheckResolutionText();
    }

    public void ChangeResolutionMed(){
        #if UNITY_EDITOR
            Debug.Log("This setting is only visible in build versions");
        #endif
        AudioManager.buttonClick.Play();
        Screen.SetResolution(1080, 960, PlayerPrefs.GetInt("IsFullScreen") == 1);
        PlayerPrefs.SetInt("Resolution", 1);
        CheckResolutionText();
    }

    public void ChangeResolutionHigh(){
        #if UNITY_EDITOR
            Debug.Log("This setting is only visible in build versions");
        #endif
        AudioManager.buttonClick.Play();
        Screen.SetResolution(1920, 1080, PlayerPrefs.GetInt("IsFullScreen") == 1);
        PlayerPrefs.SetInt("Resolution", 0);
        CheckResolutionText();
    }

    private void CheckResolutionText(){
        if(PlayerPrefs.GetInt("Resolution") == 2){
            res1.text = "Selected";
            res2.text = string.Empty;
            res3.text = res2.text;
        }
        else if(PlayerPrefs.GetInt("Resolution") == 1){
            res2.text = "Selected";
            res1.text = string.Empty;
            res3.text = res1.text;
        }
        else{
            res3.text = "Selected";
            res1.text = string.Empty;
            res2.text = res1.text;
        }
    }

    private void CheckWindowText(){
        if(isFullScreen){
            windowDescription.text = "Fullscreen";
        }
        else{
            windowDescription.text = "Windowed";
        }
    }
}