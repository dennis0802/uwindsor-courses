using Mirror;
using UnityEngine;
using UnityEngine.UI;
using TMPro;
using System.Collections;
using System.Collections.Generic;

// Based off of: https://www.youtube.com/watch?v=Fx8efi2MNz0
//               https://www.youtube.com/watch?v=WMJS7sVp2FQ
public class NetworkGamePlayerLobby : NetworkBehaviour {

    [SyncVar]
    public string DisplayName = "Loading...";
    [SyncVar]
    public string Team = string.Empty;
    [SyncVar]
    public string Weapon = string.Empty;

    private NetworkManagerLobby room;
    private NetworkManagerLobby Room{
        get{
            if(room != null){
                return room;
            }
            return room = NetworkManager.singleton as NetworkManagerLobby;
        }
    }

    public override void OnStartClient(){
        DontDestroyOnLoad(gameObject);
        Room.GamePlayers.Add(this);
    }

    public override void OnStopClient(){
        Cursor.lockState = CursorLockMode.None;
        Room.GamePlayers.Remove(this);
    }

    // Setting properties of each player
    [Server]
    public void SetDisplayName(string displayName){
        this.DisplayName = displayName;
    }

    [Server]
    public void SetTeam(string team){
        this.Team = team;
    }

    [Server]
    public void SetWeapon(string weapon){
        this.Weapon = weapon;
    }
}