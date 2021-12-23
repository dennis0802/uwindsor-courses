using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class MainMenu : MonoBehaviour{
    // Based off of: https://www.youtube.com/watch?v=zc8ac_qUXQY
    // Each menu option
    // NOTE: According to build index settings on the project
    // 0 = splash screen
    // 1 = menu
    // 2 = instructions
    // 3 = options
    // 4 = lobby

    [SerializeField] private NetworkManagerLobby networkManager = null;
    [Header("UI")][SerializeField] private GameObject landingPagePanel = null;

    // Based off of: https://www.youtube.com/watch?v=Fx8efi2MNz0
    public void HostLobby(){
        AudioManager.buttonClick.Play();
        if(NetworkManagerLobby.instance == null){
            NetworkManagerLobby.instance = networkManager;
        }
        NetworkManagerLobby.instance.StartHost();
        landingPagePanel.SetActive(false);
    }

    public void LeaveLobby(){
        AudioManager.backButton.Play();
        SceneManager.LoadScene(1);
        NetworkManagerLobby.Shutdown();
    }

    // Placeholder function to play audio on the lobby functions/instruction page
    public void ButtonSound(){
        AudioManager.buttonClick.Play();
    }

    public void StopBgm(){
        AudioManager.bgm.Stop();
    }

    // Typical menu functions
    public void Play(){
        AudioManager.buttonClick.Play();
        SceneManager.LoadScene(4);
    }
    public void Controls(){
        AudioManager.buttonClick.Play();
        SceneManager.LoadScene(2);
    }

    public void Options(){
        AudioManager.buttonClick.Play();
        SceneManager.LoadScene(3);
    }

    public void ReturnToMenu(){
        AudioManager.backButton.Play();
        SceneManager.LoadScene(1);       
    }

    public void Quit(){
        AudioManager.buttonClick.Play();
        #if UNITY_EDITOR
            UnityEditor.EditorApplication.isPlaying = false;
        #else
            UnityEngine.Application.Quit();
        #endif
    }

    private void Update(){
        if(!AudioManager.bgm.isPlaying){
            AudioManager.bgm.Play();
            AudioManager.bgm.loop = true;
        }
    }
}
