using Mirror;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.InputSystem;
using System;
using TMPro;

// Based off of: https://www.youtube.com/watch?v=Fx8efi2MNz0
//               https://www.youtube.com/watch?v=WMJS7sVp2FQ
public class NetworkRoomPlayerLobby : NetworkBehaviour {
    [Header("UI")]
    [SerializeField] private GameObject lobbyUI = null;
    [SerializeField] private TMP_Text[] playerNameTexts = new TMP_Text[4];
    [SerializeField] private TMP_Text[] playerReadyTexts = new TMP_Text[4];
    [SerializeField] private Button startGameButton = null;

    [SyncVar(hook = nameof(HandleDisplayNameChanged))]
    public string DisplayName = "Loading...";
    [SyncVar(hook = nameof(HandleReadyStatusChanged))]
    public bool IsReady = false;
    [SyncVar(hook = nameof(HandleTeamChanged))]
    public string Team = string.Empty;
    [SyncVar]
    public string Weapon = string.Empty;

    private bool isLeader;
    public bool IsLeader{
        set{
            isLeader = value;
            startGameButton.gameObject.SetActive(value);
        }
    }

    private NetworkManagerLobby room;
    private NetworkManagerLobby Room{
        get{
            if(room != null){
                return room;
            }
            return room = NetworkManager.singleton as NetworkManagerLobby;
        }
    }

    public override void OnStartAuthority(){
        CmdSetDisplayName(PlayerNameInput.DisplayName);
        lobbyUI.SetActive(true);
    }

    public override void OnStartClient(){
        Room.RoomPlayers.Add(this);
        UpdateDisplay();
    }

    public override void OnStopClient(){
        Room.RoomPlayers.Remove(this);
        UpdateDisplay();
    }

    public void HandleReadyStatusChanged(bool oldValue, bool newValue) => UpdateDisplay();
    public void HandleDisplayNameChanged(string oldValue, string newValue) => UpdateDisplay();
    public void HandleTeamChanged(string oldValue, string newValue) => UpdateDisplay();

    // Change display info depending on player statuses
    private void UpdateDisplay(){
        if(!hasAuthority){
            foreach(var player in Room.RoomPlayers){
                if(player.hasAuthority){
                    player.UpdateDisplay();
                    break;
                }
            }
            return;
        }

        // Name
        for(int i = 0; i < playerNameTexts.Length; i++){
            playerNameTexts[i].text = "Waiting for player...";
            playerReadyTexts[i].text = string.Empty;
        }

        // Ready text
        for(int i = 0; i < Room.RoomPlayers.Count; i++){
            playerNameTexts[i].text = Room.RoomPlayers[i].DisplayName;
            playerReadyTexts[i].text = Room.RoomPlayers[i].IsReady ? "<color=green>Ready</color>" : "<color=red>Not Ready</color>";
        }

        // Team selection - visualized in their player name
        for(int i = 0; i < Room.RoomPlayers.Count; i++){
            if(Room.RoomPlayers[i].Team == "Red"){
                playerNameTexts[i].text = "<color=red>" + playerNameTexts[i].text + "</color>";
            }
            else if(Room.RoomPlayers[i].Team == "Blue"){
                playerNameTexts[i].text = "<color=#7E89FC>" + playerNameTexts[i].text + "</color>";
            }
        }
    }

    // Check to start
    public void HandleReadyToStart(bool readyToStart){
        if(!isLeader){
            return;
        }
        startGameButton.interactable = readyToStart;
    }

    // Set display name
    [Command]
    private void CmdSetDisplayName(string displayName){
        DisplayName = displayName;
    }

    // Set to blue team
    [Command]
    public void CmdSetBlueTeam(){
        // Team switching if applicable
        if(Room.RedPlayers.Contains(this)){
            Room.RedPlayers.Remove(this);
        }
        Room.BluePlayers.Add(this);
        Team = "Blue";
    }

    // Set to red team
    [Command]
    public void CmdSetRedTeam(){
        // Team switching if applicable
        if(Room.BluePlayers.Contains(this)){
            Room.BluePlayers.Remove(this);
        }
        Room.RedPlayers.Add(this);
        Team = "Red";
    }

    // Set gun
    [Command]
    public void CmdSetGun(){
        Weapon = "Gun";
    }

    // Set spear
    [Command]
    public void CmdSetSpear(){
        Weapon = "Spear";
    }

    // Set sword
    [Command]
    public void CmdSetSword(){
        Weapon = "Sword";
    }

    // Set magic
    [Command]
    public void CmdSetMagic(){
        Weapon = "Magic";
    }

    // Set ready
    [Command]
    public void CmdReadyUp(){
        if(Team == string.Empty || Weapon == string.Empty){
            Debug.Log("Team or weapon has not been selected.");
            return;
        }
        IsReady = !IsReady;
        Room.NotifyPlayersOfReadyState();
    }

    // Start game
    [Command]
    public void CmdStartGame(){
        if(Room.RoomPlayers[0].connectionToClient != connectionToClient){
            return;
        }
        
        Room.StartGame();
    }
}