using Mirror;
using UnityEngine;
using UnityEngine.InputSystem;
using System;
using TMPro;

// Based off of: https://www.youtube.com/watch?v=p-2QFmCMBt8, minus showing who sent the message
public class ChatBehaviour : NetworkBehaviour{    
    [Header("Chat UI")]
    [SerializeField] private GameObject chatUI = null;
    [SerializeField] private TMP_Text chatText = null;
    [SerializeField] private TMP_InputField inputField = null;
    private PlayerInput playerInput;
    private InputAction sendAction;
    private NetworkRoomPlayerLobby player;

    private static event Action<string> OnMessage;

    void Awake(){
        playerInput = GetComponent<PlayerInput>();
        sendAction = playerInput.actions["SendMessage"];
    }
    
    public override void OnStartAuthority(){    
        chatUI.SetActive(true);
        OnMessage += HandleNewMessage;
    }
    
    [ClientCallback]
    private void OnDestroy(){
        if(!hasAuthority){
            return;
        }
        OnMessage -= HandleNewMessage;
    }

    private void HandleNewMessage(string message){
        chatText.text += message;
    }

    // Send a message to the server
    [Client]
    public void Send(string message){
        player = NetworkClient.connection.identity.GetComponent<NetworkRoomPlayerLobby>();
        if(!sendAction.triggered){
            return;
        }

        if(string.IsNullOrWhiteSpace(inputField.text)){
            return;
        }

        CmdSendMessage($"[{player.DisplayName}]: " + inputField.text);
        inputField.text = string.Empty;
    }

    // Handle the message, then send to clients
    [Command]
    private void CmdSendMessage(string message){
        RpcHandleMessage($"{message}");
    }

    // Other clients receiving the message
    [ClientRpc]
    private void RpcHandleMessage(string message){
        OnMessage?.Invoke($"\n{message}");
    }
}