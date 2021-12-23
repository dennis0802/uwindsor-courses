using TMPro;
using UnityEngine;
using UnityEngine.UI;

// Based off of: https://www.youtube.com/watch?v=Fx8efi2MNz0
public class JoinLobbyMenu : MonoBehaviour {
    [SerializeField] private NetworkManagerLobby networkManager = null;
    [Header("UI")]
    [SerializeField] private GameObject landingPagePanel = null;
    [SerializeField] private TMP_InputField ipAddressInputField = null;
    [SerializeField] private Button joinButton = null;

    private void OnEnable(){
        NetworkManagerLobby.OnClientConnected += HandleClientConnected;
        NetworkManagerLobby.OnClientDisconnected += HandleClientDisconnected;
    }

    private void OnDisable(){
        NetworkManagerLobby.OnClientConnected -= HandleClientConnected;
        NetworkManagerLobby.OnClientDisconnected -= HandleClientDisconnected;       
    }

    // Joining by ip
    public void JoinLobby(){
        string ipAddress = ipAddressInputField.text;
        if(networkManager == null){
            networkManager = NetworkManagerLobby.instance;
        }

        networkManager.networkAddress = ipAddress;
        networkManager.StartClient();

        AudioManager.buttonClick.Play();
        joinButton.interactable = false;
    }

    private void HandleClientConnected(){
        joinButton.interactable = true;

        gameObject.SetActive(false);
        landingPagePanel.SetActive(false);
    }

    private void HandleClientDisconnected(){
        joinButton.interactable = true;
    }
}